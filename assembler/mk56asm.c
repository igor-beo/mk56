/**
 * MK56-ASM Assembler - Implementation
 */

#include "mk56asm.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_TOKENS 128

// ============================================================================
// HELPERS
// ============================================================================

static void set_error(Assembler *as, int line, const char *fmt, const char *arg) {
    if (as->has_error) return;
    as->has_error = true;
    as->error_line = line;
    char msg[200];
    snprintf(msg, sizeof msg, fmt, arg ? arg : "");
    snprintf(as->error_msg, sizeof as->error_msg, "Line %d: %s", line, msg);
}

static void emit(Assembler *as, uint8_t code, int line) {
    if (as->current_address >= MK56_STEPS) {
        set_error(as, line, "Program exceeds %s98 steps (00-97)", "");
        return;
    }
    as->binary[as->current_address++] = code;
    if ((size_t)as->current_address > as->binary_size)
        as->binary_size = (size_t)as->current_address;
}

static bool is_identifier(const char *s) {
    if (!isalpha((unsigned char)s[0]) && s[0] != '_') return false;
    for (; *s; s++)
        if (!isalnum((unsigned char)*s) && *s != '_') return false;
    return true;
}

static bool is_unsigned_int(const char *s) {
    if (!*s) return false;
    for (; *s; s++) if (!isdigit((unsigned char)*s)) return false;
    return true;
}

static int find_label(const Assembler *as, const char *name) {
    for (size_t i = 0; i < as->label_count; i++)
        if (strcasecmp(as->labels[i].name, name) == 0) return as->labels[i].address;
    return -1;
}

static void define_label(Assembler *as, const char *name, int line) {
    if (find_label(as, name) >= 0) { set_error(as, line, "Duplicate label: %s", name); return; }
    if (as->label_count >= MK56_MAX_LABELS) { set_error(as, line, "Too many labels%s", ""); return; }
    Label *l = &as->labels[as->label_count++];
    snprintf(l->name, sizeof l->name, "%s", name);
    l->address = as->current_address;
}

/* "NN:" asserts the address of the next step; "name:" defines a label. */
static void address_marker(Assembler *as, const char *tok, int line) {
    if (is_unsigned_int(tok)) {
        if (atoi(tok) != as->current_address) {
            char msg[64];
            snprintf(msg, sizeof msg, "%s: is at address %02d", tok, as->current_address);
            set_error(as, line, "Address mismatch: %s", msg);
        }
    } else if (is_identifier(tok)) {
        define_label(as, tok, line);
    } else {
        set_error(as, line, "Invalid label: %s", tok);
    }
}

/* Address operand: "42" or a label (patched in the second pass). */
static void emit_address(Assembler *as, const char *tok, int line) {
    if (!tok) { set_error(as, line, "Missing address%s", ""); return; }
    if (is_unsigned_int(tok)) {
        int addr = atoi(tok);
        if (addr >= MK56_STEPS) { set_error(as, line, "Address out of range 00-97: %s", tok); return; }
        emit(as, mk56_addr_encode(addr), line);
    } else if (is_identifier(tok)) {
        if (as->fixup_count >= MK56_MAX_FIXUPS) { set_error(as, line, "Too many label references%s", ""); return; }
        Fixup *f = &as->fixups[as->fixup_count++];
        f->address = as->current_address;
        snprintf(f->label, sizeof f->label, "%s", tok);
        f->source_line = line;
        emit(as, 0, line);
    } else {
        set_error(as, line, "Invalid address: %s", tok);
    }
}

/* "R3", "RA", "Rd" -> 0-13 */
static int parse_register(const char *s) {
    if ((s[0] != 'R' && s[0] != 'r') || !s[1] || s[2]) return -1;
    char c = (char)toupper((unsigned char)s[1]);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'D') return 10 + c - 'A';
    return -1;
}

