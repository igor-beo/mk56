/**
 * MK56 Emulator - Header
 * Emulates the Электроника МК-56 programmable calculator, following the
 * original manual (see common/mk56_isa.h for the instruction set).
 */

#ifndef MK56EMU_H
#define MK56EMU_H

#include "mk56_isa.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// ============================================================================
// CONSTANTS
// ============================================================================

#define MK56_PROGRAM_SIZE   MK56_STEPS  // 98 steps, addresses 00-97
#define MK56_STACK_SIZE     4           // X, Y, Z, T
#define MK56_RETURN_DEPTH   5           // manual p.56 §6.1.10
#define MK56_STEP_LIMIT     10000000    // vm_run gives up after this many steps

// ============================================================================
// VM STATE
// ============================================================================

typedef enum {
    VM_STOPPED,
    VM_RUNNING,
    VM_HALTED,
    VM_ERROR
} VMState;

typedef enum {
    ERR_NONE = 0,
    ERR_DOMAIN,             // ЕГГОГ: ÷0, √x<0, ln x≤0, |arcsin x|>1 ...
    ERR_OVERFLOW,           // ЕГГОГ: |x| > 9.9999999e99
    ERR_UNDERFLOW,          // ЕГГОГ: |x| < 1e-99, X set to 0 (manual p.24)
    ERR_INVALID_OPCODE,     // code not documented in the manual
    ERR_BAD_ADDRESS,        // jump target outside 00-97
    ERR_STEP_LIMIT          // vm_run stopped a program that never halts
} VMError;

typedef enum {
    ANGLE_RAD,              // Р
    ANGLE_DEG,              // Г
    ANGLE_GRAD              // ГРД
} AngleMode;

/** Number being keyed in (digits, decimal point, ВП exponent). */
typedef struct {
    bool active;
    char mant[12];          // up to 8 digits and a point
    int digits;
    bool neg;
    bool exp_mode;
    int exp;                // 0-99, the last two digits keyed
    bool exp_neg;
} NumberEntry;

typedef struct {
    // Stack (X=0, Y=1, Z=2, T=3)
    double stack[MK56_STACK_SIZE];
    double lastx;                       // X1, recalled by F Bx

    // Registers R0-R9, Ra-Rd
    double regs[MK56_NUM_REGISTERS];

    // Program memory
    uint8_t program[MK56_PROGRAM_SIZE];
    size_t program_size;                // steps loaded (memory is always 98)

    // Execution state
    uint8_t pc;
    uint8_t ret_stack[MK56_RETURN_DEPTH];
    int ret_depth;
    AngleMode angle;

    NumberEntry entry;
    bool lift;                          // next keyed digit lifts the stack

    VMState state;
    VMError error;

    // Statistics
    uint64_t cycles;
    int last_opcode;

    // Breakpoints
    bool breakpoints[MK56_PROGRAM_SIZE];

} MK56VM;

// ============================================================================
// API
// ============================================================================

/** Power on: everything zeroed, radians */
void vm_init(MK56VM *vm);

/** Load program from binary data (one byte per step, at most 98) */
bool vm_load(MK56VM *vm, const uint8_t *data, size_t size);

/** Load program from file */
bool vm_load_file(MK56VM *vm, const char *path);

/** Reset VM (keep program and angle mode) */
void vm_reset(MK56VM *vm);

/** Execute one program step (a jump and its address count as one) */
bool vm_step(MK56VM *vm);

/** Run until С/П, breakpoint, error or step limit */
void vm_run(MK56VM *vm);

/** Key a number into X, as the user does before pressing С/П */
void vm_input(MK56VM *vm, double value);

/** Get X register value */
double vm_get_x(const MK56VM *vm);

/** Get stack value */
double vm_get_stack(const MK56VM *vm, int idx);

/** Get register value */
double vm_get_reg(const MK56VM *vm, int idx);

/** Set breakpoint */
void vm_set_breakpoint(MK56VM *vm, uint16_t addr, bool enabled);

/** X as the calculator displays it: "12,56637", "3,3333333 -01", "ЕГГОГ" */
void vm_format_display(const MK56VM *vm, char *buf, size_t size);

/** Get error message */
const char* vm_error_str(VMError err);

/** Disassemble the step at addr in MK56-ASM syntax; returns 1 or 2 steps */
int vm_disasm(const MK56VM *vm, uint16_t addr, char *buf, size_t buf_size);

#endif // MK56EMU_H
