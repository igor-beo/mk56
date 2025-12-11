/**
 * MK56 Emulator - Core Implementation
 */

#include "mk56emu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ============================================================================
// HELPERS
// ============================================================================

static void stack_push(MK56VM *vm, double val) {
    vm->stack[3] = vm->stack[2];  // T = Z
    vm->stack[2] = vm->stack[1];  // Z = Y
    vm->stack[1] = vm->stack[0];  // Y = X
    vm->stack[0] = val;           // X = val
}

static double stack_pop(MK56VM *vm) {
    double val = vm->stack[0];
    vm->stack[0] = vm->stack[1];  // X = Y
    vm->stack[1] = vm->stack[2];  // Y = Z
    vm->stack[2] = vm->stack[3];  // Z = T
    // T stays the same (standard RPN behavior)
    return val;
}

static void stack_drop(MK56VM *vm) {
    vm->stack[0] = vm->stack[1];
    vm->stack[1] = vm->stack[2];
    vm->stack[2] = vm->stack[3];
}

// ============================================================================
// INITIALIZATION
// ============================================================================

void vm_init(MK56VM *vm) {
    memset(vm, 0, sizeof(MK56VM));
    vm->state = VM_STOPPED;
}

bool vm_load(MK56VM *vm, const uint8_t *data, size_t size) {
    if (size > MK56_PROGRAM_SIZE) return false;
    memcpy(vm->program, data, size);
    vm->program_size = size;
    vm->state = VM_STOPPED;
    vm->pc = 0;
    return true;
}

bool vm_load_file(MK56VM *vm, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    if (size > MK56_PROGRAM_SIZE) {
        fclose(f);
        return false;
    }
    
    vm->program_size = fread(vm->program, 1, size, f);
    fclose(f);
    
    vm->state = VM_STOPPED;
    vm->pc = 0;
    return true;
}

void vm_reset(MK56VM *vm) {
    vm->pc = 0;
    vm->call_sp = 0;
    vm->state = VM_STOPPED;
    vm->error = ERR_NONE;
    vm->cycles = 0;
    memset(vm->stack, 0, sizeof(vm->stack));
    memset(vm->regs, 0, sizeof(vm->regs));
    vm->lastx = 0;
}

// ============================================================================
// EXECUTION
// ============================================================================