/* "(R3)" -> 3 */
static int parse_indirect(const char *s) {
    size_t n = strlen(s);
    if (n < 4 || s[0] != '(' || s[n - 1] != ')') return -1;
    char inner[8];
    if (n - 2 >= sizeof inner) return -1;
    memcpy(inner, s + 1, n - 2);
    inner[n - 2] = '\0';
    return parse_register(inner);
}

/* Number literal -> keystrokes: mantissa digits and point, /-/ for a
 * negative mantissa, then ВП, exponent digits and /-/ for a negative
 * exponent. "-1.5e-3" -> 1 , 5 /-/ ВП 3 /-/ */
static bool emit_number(Assembler *as, const char *tok, int line) {
    const char *p = tok;
    bool neg = false, exp_neg = false, point = false;
    char mant[16];
    int mant_len = 0, digits = 0;

    if (*p == '-' || *p == '+') neg = (*p++ == '-');
    for (; isdigit((unsigned char)*p) || *p == '.' || *p == ','; p++) {
        if (*p == '.' || *p == ',') {
            if (point) return false;
            point = true;
            mant[mant_len++] = '.';
        } else {
            if (++digits > 8) { set_error(as, line, "More than 8 mantissa digits: %s", tok); return true; }
            mant[mant_len++] = *p;
        }
    }
    if (digits == 0) return false;

    int exp_digits = 0;
    char exp[3] = { 0 };
    if (*p == 'e' || *p == 'E') {
        p++;
        if (*p == '-' || *p == '+') exp_neg = (*p++ == '-');
        while (isdigit((unsigned char)*p)) {
            if (exp_digits >= 2) { set_error(as, line, "Exponent has more than 2 digits: %s", tok); return true; }
            exp[exp_digits++] = *p++;
        }
        if (exp_digits == 0) return false;
    }
    if (*p) return false;

    for (int i = 0; i < mant_len; i++)
        emit(as, mant[i] == '.' ? MK56_POINT : (uint8_t)(mant[i] - '0'), line);
    if (neg) emit(as, MK56_CHS, line);
    if (exp_digits) {
        emit(as, MK56_EEX, line);
        for (int i = 0; i < exp_digits; i++) emit(as, (uint8_t)(exp[i] - '0'), line);
        if (exp_neg) emit(as, MK56_CHS, line);
    }
    return true;
}

// ============================================================================
// MK56-ASM STATEMENTS
// ============================================================================

typedef struct { const char *name; uint8_t direct; uint8_t indirect; bool has_indirect; } BranchDef;

static const BranchDef BRANCHES[] = {
    { "JMP",   MK56_JMP,    MK56_K_JMP,  true },
    { "GOTO",  MK56_JMP,    MK56_K_JMP,  true },
    { "CALL",  MK56_CALL,   MK56_K_CALL, true },
    { "JZ",    MK56_FX_NE0, MK56_K_NE0,  true },
    { "JNZ",   MK56_FX_EQ0, MK56_K_EQ0,  true },
    { "JLT",   MK56_FX_GE0, MK56_K_GE0,  true },
    { "JGE",   MK56_FX_LT0, MK56_K_LT0,  true },
    { "LOOP0", MK56_FL0,    0, false },
    { "LOOP1", MK56_FL1,    0, false },
    { "LOOP2", MK56_FL2,    0, false },
    { "LOOP3", MK56_FL3,    0, false },
    { NULL, 0, 0, false }
};

static const char *ALIASES[][2] = {
    { "STOP", "HALT" }, { "RETURN", "RTN" }, { "ROLLDOWN", "ROT" }, { NULL, NULL }
};

