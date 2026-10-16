/**
 * MK56-ASM Assembler
 *
 * Two source syntaxes, both producing real MK-56 machine codes (one byte
 * per program step, see common/mk56_isa.h):
 *
 *   MK56-ASM     one instruction per line: "loop: RCL R0", "JLT done",
 *                "STO (R3)", number literals like "9.81" or "-1e-5"
 *   listing      original notation, many steps per line, as printed in
 *                Soviet manuals: "00: ИП0 Fx² 2 × С/П  БП 05". Selected by
 *                the .LISTING directive or asm_assemble_ex(..., true);
 *                the CLI uses it for *.mk56 files.
 */

#ifndef MK56ASM_H
#define MK56ASM_H

#include "mk56_isa.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define MK56_MAX_LABEL_LEN      64
#define MK56_MAX_LABELS         128
#define MK56_MAX_FIXUPS         128
#define MK56_MAX_LINES          512
#define MK56_MAX_LINE_LEN       256

typedef struct {
    char name[MK56_MAX_LABEL_LEN];
    int address;
} Label;

typedef struct {
    int address;                        // address step to patch
    char label[MK56_MAX_LABEL_LEN];
    int source_line;
} Fixup;

typedef struct {
    int address;                        // first step emitted by the line
    int steps;
    int source_line;
    char source_text[MK56_MAX_LINE_LEN];
} ListingLine;

typedef struct {
    uint8_t binary[MK56_STEPS];
    size_t binary_size;                 // highest address used + 1
    int current_address;
    bool listing_syntax;

    Label labels[MK56_MAX_LABELS];
    size_t label_count;
    Fixup fixups[MK56_MAX_FIXUPS];
    size_t fixup_count;
    ListingLine lines[MK56_MAX_LINES];
    size_t line_count;

    char error_msg[256];
    int error_line;
    bool has_error;
} Assembler;

/** Initialize assembler state */
void asm_init(Assembler *as);

/** Assemble MK56-ASM source (a .LISTING directive switches syntax) */
bool asm_assemble(Assembler *as, const char *source);

/** Assemble, starting in listing syntax if `listing` is true */
bool asm_assemble_ex(Assembler *as, const char *source, bool listing);

/**
 * Encode one statement without labels - MK56-ASM ("RCL R3", "JMP 12")
 * or listing notation ("ИП3", "БП 12") - into at most `max` steps.
 * Returns the number of steps, or -1 with a message in `err`.
 */
int asm_encode_line(const char *line, uint8_t *out, size_t max,
                    char *err, size_t err_size);

/** Get binary output (one byte per step) */
const uint8_t* asm_get_binary(const Assembler *as, size_t *out_size);

/** Listing: address, codes, original notation, source line */
size_t asm_get_listing(const Assembler *as, char *buffer, size_t buffer_size);

/** Get error message, or NULL if no error */
const char* asm_get_error(const Assembler *as);

#endif // MK56ASM_H
