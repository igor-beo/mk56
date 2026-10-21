/**
 * MK-56 instruction set - opcode table, listing-notation parser,
 * disassembler. See mk56_isa.h.
 */

#include "mk56_isa.h"
#include <stdio.h>
#include <string.h>

static const char *REG_NAMES[MK56_NUM_REGISTERS] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d"
};

static const char *ASM_REG_NAMES[MK56_NUM_REGISTERS] = {
    "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9",
    "RA", "RB", "RC", "RD"
};

static Mk56Op ops[256];

/* Listing-notation spellings, stored in canonical form (see canon()). */
typedef struct {
    char canon[24];
    uint8_t code;
    bool reg_prefix;        /* code is a base; a register 0-13 follows */
} Alias;

static Alias aliases[256];
static int alias_count;
static bool initialized;

/* ------------------------------------------------------------------------ */
/* Canonical form: lowercase ASCII, Cyrillic/Latin lookalikes folded, math  */
/* symbols mapped to single ASCII characters. "ИП3" and "ИП 3" both become  */
/* "IP3"; "Fx≠0" and "Fx!=0" both become "fx#0".                            */
/* ------------------------------------------------------------------------ */

static unsigned decode_utf8(const unsigned char **p) {
    const unsigned char *s = *p;
    unsigned c = s[0];
    int len = 1;
    if (c >= 0xF0 && s[1] && s[2] && s[3]) {
        c = ((c & 0x07) << 18) | ((s[1] & 0x3F) << 12) | ((s[2] & 0x3F) << 6) | (s[3] & 0x3F);
        len = 4;
    } else if (c >= 0xE0 && s[1] && s[2]) {
        c = ((c & 0x0F) << 12) | ((s[1] & 0x3F) << 6) | (s[2] & 0x3F);
        len = 3;
    } else if (c >= 0xC0 && s[1]) {
        c = ((c & 0x1F) << 6) | (s[1] & 0x3F);
        len = 2;
    }
    *p = s + len;
    return c;
}

static const char *canon_char(unsigned c) {
    if (c >= 0x410 && c <= 0x42F) c += 0x20;            /* Cyrillic upper -> lower */
    switch (c) {
    case 0x430: return "a";     /* а */
    case 0x432: return "b";     /* в: В/О, В↑, ВП, register в */
    case 0x441: return "c";     /* с */
    case 0x434: return "d";     /* д */
    case 0x435: return "e";     /* е */
    case 0x43E: return "o";     /* о */
    case 0x445: return "x";     /* х */
    case 0x43A: return "k";     /* к */
    case 0x440: return "p";     /* р */
    case 0x43B: return "l";     /* л */
    case 0x43F: return "P";     /* п */
    case 0x438: return "I";     /* и */
    case 0x431: return "B";     /* б */
    case 0x43D: return "N";     /* н */
    case 0x433: return "G";     /* г */
    case 0x2212: case 0x2013: return "-";
    case 0x00D7: return "*";
    case 0x00F7: return ":";
    case 0x2191: return "|";    /* ↑ */
    case 0x2192: return ">";    /* → */
    case 0x2260: return "#";    /* ≠ */
    case 0x2265: return "}";    /* ≥ */
    case 0x2194: return "~";    /* ↔ */
    case 0x03C0: return "pi";
    case 0x221A: return "sqrt";
    case 0x00B2: return "2";
    case 0x02E3: return "x";    /* ˣ */
    case 0x02B8: return "y";    /* ʸ */
    case 0x207B: return "-";    /* ⁻ */
    case 0x00B9: return "1";    /* ¹ */
    case 0x27F3: case 0x21BB: return "@";   /* ⟳ */
    default: return NULL;
    }
}

static void canon(const char *in, char *out, size_t size) {
    const unsigned char *p = (const unsigned char *)in;
    size_t n = 0;
    while (*p && n + 5 < size) {
        if (*p < 0x80) {
            char c = (char)*p++;
            if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
            if (c == '^') continue;
            if (c == '-' && *p == '>') { p++; out[n++] = '>'; continue; }
            if (c == '!' && *p == '=') { p++; out[n++] = '#'; continue; }
            if (c == '>' && *p == '=') { p++; out[n++] = '}'; continue; }
            if (c == '<' && *p == '>') { p++; out[n++] = '#'; continue; }
            if (c == '<' && p[0] == '-' && p[1] == '>') { p += 2; out[n++] = '~'; continue; }
            out[n++] = c;
        } else {
            const char *m = canon_char(decode_utf8(&p));
            if (!m) m = "?";
            while (*m && n + 1 < size) out[n++] = *m++;
        }
    }
    out[n] = '\0';
}

/* ------------------------------------------------------------------------ */
/* Table construction                                                       */
/* ------------------------------------------------------------------------ */