static void asm_statement(Assembler *as, char **tok, int n, int line) {
    char m[32];
    snprintf(m, sizeof m, "%s", tok[0]);
    for (char *c = m; *c; c++) *c = (char)toupper((unsigned char)*c);
    for (int i = 0; ALIASES[i][0]; i++)
        if (strcmp(m, ALIASES[i][0]) == 0) snprintf(m, sizeof m, "%s", ALIASES[i][1]);

    if (strcmp(m, "ROLLUP") == 0 || strcmp(m, "STO+") == 0 || strcmp(m, "STO-") == 0) {
        set_error(as, line, "%s is not an MK-56 instruction", m);
        return;
    }

    int used = 1;
    if (strcmp(m, "STO") == 0 || strcmp(m, "RCL") == 0) {
        bool sto = m[0] == 'S';
        int r;
        if (n < 2) { set_error(as, line, "%s needs a register", m); return; }
        if ((r = parse_register(tok[1])) >= 0) emit(as, (uint8_t)((sto ? MK56_STO : MK56_RCL) + r), line);
        else if ((r = parse_indirect(tok[1])) >= 0) emit(as, (uint8_t)((sto ? MK56_K_STO : MK56_K_RCL) + r), line);
        else { set_error(as, line, "Invalid register: %s", tok[1]); return; }
        used = 2;
    } else {
        const BranchDef *b = BRANCHES;
        while (b->name && strcmp(b->name, m) != 0) b++;
        if (b->name) {
            if (n < 2) { set_error(as, line, "%s needs an address", m); return; }
            int r = parse_indirect(tok[1]);
            if (r >= 0) {
                if (!b->has_indirect) { set_error(as, line, "%s has no indirect form", m); return; }
                emit(as, (uint8_t)(b->indirect + r), line);
            } else {
                emit(as, b->direct, line);
                emit_address(as, tok[1], line);
            }
            used = 2;
        } else {
            int code = -1;
            for (int c = 0; c < 256 && code < 0; c++) {
                const Mk56Op *op = mk56_op((uint8_t)c);
                if (op->valid && !op->has_addr && c > 9 && strcmp(op->mnem, m) == 0) code = c;
            }
            if (code >= 0) {
                emit(as, (uint8_t)code, line);
            } else if (emit_number(as, tok[0], line)) {
                /* literal */
            } else {
                /* Original notation is accepted too: "Fx²", "БП 12" */
                code = mk56_parse_key(tok, n, &used);
                if (code < 0) { set_error(as, line, "Unknown instruction: %s", tok[0]); return; }
                emit(as, (uint8_t)code, line);
                if (mk56_op((uint8_t)code)->has_addr) {
                    emit_address(as, used < n ? tok[used] : NULL, line);
                    used++;
                }
            }
        }
    }
    if (used < n) set_error(as, line, "Unexpected: %s", tok[used]);
}

// ============================================================================
// LISTING NOTATION
// ============================================================================

static bool is_number_token(const char *s) {
    bool digit = false;
    for (; *s; s++) {
        if (isdigit((unsigned char)*s)) digit = true;
        else if (*s != ',' && *s != '.') return false;
    }
    return digit;
}

static void listing_steps(Assembler *as, char **tok, int n, int line) {
    for (int i = 0; i < n && !as->has_error; ) {
        size_t len = strlen(tok[i]);
        if (len > 1 && tok[i][len - 1] == ':') {
            tok[i][len - 1] = '\0';
            address_marker(as, tok[i], line);
            i++;
            continue;
        }
        if (is_number_token(tok[i])) {
            for (const char *c = tok[i]; *c; c++)
                emit(as, isdigit((unsigned char)*c) ? (uint8_t)(*c - '0') : MK56_POINT, line);
            i++;
            continue;
        }
        int used = 1;
        int code = mk56_parse_key(tok + i, n - i, &used);
        if (code < 0) { set_error(as, line, "Unknown key: %s", tok[i]); return; }
        emit(as, (uint8_t)code, line);
        i += used;
        if (mk56_op((uint8_t)code)->has_addr) {
            emit_address(as, i < n ? tok[i] : NULL, line);
            i++;
        }
    }
}

// ============================================================================
// LINES
// ============================================================================