bool vm_step(MK56VM *vm) {
    if (vm->pc >= vm->program_size) {
        vm->state = VM_HALTED;
        return false;
    }
    
    if (vm->state == VM_ERROR) return false;
    
    vm->state = VM_RUNNING;
    
    uint8_t op = vm->program[vm->pc];
    vm->last_opcode = op;
    vm->cycles++;
    
    double x = vm->stack[0];
    double y = vm->stack[1];
    double result;
    
    // Decode and execute
    if (op == OP_LITERAL) {
        // Literal: next 8 bytes are double
        if (vm->pc + 9 > vm->program_size) {
            vm->error = ERR_PC_OVERFLOW;
            vm->state = VM_ERROR;
            return false;
        }
        double val;
        memcpy(&val, &vm->program[vm->pc + 1], sizeof(double));
        stack_push(vm, val);
        vm->pc += 9;
    }
    else if (op >= OP_STO && op < OP_STO + MK56_NUM_REGISTERS) {
        int reg = op - OP_STO;
        vm->regs[reg] = x;
        vm->pc++;
    }
    else if (op >= OP_RCL && op < OP_RCL + MK56_NUM_REGISTERS) {
        int reg = op - OP_RCL;
        stack_push(vm, vm->regs[reg]);
        vm->pc++;
    }
    else if (op >= OP_STO_ADD && op < OP_STO_ADD + MK56_NUM_REGISTERS) {
        int reg = op - OP_STO_ADD;
        vm->regs[reg] += x;
        vm->pc++;
    }
    else if (op >= OP_STO_SUB && op < OP_STO_SUB + MK56_NUM_REGISTERS) {
        int reg = op - OP_STO_SUB;
        vm->regs[reg] -= x;
        vm->pc++;
    }
    else {
        switch (op) {
            case OP_NOP:
                vm->pc++;
                break;
                
            case OP_ENTER:
                stack_push(vm, x);
                vm->pc++;
                break;
                
            case OP_SWAP:
                vm->stack[0] = y;
                vm->stack[1] = x;
                vm->pc++;
                break;
                
            case OP_CLX:
                vm->stack[0] = 0;
                vm->pc++;
                break;
                
            case OP_ROLLDOWN:
                result = vm->stack[0];
                vm->stack[0] = vm->stack[1];
                vm->stack[1] = vm->stack[2];
                vm->stack[2] = vm->stack[3];
                vm->stack[3] = result;
                vm->pc++;
                break;
                
            case OP_ROLLUP:
                result = vm->stack[3];
                vm->stack[3] = vm->stack[2];
                vm->stack[2] = vm->stack[1];
                vm->stack[1] = vm->stack[0];
                vm->stack[0] = result;
                vm->pc++;
                break;
                
            // Arithmetic
            case OP_ADD:
                vm->lastx = x;
                stack_drop(vm);
                vm->stack[0] = y + x;
                vm->pc++;
                break;
                
            case OP_SUB:
                vm->lastx = x;
                stack_drop(vm);
                vm->stack[0] = y - x;
                vm->pc++;
                break;
                
            case OP_MUL:
                vm->lastx = x;
                stack_drop(vm);
                vm->stack[0] = y * x;
                vm->pc++;
                break;
                
            case OP_DIV:
                if (x == 0) {
                    vm->error = ERR_DIV_ZERO;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->lastx = x;
                stack_drop(vm);
                vm->stack[0] = y / x;
                vm->pc++;
                break;
                
            case OP_CHS:
                vm->stack[0] = -x;
                vm->pc++;
                break;
                
            // Math functions
            case OP_SQ:
                vm->lastx = x;
                vm->stack[0] = x * x;
                vm->pc++;
                break;
                
            case OP_SQRT:
                if (x < 0) {
                    vm->error = ERR_SQRT_NEG;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->lastx = x;
                vm->stack[0] = sqrt(x);
                vm->pc++;
                break;
                
            case OP_INV:
                if (x == 0) {
                    vm->error = ERR_DIV_ZERO;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->lastx = x;
                vm->stack[0] = 1.0 / x;
                vm->pc++;
                break;
                
            case OP_POW:
                vm->lastx = x;
                stack_drop(vm);
                vm->stack[0] = pow(y, x);
                vm->pc++;
                break;
                
            case OP_EXP:
                vm->lastx = x;
                vm->stack[0] = exp(x);
                vm->pc++;
                break;
                
            case OP_EXP10:
                vm->lastx = x;
                vm->stack[0] = pow(10.0, x);
                vm->pc++;
                break;
                
            case OP_LN:
                if (x <= 0) {
                    vm->error = ERR_LOG_DOMAIN;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->lastx = x;
                vm->stack[0] = log(x);
                vm->pc++;
                break;
                
            case OP_LOG:
                if (x <= 0) {
                    vm->error = ERR_LOG_DOMAIN;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->lastx = x;
                vm->stack[0] = log10(x);
                vm->pc++;
                break;
                
            case OP_SIN:
                vm->lastx = x;
                vm->stack[0] = sin(x);
                vm->pc++;
                break;
                
            case OP_COS:
                vm->lastx = x;
                vm->stack[0] = cos(x);
                vm->pc++;
                break;
                
            case OP_PI:
                stack_push(vm, M_PI);
                vm->pc++;
                break;
                
            // Flow control
            case OP_JMP:
                vm->pc = vm->program[vm->pc + 1];
                break;
                
            case OP_JGE:
                if (x >= 0) {
                    vm->pc = vm->program[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                break;
                
            case OP_JLT:
                if (x < 0) {
                    vm->pc = vm->program[vm->pc + 1];
                } else {
                    vm->pc += 2;
                }
                break;
                
            case OP_CALL:
                if (vm->call_sp >= 16) {
                    vm->error = ERR_CALL_OVERFLOW;
                    vm->state = VM_ERROR;
                    return false;
                }
                vm->call_stack[vm->call_sp++] = vm->pc + 2;
                vm->pc = vm->program[vm->pc + 1];
                break;
                
            case OP_RTN:
                if (vm->call_sp <= 0) {
                    vm->state = VM_HALTED;
                    return false;
                }
                vm->pc = vm->call_stack[--vm->call_sp];
                break;
                
            case OP_HALT:
                vm->state = VM_HALTED;
                vm->pc++;
                return false;
                
            default:
                vm->error = ERR_INVALID_OPCODE;
                vm->state = VM_ERROR;
                return false;
        }
    }
    
    // Check for breakpoint
    if (vm->breakpoints[vm->pc]) {
        vm->state = VM_STOPPED;
        return false;
    }
    
    return true;
}

void vm_run(MK56VM *vm) {
    vm->state = VM_RUNNING;
    while (vm_step(vm)) {
        // Continue until halt/error/breakpoint
    }
}

void vm_input(MK56VM *vm, double value) {
    stack_push(vm, value);
}

double vm_get_x(const MK56VM *vm) {
    return vm->stack[0];
}

double vm_get_stack(const MK56VM *vm, int idx) {
    if (idx >= 0 && idx < MK56_STACK_SIZE) {
        return vm->stack[idx];
    }
    return 0;
}

double vm_get_reg(const MK56VM *vm, int idx) {
    if (idx >= 0 && idx < MK56_NUM_REGISTERS) {
        return vm->regs[idx];
    }
    return 0;
}

void vm_set_breakpoint(MK56VM *vm, uint16_t addr, bool enabled) {
    if (addr < MK56_PROGRAM_SIZE) {
        vm->breakpoints[addr] = enabled;
    }
}

const char* vm_error_str(VMError err) {
    static const char* msgs[] = {
        "No error",
        "Division by zero",
        "Square root of negative",
        "Logarithm domain error",
        "Overflow",
        "Stack underflow",
        "Invalid opcode",
        "Call stack overflow",
        "Program counter overflow"
    };
    return (err < sizeof(msgs)/sizeof(msgs[0])) ? msgs[err] : "Unknown error";
}

// ============================================================================
// DISASSEMBLER
// ============================================================================

int vm_disasm(const MK56VM *vm, uint16_t addr, char *buf, size_t buf_size) {
    if (addr >= vm->program_size) {
        snprintf(buf, buf_size, "???");
        return 0;
    }
    
    uint8_t op = vm->program[addr];
    int size = 1;
    
    if (op == OP_LITERAL) {
        double val;
        memcpy(&val, &vm->program[addr + 1], sizeof(double));
        snprintf(buf, buf_size, "PUSH %.8g", val);
        size = 9;
    }
    else if (op >= OP_STO && op < OP_STO + 14) {
        int reg = op - OP_STO;
        snprintf(buf, buf_size, "STO  R%X", reg);
    }
    else if (op >= OP_RCL && op < OP_RCL + 14) {
        int reg = op - OP_RCL;
        snprintf(buf, buf_size, "RCL  R%X", reg);
    }
    else if (op >= OP_STO_ADD && op < OP_STO_ADD + 14) {
        int reg = op - OP_STO_ADD;
        snprintf(buf, buf_size, "STO+ R%X", reg);
    }
    else if (op >= OP_STO_SUB && op < OP_STO_SUB + 14) {
        int reg = op - OP_STO_SUB;
        snprintf(buf, buf_size, "STO- R%X", reg);
    }
    else {
        switch (op) {
            case OP_NOP: snprintf(buf, buf_size, "NOP"); break;
            case OP_ENTER: snprintf(buf, buf_size, "ENTER"); break;
            case OP_SWAP: snprintf(buf, buf_size, "SWAP"); break;
            case OP_CLX: snprintf(buf, buf_size, "CLX"); break;
            case OP_ROLLDOWN: snprintf(buf, buf_size, "ROLL↓"); break;
            case OP_ROLLUP: snprintf(buf, buf_size, "ROLL↑"); break;
            case OP_ADD: snprintf(buf, buf_size, "ADD"); break;
            case OP_SUB: snprintf(buf, buf_size, "SUB"); break;
            case OP_MUL: snprintf(buf, buf_size, "MUL"); break;
            case OP_DIV: snprintf(buf, buf_size, "DIV"); break;
            case OP_CHS: snprintf(buf, buf_size, "CHS"); break;
            case OP_SQ: snprintf(buf, buf_size, "SQ"); break;
            case OP_SQRT: snprintf(buf, buf_size, "SQRT"); break;
            case OP_INV: snprintf(buf, buf_size, "INV"); break;
            case OP_POW: snprintf(buf, buf_size, "POW"); break;
            case OP_EXP: snprintf(buf, buf_size, "EXP"); break;
            case OP_EXP10: snprintf(buf, buf_size, "10^X"); break;
            case OP_LN: snprintf(buf, buf_size, "LN"); break;
            case OP_LOG: snprintf(buf, buf_size, "LOG"); break;
            case OP_SIN: snprintf(buf, buf_size, "SIN"); break;
            case OP_COS: snprintf(buf, buf_size, "COS"); break;
            case OP_PI: snprintf(buf, buf_size, "PI"); break;
            case OP_JMP:
                snprintf(buf, buf_size, "JMP  %03d", vm->program[addr + 1]);
                size = 2;
                break;
            case OP_JGE:
                snprintf(buf, buf_size, "JGE  %03d", vm->program[addr + 1]);
                size = 2;
                break;
            case OP_JLT:
                snprintf(buf, buf_size, "JLT  %03d", vm->program[addr + 1]);
                size = 2;
                break;
            case OP_CALL:
                snprintf(buf, buf_size, "CALL %03d", vm->program[addr + 1]);
                size = 2;
                break;
            case OP_RTN: snprintf(buf, buf_size, "RTN"); break;
            case OP_HALT: snprintf(buf, buf_size, "HALT"); break;
            default: snprintf(buf, buf_size, "??? %02X", op); break;
        }
    }
    
    return size;
}
