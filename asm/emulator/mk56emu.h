/**
 * MK56 Emulator - Header
 * Emulates the MK-56 programmable calculator
 */

#ifndef MK56EMU_H
#define MK56EMU_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// ============================================================================
// CONSTANTS
// ============================================================================

#define MK56_PROGRAM_SIZE   256     // Max program bytes
#define MK56_NUM_REGISTERS  14      // R0-R9, RA-RD
#define MK56_STACK_SIZE     4       // X, Y, Z, T

// ============================================================================
// OPCODES (must match assembler)
// ============================================================================

typedef enum {
    OP_NOP = 0x00, OP_ENTER = 0x01, OP_SWAP = 0x02, OP_CLX = 0x03,
    OP_ROLLDOWN = 0x04, OP_ROLLUP = 0x05,
    OP_ADD = 0x10, OP_SUB = 0x11, OP_MUL = 0x12, OP_DIV = 0x13, OP_CHS = 0x14,
    OP_SQ = 0x20, OP_SQRT = 0x21, OP_INV = 0x22, OP_POW = 0x23,
    OP_EXP = 0x24, OP_EXP10 = 0x25, OP_LN = 0x26, OP_LOG = 0x27,
    OP_SIN = 0x28, OP_COS = 0x29, OP_PI = 0x2A,
    OP_STO = 0x30, OP_RCL = 0x40, OP_STO_ADD = 0x50, OP_STO_SUB = 0x60,
    OP_JMP = 0x70, OP_JGE = 0x71, OP_JLT = 0x72,
    OP_CALL = 0x73, OP_RTN = 0x74, OP_HALT = 0x75,
    OP_LITERAL = 0x80
} Opcode;

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
    ERR_DIV_ZERO,
    ERR_SQRT_NEG,
    ERR_LOG_DOMAIN,
    ERR_OVERFLOW,
    ERR_STACK_UNDERFLOW,
    ERR_INVALID_OPCODE,
    ERR_CALL_OVERFLOW,
    ERR_PC_OVERFLOW
} VMError;

typedef struct {
    // Stack (X=0, Y=1, Z=2, T=3)
    double stack[MK56_STACK_SIZE];
    double lastx;                       // Last X value
    
    // Registers
    double regs[MK56_NUM_REGISTERS];
    
    // Program
    uint8_t program[MK56_PROGRAM_SIZE];
    size_t program_size;
    
    // Execution state
    uint16_t pc;                        // Program counter
    uint16_t call_stack[16];            // Return addresses
    int call_sp;                        // Call stack pointer
    
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

/** Initialize VM state */
void vm_init(MK56VM *vm);

/** Load program from binary data */
bool vm_load(MK56VM *vm, const uint8_t *data, size_t size);

/** Load program from file */
bool vm_load_file(MK56VM *vm, const char *path);

/** Reset VM (keep program) */
void vm_reset(MK56VM *vm);

/** Execute single instruction */
bool vm_step(MK56VM *vm);

/** Run until halt/breakpoint/error */
void vm_run(MK56VM *vm);

/** Set input value (push to X) */
void vm_input(MK56VM *vm, double value);

/** Get X register value */
double vm_get_x(const MK56VM *vm);

/** Get stack value */
double vm_get_stack(const MK56VM *vm, int idx);

/** Get register value */
double vm_get_reg(const MK56VM *vm, int idx);

/** Set breakpoint */
void vm_set_breakpoint(MK56VM *vm, uint16_t addr, bool enabled);

/** Get error message */
const char* vm_error_str(VMError err);

/** Disassemble instruction at address */
int vm_disasm(const MK56VM *vm, uint16_t addr, char *buf, size_t buf_size);

#endif // MK56EMU_H