static int tokenize(char *s, char **tok) {
    int n = 0;
    for (char *p = strtok(s, " \t\r"); p && n < MAX_TOKENS; p = strtok(NULL, " \t\r"))
        tok[n++] = p;
    return n;
}

/* Returns false at .END */
static bool parse_line(Assembler *as, const char *text, int line) {
    char buf[MK56_MAX_LINE_LEN];
    snprintf(buf, sizeof buf, "%s", text);
    char *c = strchr(buf, ';');
    if (c) *c = '\0';
    if ((c = strstr(buf, "//")) != NULL) *c = '\0';

    char *tok[MAX_TOKENS];
    int n = tokenize(buf, tok);
    if (n == 0) return true;

    if (tok[0][0] == '.' && isalpha((unsigned char)tok[0][1])) {
        char d[16];
        snprintf(d, sizeof d, "%s", tok[0] + 1);
        for (char *p = d; *p; p++) *p = (char)toupper((unsigned char)*p);
        if (strcmp(d, "END") == 0) return false;
        if (strcmp(d, "LISTING") == 0) as->listing_syntax = true;
        else if (strcmp(d, "ASM") == 0) as->listing_syntax = false;
        else if (strcmp(d, "ORG") == 0) {
            int addr = n > 1 ? atoi(tok[1]) : -1;
            if (addr < 0 || addr >= MK56_STEPS) set_error(as, line, ".ORG needs an address 00-97%s", "");
            else as->current_address = addr;
        } else if (strcmp(d, "STEP") == 0) {
            if (n < 2) set_error(as, line, ".STEP needs a code%s", "");
            else emit(as, (uint8_t)strtol(tok[1], NULL, 16), line);
        }
        /* .EQU, .ASSERT, .TRACE, .BREAK: accepted, ignored */
        return true;
    }

    int start = as->current_address;
    if (as->listing_syntax) {
        listing_steps(as, tok, n, line);
    } else {
        int i = 0;
        /* Leading "label:" / "NN:" markers, also glued: "loop:RCL" */
        while (i < n) {
            char *colon = strchr(tok[i], ':');
            if (!colon || colon == tok[i]) break;
            *colon = '\0';
            address_marker(as, tok[i], line);
            if (colon[1]) { tok[i] = colon + 1; break; }
            i++;
        }
        if (i < n && !as->has_error) asm_statement(as, tok + i, n - i, line);
    }

    if (as->line_count < MK56_MAX_LINES) {
        ListingLine *l = &as->lines[as->line_count++];
        l->address = start;
        l->steps = as->current_address - start;
        l->source_line = line;
        snprintf(l->source_text, sizeof l->source_text, "%s", text);
    }
    return true;
}

static void resolve_labels(Assembler *as) {
    for (size_t i = 0; i < as->fixup_count && !as->has_error; i++) {
        const Fixup *f = &as->fixups[i];
        int addr = find_label(as, f->label);
        if (addr < 0) set_error(as, f->source_line, "Undefined label: %s", f->label);
        else as->binary[f->address] = mk56_addr_encode(addr);
    }
}

// ============================================================================
// PUBLIC API
// ============================================================================

void asm_init(Assembler *as) {
    memset(as, 0, sizeof(Assembler));
}

bool asm_assemble_ex(Assembler *as, const char *source, bool listing) {
    asm_init(as);
    as->listing_syntax = listing;

    const char *p = source;
    for (int line = 1; *p && !as->has_error; line++) {
        const char *eol = strchr(p, '\n');
        size_t len = eol ? (size_t)(eol - p) : strlen(p);
        char text[MK56_MAX_LINE_LEN];
        if (len >= sizeof text) {
            set_error(as, line, "Line too long%s", "");
            break;
        }
        memcpy(text, p, len);
        text[len] = '\0';
        if (!parse_line(as, text, line)) break;
        p = eol ? eol + 1 : p + len;
    }

    if (!as->has_error) resolve_labels(as);
    return !as->has_error;
}

