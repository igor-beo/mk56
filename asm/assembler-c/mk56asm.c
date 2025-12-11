/**
 * MK56-ASM Assembler - Modern C Implementation
 * Build: gcc -O2 -Wall -std=c11 -o mk56asm mk56asm.c main.c -lm
 */

#include "mk56asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// INSTRUCTION TABLE
// ============================================================================

static const InstructionDef INSTR_TABLE[] = {
    {"NOP", OP_NOP, OPERAND_NONE}, {"ENTER", OP_ENTER, OPERAND_NONE},
    {"SWAP", OP_SWAP, OPERAND_NONE}, {"CLX", OP_CLX, OPERAND_NONE},
    {"ROLLDOWN", OP_ROLLDOWN, OPERAND_NONE}, {"ROLLUP", OP_ROLLUP, OPERAND_NONE},
    {"ADD", OP_ADD, OPERAND_NONE}, {"SUB", OP_SUB, OPERAND_NONE},
    {"MUL", OP_MUL, OPERAND_NONE}, {"DIV", OP_DIV, OPERAND_NONE},
    {"CHS", OP_CHS, OPERAND_NONE}, {"SQ", OP_SQ, OPERAND_NONE},
    {"SQRT", OP_SQRT, OPERAND_NONE}, {"INV", OP_INV, OPERAND_NONE},
    {"POW", OP_POW, OPERAND_NONE}, {"EXP", OP_EXP, OPERAND_NONE},
    {"EXP10", OP_EXP10, OPERAND_NONE}, {"LN", OP_LN, OPERAND_NONE},
    {"LOG", OP_LOG, OPERAND_NONE}, {"SIN", OP_SIN, OPERAND_NONE},
    {"COS", OP_COS, OPERAND_NONE}, {"PI", OP_PI, OPERAND_NONE},
    {"STO", OP_STO, OPERAND_REG}, {"RCL", OP_RCL, OPERAND_REG},
    {"STO+", OP_STO_ADD, OPERAND_REG}, {"STO-", OP_STO_SUB, OPERAND_REG},
    {"JMP", OP_JMP, OPERAND_ADDR}, {"GOTO", OP_JMP, OPERAND_ADDR},
    {"JGE", OP_JGE, OPERAND_ADDR}, {"JLT", OP_JLT, OPERAND_ADDR},
    {"CALL", OP_CALL, OPERAND_ADDR}, {"RTN", OP_RTN, OPERAND_NONE},
    {"RETURN", OP_RTN, OPERAND_NONE}, {"HALT", OP_HALT, OPERAND_NONE},
    {"STOP", OP_HALT, OPERAND_NONE}, {"", 0, 0}
};

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

static void str_upper(char *s) {
    for (; *s; s++) *s = toupper((unsigned char)*s);
}

static void set_error(Assembler *as, int line, const char *msg) {
    as->has_error = true;
    as->error_line = line;
    snprintf(as->error_msg, sizeof(as->error_msg), "Line %d: %s", line, msg);
}

static const InstructionDef* find_instruction(const char *name) {
    char upper[32];
    strncpy(upper, name, sizeof(upper) - 1);
    upper[sizeof(upper) - 1] = '\0';
    str_upper(upper);
    
    for (const InstructionDef *def = INSTR_TABLE; def->name[0]; def++) {
        if (strcmp(def->name, upper) == 0) return def;
    }
    return NULL;
}

static int parse_register(const char *name) {
    char upper[8];
    strncpy(upper, name, sizeof(upper) - 1);
    upper[sizeof(upper) - 1] = '\0';
    str_upper(upper);
    
    if (upper[0] == 'R' && strlen(upper) == 2) {
        char c = upper[1];
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'D') return 10 + (c - 'A');
    }
    return -1;
}

static int find_label(const Assembler *as, const char *name) {
    for (size_t i = 0; i < as->label_count; i++) {
        if (strcasecmp(as->labels[i].name, name) == 0) {
            return (int)as->labels[i].address;
        }
    }
    return -1;
}

static bool add_label(Assembler *as, const char *name, uint16_t addr, int line) {
    if (as->label_count >= MK56_MAX_LABELS) {
        set_error(as, line, "Too many labels");
        return false;
    }
    if (find_label(as, name) >= 0) {
        set_error(as, line, "Duplicate label");
        return false;
    }
    Label *lbl = &as->labels[as->label_count++];
    strncpy(lbl->name, name, MK56_MAX_LABEL_LEN - 1);
    lbl->address = addr;
    return true;
}

static char* skip_whitespace(char *p) {
    while (*p && (*p == ' ' || *p == '\t')) p++;
    return p;
}

