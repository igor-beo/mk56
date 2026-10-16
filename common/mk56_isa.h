/**
 * MK-56 instruction set - shared by the assembler, emulator and TUI.
 *
 * Codes are the real machine codes from the original manual
 * (references/MK-56 inst.pdf, Table 4, p.51-55). The full write-up with
 * page citations is docs/machine-reference.md.
 *
 * Every opcode has two spellings:
 *   key  - the original listing notation as printed in Soviet manuals
 *          and magazines (UTF-8), e.g. "ИП3", "FL1", "КБП3"
 *   mnem - the MK56-ASM mnemonic, e.g. "RCL R3", "LOOP1", "JMP (R3)"
 */

#ifndef MK56_ISA_H
#define MK56_ISA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MK56_STEPS          98      /* program memory: addresses 00-97 */
#define MK56_NUM_REGISTERS  14      /* R0-R9, Ra, Rb, Rc, Rd */

enum {
    MK56_POINT   = 0x0A, MK56_CHS    = 0x0B, MK56_EEX    = 0x0C,
    MK56_CLX     = 0x0D, MK56_ENTER  = 0x0E, MK56_LASTX  = 0x0F,
    MK56_ADD     = 0x10, MK56_SUB    = 0x11, MK56_MUL    = 0x12,
    MK56_DIV     = 0x13, MK56_SWAP   = 0x14, MK56_EXP10  = 0x15,
    MK56_EXP     = 0x16, MK56_LOG    = 0x17, MK56_LN     = 0x18,
    MK56_ASIN    = 0x19, MK56_ACOS   = 0x1A, MK56_ATAN   = 0x1B,
    MK56_SIN     = 0x1C, MK56_COS    = 0x1D, MK56_TAN    = 0x1E,
    MK56_PI      = 0x20, MK56_SQRT   = 0x21, MK56_SQ     = 0x22,
    MK56_INV     = 0x23, MK56_POW    = 0x24, MK56_ROT    = 0x25,
    MK56_STO     = 0x40,                    /* + register 0-13 */
    MK56_HALT    = 0x50, MK56_JMP    = 0x51, MK56_RTN    = 0x52,
    MK56_CALL    = 0x53, MK56_NOP    = 0x54,
    MK56_FX_NE0  = 0x57, MK56_FL2    = 0x58, MK56_FX_GE0 = 0x59,
    MK56_FL3     = 0x5A, MK56_FL1    = 0x5B, MK56_FX_LT0 = 0x5C,
    MK56_FL0     = 0x5D, MK56_FX_EQ0 = 0x5E,
    MK56_RCL     = 0x60,                    /* + register 0-13 */
    MK56_K_NE0   = 0x70,                    /* К-prefixed, + register */
    MK56_K_JMP   = 0x80,
    MK56_K_GE0   = 0x90,
    MK56_K_CALL  = 0xA0,
    MK56_K_STO   = 0xB0,
    MK56_K_LT0   = 0xC0,
    MK56_K_RCL   = 0xD0,
    MK56_K_EQ0   = 0xE0
};

typedef struct {
    bool valid;             /* documented in the manual (or 25 = F⟳) */
    bool has_addr;          /* followed by an address step */
    char key[24];           /* original notation, UTF-8 */
    char mnem[24];          /* MK56-ASM mnemonic */
} Mk56Op;

/** Opcode description. Never NULL. */
const Mk56Op *mk56_op(uint8_t code);

/** Register index 0-13 -> "0".."9", "a".."d". */
const char *mk56_reg_name(int reg);

/** Address step 0x42 -> 42. Returns -1 if not two decimal digits < 98. */
int mk56_addr_decode(uint8_t step);

/** Address 42 -> step 0x42. */
uint8_t mk56_addr_encode(int addr);

/**
 * Parse one step written in original listing notation, e.g. "ИП3",
 * "Fx≠0", "КБПa", "В/О". Accepts Cyrillic/Latin lookalikes, ASCII
 * spellings (Fx!=0, F1/x, Fsqrt) and prefixes or registers written as
 * separate tokens ("ИП 3", "П→x 3", "F √", "К ПП 7"). `tok` holds the
 * `n` remaining tokens of the line. Returns the code (0-255) and sets
 * *consumed to the number of tokens used, or returns -1.
 * The address step after БП/ПП/conditionals/loops is NOT consumed.
 */
int mk56_parse_key(char *const *tok, int n, int *consumed);

/**
 * Disassemble the step at `addr`. Writes "ИП3" / "БП 42" (asm == false)
 * or "RCL R3" / "JMP 42" (asm == true). Returns 1 or 2 steps.
 */
int mk56_disasm(const uint8_t *program, int addr, bool asm_syntax,
                char *buf, size_t size);

#endif /* MK56_ISA_H */