static void alias_add(uint8_t code, const char *spelling, bool reg_prefix) {
    Alias *a = &aliases[alias_count++];
    canon(spelling, a->canon, sizeof a->canon);
    a->code = code;
    a->reg_prefix = reg_prefix;
}

static void def(uint8_t code, const char *key, const char *mnem, bool has_addr) {
    Mk56Op *op = &ops[code];
    op->valid = true;
    op->has_addr = has_addr;
    snprintf(op->key, sizeof op->key, "%s", key);
    snprintf(op->mnem, sizeof op->mnem, "%s", mnem);
    alias_add(code, key, false);
}

/* A register family: base + 0..13, e.g. ИП0..ИПd. */
static void def_reg(uint8_t base, const char *key, const char *mnem_fmt) {
    for (int r = 0; r < MK56_NUM_REGISTERS; r++) {
        Mk56Op *op = &ops[base + r];
        op->valid = true;
        snprintf(op->key, sizeof op->key, "%s%s", key, REG_NAMES[r]);
        snprintf(op->mnem, sizeof op->mnem, mnem_fmt, ASM_REG_NAMES[r]);
    }
    alias_add(base, key, true);
}

static void init(void) {
    if (initialized) return;
    initialized = true;

    for (int c = 0; c < 256; c++) {
        snprintf(ops[c].key, sizeof ops[c].key, "?%02X", c);
        snprintf(ops[c].mnem, sizeof ops[c].mnem, ".STEP 0x%02X", c);
    }

    static const char *digits[10] = { "0","1","2","3","4","5","6","7","8","9" };
    for (int d = 0; d < 10; d++) def((uint8_t)d, digits[d], digits[d], false);

    def(MK56_POINT, ",", ".", false);       alias_add(MK56_POINT, ".", false);
    def(MK56_CHS, "/-/", "CHS", false);
    def(MK56_EEX, "ВП", "EEX", false);
    def(MK56_CLX, "Cx", "CLX", false);
    def(MK56_ENTER, "В↑", "ENTER", false);  alias_add(MK56_ENTER, "↑", false);
    def(MK56_LASTX, "FBx", "LASTX", false);

    def(MK56_ADD, "+", "ADD", false);
    def(MK56_SUB, "−", "SUB", false);
    def(MK56_MUL, "×", "MUL", false);       alias_add(MK56_MUL, "*", false);
    def(MK56_DIV, "÷", "DIV", false);       alias_add(MK56_DIV, "/", false);
    def(MK56_SWAP, "↔", "SWAP", false);     alias_add(MK56_SWAP, "XY", false);
    def(MK56_EXP10, "F10ˣ", "EXP10", false);
    def(MK56_EXP, "Feˣ", "EXP", false);
    def(MK56_LOG, "Flg", "LOG", false);
    def(MK56_LN, "Fln", "LN", false);
    def(MK56_ASIN, "Fsin⁻¹", "ASIN", false);  alias_add(MK56_ASIN, "Farcsin", false);
    def(MK56_ACOS, "Fcos⁻¹", "ACOS", false);  alias_add(MK56_ACOS, "Farccos", false);
    def(MK56_ATAN, "Ftg⁻¹", "ATAN", false);   alias_add(MK56_ATAN, "Farctg", false);
    def(MK56_SIN, "Fsin", "SIN", false);
    def(MK56_COS, "Fcos", "COS", false);
    def(MK56_TAN, "Ftg", "TAN", false);     alias_add(MK56_TAN, "Ftan", false);

    def(MK56_PI, "Fπ", "PI", false);
    def(MK56_SQRT, "F√", "SQRT", false);
    def(MK56_SQ, "Fx²", "SQ", false);
    def(MK56_INV, "F1/x", "INV", false);
    def(MK56_POW, "Fxʸ", "POW", false);
    def(MK56_ROT, "F⟳", "ROT", false);      alias_add(MK56_ROT, "F,", false);
                                            alias_add(MK56_ROT, "F.", false);

    def_reg(MK56_STO, "П", "STO %s");       alias_add(MK56_STO, "x→П", true);
    def_reg(MK56_RCL, "ИП", "RCL %s");      alias_add(MK56_RCL, "П→x", true);

    def(MK56_HALT, "С/П", "HALT", false);
    def(MK56_JMP, "БП", "JMP", true);
    def(MK56_RTN, "В/О", "RTN", false);     alias_add(MK56_RTN, "В/0", false);
    def(MK56_CALL, "ПП", "CALL", true);
    def(MK56_NOP, "КНОП", "NOP", false);    alias_add(MK56_NOP, "НОП", false);

    /* Conditional jumps go to the address when the condition FAILS
     * (manual p.65), so each ASM mnemonic names the opposite condition:
     * Fx≥0 nn jumps when X < 0, hence JLT. */
    def(MK56_FX_NE0, "Fx≠0", "JZ", true);
    def(MK56_FX_GE0, "Fx≥0", "JLT", true);
    def(MK56_FX_LT0, "Fx<0", "JGE", true);
    def(MK56_FX_EQ0, "Fx=0", "JNZ", true);
    def(MK56_FL0, "FL0", "LOOP0", true);
    def(MK56_FL1, "FL1", "LOOP1", true);
    def(MK56_FL2, "FL2", "LOOP2", true);
    def(MK56_FL3, "FL3", "LOOP3", true);

    def_reg(MK56_K_NE0, "Кx≠0", "JZ (%s)");
    def_reg(MK56_K_JMP, "КБП", "JMP (%s)");
    def_reg(MK56_K_GE0, "Кx≥0", "JLT (%s)");
    def_reg(MK56_K_CALL, "КПП", "CALL (%s)");
    def_reg(MK56_K_STO, "КП", "STO (%s)");  alias_add(MK56_K_STO, "Кx→П", true);
    def_reg(MK56_K_LT0, "Кx<0", "JGE (%s)");
    def_reg(MK56_K_RCL, "КИП", "RCL (%s)"); alias_add(MK56_K_RCL, "КП→x", true);
    def_reg(MK56_K_EQ0, "Кx=0", "JNZ (%s)");
}

