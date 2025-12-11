/**
 * MK56-ASM Assembler
 * Header file with opcodes, data structures, and API
 */

#ifndef MK56ASM_H
#define MK56ASM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// ============================================================================
// CONSTANTS
// ============================================================================

#define MK56_MAX_PROGRAM_SIZE   105
#define MK56_MAX_REGISTERS      14
#define MK56_MAX_LABEL_LEN      64
#define MK56_MAX_LABELS         128
#define MK56_MAX_LINE_LEN       256
#define MK56_MAX_INSTRUCTIONS   256

// ============================================================================
// OPCODES
// ============================================================================

typedef enum {
    // Stack operations (0x00-0x0F)
    OP_NOP      = 0x00,
    OP_ENTER    = 0x01,
    OP_SWAP     = 0x02,
    OP_CLX      = 0x03,
    OP_ROLLDOWN = 0x04,
    OP_ROLLUP   = 0x05,
    
    // Arithmetic (0x10-0x1F)
    OP_ADD      = 0x10,
    OP_SUB      = 0x11,
    OP_MUL      = 0x12,
    OP_DIV      = 0x13,
    OP_CHS      = 0x14,
    
    // Math functions (0x20-0x2F)
    OP_SQ       = 0x20,
    OP_SQRT     = 0x21,
    OP_INV      = 0x22,
    OP_POW      = 0x23,
    OP_EXP      = 0x24,
    OP_EXP10    = 0x25,
    OP_LN       = 0x26,
    OP_LOG      = 0x27,
    OP_SIN      = 0x28,
    OP_COS      = 0x29,
    OP_PI       = 0x2A,
    
    // Memory operations (0x30-0x6F)
    OP_STO      = 0x30,     // + register (0-13)
    OP_RCL      = 0x40,     // + register (0-13)
    OP_STO_ADD  = 0x50,     // + register
    OP_STO_SUB  = 0x60,     // + register
    
    // Flow control (0x70-0x7F)
    OP_JMP      = 0x70,
    OP_JGE      = 0x71,
    OP_JLT      = 0x72,
    OP_CALL     = 0x73,
    OP_RTN      = 0x74,
    OP_HALT     = 0x75,
    
    // Literals (0x80)
    OP_LITERAL  = 0x80      // Followed by 8-byte double
} Opcode;

// ============================================================================
// OPERAND TYPES
// ============================================================================

typedef enum {
    OPERAND_NONE,
    OPERAND_REG,
    OPERAND_ADDR,
    OPERAND_LITERAL
} OperandType;

// ============================================================================
// DATA STRUCTURES
// ============================================================================

typedef struct {
    char name[16];
    Opcode opcode;
    OperandType operand_type;
} InstructionDef;

typedef struct {
    char name[MK56_MAX_LABEL_LEN];
    uint16_t address;
} Label;

typedef struct {
    uint16_t address;
    Opcode opcode;
    OperandType operand_type;
    union {
        int reg_num;
        uint16_t addr;
        double literal;
        char label_ref[MK56_MAX_LABEL_LEN];
    } operand;
    bool operand_is_label;
    int source_line;
    char source_text[MK56_MAX_LINE_LEN];
} Instruction;

typedef struct {
    Instruction instructions[MK56_MAX_INSTRUCTIONS];
    size_t instruction_count;
    
    Label labels[MK56_MAX_LABELS];
    size_t label_count;
    
    uint8_t binary[MK56_MAX_INSTRUCTIONS * 10];  // Max size with literals
    size_t binary_size;
    
    uint16_t current_address;
    uint16_t origin;
    
    char error_msg[256];
    int error_line;
    bool has_error;
} Assembler;

// ============================================================================
// API FUNCTIONS
// ============================================================================

/**
 * Initialize assembler state
 */
void asm_init(Assembler *as);

/**
 * Assemble source code
 * @param as Assembler state
 * @param source Source code string
 * @return true on success, false on error
 */
bool asm_assemble(Assembler *as, const char *source);

/**
 * Get binary output
 * @param as Assembler state
 * @param out_size Output size in bytes
 * @return Pointer to binary data
 */
const uint8_t* asm_get_binary(const Assembler *as, size_t *out_size);

/**
 * Generate listing
 * @param as Assembler state
 * @param buffer Output buffer
 * @param buffer_size Buffer size
 * @return Length of listing
 */
size_t asm_get_listing(const Assembler *as, char *buffer, size_t buffer_size);

/**
 * Get error message
 * @param as Assembler state
 * @return Error message or NULL if no error
 */
const char* asm_get_error(const Assembler *as);

#endif // MK56ASM_H