static char* parse_token(char *p, char *token, size_t max_len) {
    p = skip_whitespace(p);
    size_t i = 0;
    while (*p && *p != ' ' && *p != '\t' && *p != ';' && *p != ':' && i < max_len - 1) {
        token[i++] = *p++;
    }
    token[i] = '\0';
    return p;
}

// ============================================================================
// INSTRUCTION SIZE CALCULATION
// ============================================================================

static int get_instruction_size(Opcode op, OperandType operand_type) {
    if (op == OP_LITERAL) return 9;  // opcode + 8-byte double
    if (operand_type == OPERAND_ADDR) return 2;  // opcode + address byte
    return 1;  // simple opcode (including reg ops which encode reg in opcode)
}

// ============================================================================
// PARSER
// ============================================================================

static bool parse_line(Assembler *as, char *line, int line_num) {
    char *p = line;
    char token[MK56_MAX_LABEL_LEN];
    
    // Remove comments
    char *comment = strchr(line, ';');
    if (comment) *comment = '\0';
    comment = strstr(line, "//");
    if (comment) *comment = '\0';
    
    p = skip_whitespace(p);
    if (!*p) return true;  // Empty line
    
    // Check for label definition
    char *colon = strchr(p, ':');
    if (colon && colon > p) {
        size_t label_len = colon - p;
        if (label_len < MK56_MAX_LABEL_LEN) {
            strncpy(token, p, label_len);
            token[label_len] = '\0';
            // Verify it's a valid identifier
            if (isalpha((unsigned char)token[0]) || token[0] == '_') {
                // Labels point to current BYTE address
                if (!add_label(as, token, as->current_address, line_num)) {
                    return false;
                }
            }
        }
        p = colon + 1;
        p = skip_whitespace(p);
        if (!*p) return true;  // Label-only line
    }
    
    // Check for directive
    if (*p == '.') {
        p++;
        p = parse_token(p, token, sizeof(token));
        str_upper(token);
        
        if (strcmp(token, "ORG") == 0) {
            p = parse_token(p, token, sizeof(token));
            as->current_address = (uint16_t)atoi(token);
            as->origin = as->current_address;
        } else if (strcmp(token, "END") == 0) {
            // End of program
        } else if (strcmp(token, "EQU") == 0 || strcmp(token, "ASSERT") == 0 ||
                   strcmp(token, "TRACE") == 0 || strcmp(token, "BREAK") == 0) {
            // Ignore for now
        }
        return true;
    }
    
    // Parse instruction or number
    p = parse_token(p, token, sizeof(token));
    if (!token[0]) return true;
    
    // Check if it's a number literal
    char *endptr;
    double num = strtod(token, &endptr);
    if (*endptr == '\0' && token[0] != '\0') {
        // It's a number
        if (as->instruction_count >= MK56_MAX_INSTRUCTIONS) {
            set_error(as, line_num, "Too many instructions");
            return false;
        }
        Instruction *instr = &as->instructions[as->instruction_count++];
        instr->address = as->current_address;
        instr->opcode = OP_LITERAL;
        instr->operand_type = OPERAND_LITERAL;
        instr->operand.literal = num;
        instr->operand_is_label = false;
        instr->source_line = line_num;
        strncpy(instr->source_text, line, MK56_MAX_LINE_LEN - 1);
        as->current_address += get_instruction_size(OP_LITERAL, OPERAND_LITERAL);
        return true;
    }
    
    // Look up instruction
    const InstructionDef *def = find_instruction(token);
    if (!def) {
        char msg[128];
        snprintf(msg, sizeof(msg), "Unknown instruction: %s", token);
        set_error(as, line_num, msg);
        return false;
    }
    
    if (as->instruction_count >= MK56_MAX_INSTRUCTIONS) {
        set_error(as, line_num, "Too many instructions");
        return false;
    }
    
    Instruction *instr = &as->instructions[as->instruction_count++];
    instr->address = as->current_address;
    instr->opcode = def->opcode;
    instr->operand_type = def->operand_type;
    instr->operand_is_label = false;
    instr->source_line = line_num;
    strncpy(instr->source_text, line, MK56_MAX_LINE_LEN - 1);
    
    // Parse operand if needed
    if (def->operand_type == OPERAND_REG) {
        p = parse_token(p, token, sizeof(token));
        int reg = parse_register(token);
        if (reg < 0) {
            set_error(as, line_num, "Invalid register");
            return false;
        }
        instr->operand.reg_num = reg;
    } else if (def->operand_type == OPERAND_ADDR) {
        p = parse_token(p, token, sizeof(token));
        char *end;
        long addr = strtol(token, &end, 10);
        if (*end == '\0' && token[0] != '\0') {
            instr->operand.addr = (uint16_t)addr;
        } else {
            // It's a label reference
            strncpy(instr->operand.label_ref, token, MK56_MAX_LABEL_LEN - 1);
            instr->operand_is_label = true;
        }
    }
    
    // Advance address by instruction size
    as->current_address += get_instruction_size(def->opcode, def->operand_type);
    
    return true;
}