/* ------------------------------------------------------------------------ */
/* Public API                                                               */
/* ------------------------------------------------------------------------ */

const Mk56Op *mk56_op(uint8_t code) {
    init();
    return &ops[code];
}

const char *mk56_reg_name(int reg) {
    return (reg >= 0 && reg < MK56_NUM_REGISTERS) ? REG_NAMES[reg] : "?";
}

int mk56_addr_decode(uint8_t step) {
    int hi = step >> 4, lo = step & 0x0F;
    if (hi > 9 || lo > 9) return -1;
    int addr = hi * 10 + lo;
    return addr < MK56_STEPS ? addr : -1;
}

uint8_t mk56_addr_encode(int addr) {
    return (uint8_t)(((addr / 10) << 4) | (addr % 10));
}

/* "3" -> 3, "a"/"а" -> 10, ... "d" -> 13 (canonical form). */
static int canon_reg(const char *c) {
    if (c[0] && !c[1]) {
        if (c[0] >= '0' && c[0] <= '9') return c[0] - '0';
        if (c[0] >= 'a' && c[0] <= 'd') return 10 + c[0] - 'a';
    }
    return -1;
}

static int match(const char *c, const char *next, int *consumed) {
    /* Exact spellings first, so "ПП" is not read as "П" + register "П". */
    for (int i = 0; i < alias_count; i++) {
        if (!aliases[i].reg_prefix && strcmp(aliases[i].canon, c) == 0) {
            *consumed = 1;
            return aliases[i].code;
        }
    }
    for (int i = 0; i < alias_count; i++) {
        if (!aliases[i].reg_prefix) continue;
        size_t n = strlen(aliases[i].canon);
        if (strncmp(aliases[i].canon, c, n) != 0) continue;
        if (c[n]) {
            int r = canon_reg(c + n);
            if (r >= 0) { *consumed = 1; return aliases[i].code + r; }
        } else if (next) {
            char nc[24];
            canon(next, nc, sizeof nc);
            int r = canon_reg(nc);
            if (r >= 0) { *consumed = 2; return aliases[i].code + r; }
        }
    }
    return -1;
}

int mk56_parse_key(char *const *tok, int n, int *consumed) {
    init();
    if (n < 1) return -1;
    const char *next = n > 1 ? tok[1] : NULL;
    char c[48];
    canon(tok[0], c, sizeof c);

    int code = match(c, next, consumed);
    if (code >= 0) return code;

    /* The F prefix is often omitted ("x≠0", "sin", "L0") */
    if (c[0] != 'f') {
        char f[52];
        snprintf(f, sizeof f, "f%s", c);
        code = match(f, next, consumed);
        if (code >= 0) return code;
    }

    /* ...or written as a separate token: "F √", "К НОП", "К ПП 7". */
    if ((strcmp(c, "f") == 0 || strcmp(c, "k") == 0) && next) {
        char joined[112], nc[48];
        canon(next, nc, sizeof nc);
        snprintf(joined, sizeof joined, "%s%s", c, nc);
        code = match(joined, n > 2 ? tok[2] : NULL, consumed);
        if (code >= 0) { *consumed += 1; return code; }
    }
    return -1;
}

int mk56_disasm(const uint8_t *program, int addr, bool asm_syntax,
                char *buf, size_t size) {
    const Mk56Op *op = mk56_op(program[addr]);
    const char *name = asm_syntax ? op->mnem : op->key;
    if (!op->has_addr) {
        snprintf(buf, size, "%s", name);
        return 1;
    }
    uint8_t step = program[(addr + 1) % MK56_STEPS];
    int target = mk56_addr_decode(step);
    if (target >= 0) snprintf(buf, size, "%s %02d", name, target);
    else snprintf(buf, size, "%s ?%02X", name, step);
    return 2;
}