bool asm_assemble(Assembler *as, const char *source) {
    return asm_assemble_ex(as, source, false);
}

int asm_encode_line(const char *line, uint8_t *out, size_t max,
                    char *err, size_t err_size) {
    Assembler *as = malloc(sizeof *as);
    if (!as) { snprintf(err, err_size, "Out of memory"); return -1; }

    /* Lines with non-ASCII characters are original notation */
    bool listing = false;
    for (const unsigned char *c = (const unsigned char *)line; *c; c++)
        if (*c >= 0x80) listing = true;

    bool ok = asm_assemble_ex(as, line, listing);
    if (ok && as->fixup_count) {
        ok = false;
        snprintf(as->error_msg, sizeof as->error_msg, "Labels are not allowed here");
    }
    int steps = (int)as->binary_size;
    if (ok && (size_t)steps > max) {
        ok = false;
        snprintf(as->error_msg, sizeof as->error_msg, "Too many steps (%d)", steps);
    }
    if (ok) memcpy(out, as->binary, (size_t)steps);
    else snprintf(err, err_size, "%s", as->error_msg);
    free(as);
    return ok ? steps : -1;
}

const uint8_t* asm_get_binary(const Assembler *as, size_t *out_size) {
    if (out_size) *out_size = as->binary_size;
    return as->binary;
}

/* Characters, not bytes: the original notation is UTF-8. */
static int utf8_width(const char *s) {
    int n = 0;
    for (; *s; s++) if ((*s & 0xC0) != 0x80) n++;
    return n;
}

size_t asm_get_listing(const Assembler *as, char *buffer, size_t buffer_size) {
    size_t off = 0;
    off += (size_t)snprintf(buffer, buffer_size,
        "ADDR  CODES             KEYS                      SOURCE\n"
        "==============================================================================\n");

    for (size_t i = 0; i < as->line_count && off + 200 < buffer_size; i++) {
        const ListingLine *l = &as->lines[i];
        if (l->steps == 0) continue;

        char codes[64] = "", keys[256] = "";
        size_t cl = 0, kl = 0;
        for (int a = l->address; a < l->address + l->steps; ) {
            char k[40];
            int size = mk56_disasm(as->binary, a, false, k, sizeof k);
            if (a + size > l->address + l->steps) size = l->address + l->steps - a;
            for (int s = 0; s < size && cl + 4 < sizeof codes; s++)
                cl += (size_t)snprintf(codes + cl, sizeof codes - cl, "%02X ", as->binary[a + s]);
            if (kl + strlen(k) + 2 < sizeof keys)
                kl += (size_t)snprintf(keys + kl, sizeof keys - kl, "%s ", k);
            a += size;
        }
        const char *src = l->source_text;
        while (*src == ' ' || *src == '\t') src++;
        int pad = 25 - utf8_width(keys);
        off += (size_t)snprintf(buffer + off, buffer_size - off, "%02d    %-17s %s%*s %s\n",
                                l->address, codes, keys, pad > 0 ? pad : 0, "", src);
    }
    return off;
}

// ============================================================================
// MK56-ASM SOURCE FROM MACHINE CODE
// ============================================================================

static bool is_mantissa_step(uint8_t c) { return c <= 9 || c == MK56_POINT; }

/* Steps a.. that form one number literal, written to `lit`; 0 if none.
 * Stops at labels so a jump target always starts a statement. */