// ============================================================================
// CODE GENERATION
// ============================================================================

static bool resolve_labels(Assembler *as) {
    for (size_t i = 0; i < as->instruction_count; i++) {
        Instruction *instr = &as->instructions[i];
        if (instr->operand_is_label) {
            int addr = find_label(as, instr->operand.label_ref);
            if (addr < 0) {
                char msg[128];
                snprintf(msg, sizeof(msg), "Undefined label: %s", instr->operand.label_ref);
                set_error(as, instr->source_line, msg);
                return false;
            }
            instr->operand.addr = (uint16_t)addr;
            instr->operand_is_label = false;
        }
    }
    return true;
}

static bool generate_binary(Assembler *as) {
    as->binary_size = 0;
    
    for (size_t i = 0; i < as->instruction_count; i++) {
        Instruction *instr = &as->instructions[i];
        
        if (instr->opcode == OP_LITERAL) {
            // Literal: opcode + 8-byte double (little-endian)
            as->binary[as->binary_size++] = OP_LITERAL;
            double val = instr->operand.literal;
            memcpy(&as->binary[as->binary_size], &val, sizeof(double));
            as->binary_size += sizeof(double);
        } else if (instr->operand_type == OPERAND_REG) {
            // Register op: opcode + register in one byte
            as->binary[as->binary_size++] = instr->opcode + instr->operand.reg_num;
        } else if (instr->operand_type == OPERAND_ADDR) {
            // Address op: opcode + 1-byte address
            as->binary[as->binary_size++] = instr->opcode;
            as->binary[as->binary_size++] = (uint8_t)instr->operand.addr;
        } else {
            // Simple opcode
            as->binary[as->binary_size++] = instr->opcode;
        }
    }
    
    return true;
}

// ============================================================================
// PUBLIC API
// ============================================================================

void asm_init(Assembler *as) {
    memset(as, 0, sizeof(Assembler));
}

bool asm_assemble(Assembler *as, const char *source) {
    asm_init(as);
    
    // Copy source and parse line by line
    char *src_copy = strdup(source);
    if (!src_copy) {
        set_error(as, 0, "Out of memory");
        return false;
    }
    
    char *line = src_copy;
    int line_num = 1;
    
    while (line) {
        char *next = strchr(line, '\n');
        if (next) *next++ = '\0';
        
        if (!parse_line(as, line, line_num)) {
            free(src_copy);
            return false;
        }
        
        line = next;
        line_num++;
    }
    
    free(src_copy);
    
    // Second pass: resolve labels
    if (!resolve_labels(as)) return false;
    
    // Generate binary
    if (!generate_binary(as)) return false;
    
    return true;
}

const uint8_t* asm_get_binary(const Assembler *as, size_t *out_size) {
    if (out_size) *out_size = as->binary_size;
    return as->binary;
}

size_t asm_get_listing(const Assembler *as, char *buffer, size_t buffer_size) {
    size_t offset = 0;
    offset += snprintf(buffer + offset, buffer_size - offset,
        "ADDR  BYTES                 SOURCE\n"
        "======================================================================\n");
    
    size_t bin_offset = 0;
    for (size_t i = 0; i < as->instruction_count && offset < buffer_size - 100; i++) {
        const Instruction *instr = &as->instructions[i];
        
        // Calculate instruction size
        size_t instr_size = 1;
        if (instr->opcode == OP_LITERAL) instr_size = 9;
        else if (instr->operand_type == OPERAND_ADDR) instr_size = 2;
        
        // Format bytes
        char bytes_str[32] = "";
        size_t bs = 0;
        for (size_t j = 0; j < instr_size && j < 8; j++) {
            bs += snprintf(bytes_str + bs, sizeof(bytes_str) - bs, "%02X ", as->binary[bin_offset + j]);
        }
        bin_offset += instr_size;
        
        offset += snprintf(buffer + offset, buffer_size - offset,
            "%03d  %-20s  %s\n", instr->address, bytes_str, instr->source_text);
    }
    
    return offset;
}

const char* asm_get_error(const Assembler *as) {
    return as->has_error ? as->error_msg : NULL;
}