static int number_run(const uint8_t *prog, int a, int n, const char *label,
                      char *lit, size_t size) {
    char mant[16], exp[4] = "";
    int b = a, mlen = 0, digits = 0, elen = 0;
    bool point = false, neg = false, eneg = false;

    while (b < n && is_mantissa_step(prog[b]) && (b == a || !label[b])) {
        if (prog[b] == MK56_POINT) { if (point) break; point = true; mant[mlen++] = '.'; }
        else { if (digits == 8) break; digits++; mant[mlen++] = (char)('0' + prog[b]); }
        b++;
    }
    if (digits == 0) return 0;
    mant[mlen] = '\0';
    if (b < n && prog[b] == MK56_CHS && !label[b]) { neg = true; b++; }
    if (b + 1 < n && prog[b] == MK56_EEX && !label[b] && prog[b + 1] <= 9 && !label[b + 1]) {
        int e = b + 1;
        while (e < n && prog[e] <= 9 && elen < 2 && !label[e]) exp[elen++] = (char)('0' + prog[e++]);
        exp[elen] = '\0';
        if (e < n && prog[e] == MK56_CHS && !label[e]) { eneg = true; e++; }
        b = e;
    }
    snprintf(lit, size, "%s%s%s%s%s", neg ? "-" : "", mant, elen ? "e" : "", eneg ? "-" : "", exp);
    return b - a;
}

size_t asm_to_source(const uint8_t *prog, size_t n, char *buffer, size_t buffer_size) {
    char label[MK56_STEPS] = { 0 };     /* 'L' jump target, 's' subroutine */
    bool start[MK56_STEPS] = { false };
    int len = (int)(n < MK56_STEPS ? n : MK56_STEPS);
    size_t off = 0;
    buffer[0] = '\0';

    for (int a = 0; a < len; a += mk56_op(prog[a])->has_addr ? 2 : 1) start[a] = true;
    for (int a = 0; a < len; a++) {
        const Mk56Op *op = mk56_op(prog[a]);
        if (!start[a] || !op->has_addr || a + 1 >= len) continue;
        int t = mk56_addr_decode(prog[a + 1]);
        if (t >= 0 && t < len && start[t] && label[t] != 's')
            label[t] = prog[a] == MK56_CALL ? 's' : 'L';
    }

    for (int a = 0; a < len; ) {
        char stmt[48], lit[24];
        int size = number_run(prog, a, len, label, lit, sizeof lit);
        const Mk56Op *op = mk56_op(prog[a]);
        if (size) {
            snprintf(stmt, sizeof stmt, "%s", lit);
        } else if (!op->valid) {
            size = 1;
            snprintf(stmt, sizeof stmt, ".STEP %02X", prog[a]);
        } else {
            size = mk56_disasm(prog, a, true, stmt, sizeof stmt);
            int t = size == 2 ? mk56_addr_decode(prog[a + 1]) : -1;
            if (t >= 0 && t < len && label[t])
                snprintf(stmt, sizeof stmt, "%s %s%02d", op->mnem, label[t] == 's' ? "sub" : "L", t);
        }
        if (a + size > len) size = len - a;

        char keys[96] = "", codes[48] = "";
        size_t kl = 0, cl = 0;
        for (int b = a; b < a + size; ) {
            char k[40];
            int s = mk56_disasm(prog, b, false, k, sizeof k);
            if (b + s > a + size) s = a + size - b;
            kl += (size_t)snprintf(keys + kl, sizeof keys - kl, "%s%s", kl ? " " : "", k);
            for (int i = 0; i < s; i++)
                cl += (size_t)snprintf(codes + cl, sizeof codes - cl, "%s%02X", cl ? " " : "", prog[b + i]);
            b += s;
        }

        if (label[a] && off < buffer_size)
            off += (size_t)snprintf(buffer + off, buffer_size - off, "%s%s%02d:\n",
                                    a ? "\n" : "", label[a] == 's' ? "sub" : "L", a);
        int pad = 14 - utf8_width(keys);
        if (off < buffer_size)
            off += (size_t)snprintf(buffer + off, buffer_size - off, "        %-16s; %02d  %s%*s %s\n",
                                    stmt, a, keys, pad > 0 ? pad : 0, "", codes);
        a += size;
    }
    return off < buffer_size ? off : buffer_size - 1;
}

const char* asm_get_error(const Assembler *as) {
    return as->has_error ? as->error_msg : NULL;
}
