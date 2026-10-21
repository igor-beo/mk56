/**
 * MK56 Emulator - Core Implementation
 *
 * Semantics follow the original manual; page numbers below are the
 * manual's own (references/MK-56 inst.pdf). Behaviour the manual does not
 * describe is marked "inferred" and follows the Б3-34 family, whose
 * instruction set the МК-56 shares.
 */

#include "mk56emu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define X (vm->stack[0])
#define Y (vm->stack[1])

static const double MK56_PI_CONST = 3.1415926;     // the machine's π (p.27)

// ============================================================================
// HELPERS
// ============================================================================

static void set_error(MK56VM *vm, VMError err) {
    if (vm->error == ERR_NONE) vm->error = err;
}

/* Results keep 8 significant digits, truncated: 1/560 shows 1,7857142 -03
 * (p.29). Formatting to 12 digits first absorbs binary rounding noise, so
 * 0.3 stays 0.3 instead of truncating to 0.29999999. */
static double fix8(MK56VM *vm, double v) {
    if (isnan(v)) { set_error(vm, ERR_DOMAIN); return 0; }
    if (v == 0) return 0;
    if (isinf(v) || fabs(v) >= 1e100) { set_error(vm, ERR_OVERFLOW); return v; }

    char buf[32];
    snprintf(buf, sizeof buf, "%.11e", v);
    char *dot = strchr(buf, '.');
    char *exp = strchr(buf, 'e');
    if (dot && exp) memmove(dot + 8, exp, strlen(exp) + 1);
    double t = strtod(buf, NULL);

    if (fabs(t) >= 1e100) { set_error(vm, ERR_OVERFLOW); return t; }
    if (fabs(t) < 1e-99) { set_error(vm, ERR_UNDERFLOW); return 0; }
    return t;
}

/* Y←X, Z←Y, T←Z; X keeps its value until overwritten. */
static void lift_stack(MK56VM *vm) {
    vm->stack[3] = vm->stack[2];
    vm->stack[2] = vm->stack[1];
    vm->stack[1] = vm->stack[0];
}

/* Y←Z, Z←T; T keeps its value (p.39). */
static void drop_stack(MK56VM *vm) {
    vm->stack[1] = vm->stack[2];
    vm->stack[2] = vm->stack[3];
}

static double to_rad(const MK56VM *vm, double a) {
    switch (vm->angle) {
    case ANGLE_DEG:  return a * M_PI / 180.0;
    case ANGLE_GRAD: return a * M_PI / 200.0;
    default:         return a;
    }
}

static double from_rad(const MK56VM *vm, double a) {
    switch (vm->angle) {
    case ANGLE_DEG:  return a * 180.0 / M_PI;
    case ANGLE_GRAD: return a * 200.0 / M_PI;
    default:         return a;
    }
}

// ============================================================================
// NUMBER ENTRY (p.22-23)
// ============================================================================

static void entry_update_x(MK56VM *vm) {
    const NumberEntry *e = &vm->entry;
    char buf[40];
    snprintf(buf, sizeof buf, "%s%se%s%d", e->neg ? "-" : "",
             e->mant[0] ? e->mant : "0", e->exp_neg ? "-" : "", e->exp);
    X = strtod(buf, NULL);
}

static void entry_begin(MK56VM *vm) {
    if (vm->lift) lift_stack(vm);
    memset(&vm->entry, 0, sizeof vm->entry);
    vm->entry.active = true;
}

/* Any operation ends entry; the next digit then starts a new number
 * and lifts the stack. */
static void entry_end(MK56VM *vm) {
    if (vm->entry.active) {
        vm->entry.active = false;
        vm->lift = true;
        // A keyed number outside 1e-99..9,9999999e99 is ЕГГОГ (p.24)
        if (!vm_value_ok(X)) set_error(vm, ERR_OVERFLOW);
        else if (X != 0 && fabs(X) < 1e-99) set_error(vm, ERR_UNDERFLOW);
    }
}

static void key_digit(MK56VM *vm, int d) {
    NumberEntry *e = &vm->entry;
    if (!e->active) entry_begin(vm);
    if (e->exp_mode) {
        e->exp = (e->exp % 10) * 10 + d;    // older digit shifts out (p.23)
    } else {
        if (strcmp(e->mant, "0") == 0) { e->mant[0] = '\0'; e->digits = 0; }
        if (e->digits >= 8) return;         // 9th digit ignored (p.23)
        size_t n = strlen(e->mant);
        e->mant[n] = (char)('0' + d);
        e->mant[n + 1] = '\0';
        e->digits++;
    }
    entry_update_x(vm);
}

static void key_point(MK56VM *vm) {
    NumberEntry *e = &vm->entry;
    if (!e->active) entry_begin(vm);
    if (e->exp_mode || strchr(e->mant, '.')) return;
    if (!e->mant[0]) e->digits = 1;         // the leading 0 takes a position
    strcat(e->mant, e->mant[0] ? "." : "0.");
    entry_update_x(vm);
}

static void key_chs(MK56VM *vm) {
    NumberEntry *e = &vm->entry;
    if (!e->active) { X = -X; return; }
    if (e->exp_mode) e->exp_neg = !e->exp_neg;
    else e->neg = !e->neg;
    entry_update_x(vm);
}

static void key_eex(MK56VM *vm) {
    NumberEntry *e = &vm->entry;
    if (!e->active) entry_begin(vm);
    if (strtod(e->mant[0] ? e->mant : "0", NULL) == 0) {
        strcpy(e->mant, "1");               // ВП on 0 gives 1 (p.23)
        e->digits = 1;
    }
    e->exp_mode = true;
    entry_update_x(vm);
}

// ============================================================================
// OPERATIONS
// ============================================================================

/* One-operand op: X ← f(X), old X to X1 (p.25, p.38). */
static void unary(MK56VM *vm, double r) {
    vm->lastx = X;
    X = fix8(vm, r);
}

/* Two-operand op: X ← Y∘X, stack drops, old X to X1 (p.39). */
static void binary(MK56VM *vm, double r) {
    vm->lastx = X;
    drop_stack(vm);
    X = fix8(vm, r);
}

static void return_push(MK56VM *vm, uint8_t addr) {
    memmove(&vm->ret_stack[1], &vm->ret_stack[0], MK56_RETURN_DEPTH - 1);
    vm->ret_stack[0] = addr;
    if (vm->ret_depth < MK56_RETURN_DEPTH) vm->ret_depth++;
}

/* The return stack holds zeros when empty, so a stray В/О goes to 01
 * (inferred: Б3-34 family behaviour). */
static uint8_t return_pop(MK56VM *vm) {
    uint8_t addr = vm->ret_stack[0];
    memmove(&vm->ret_stack[0], &vm->ret_stack[1], MK56_RETURN_DEPTH - 1);
    vm->ret_stack[MK56_RETURN_DEPTH - 1] = 0;
    if (vm->ret_depth > 0) vm->ret_depth--;
    return addr;
}

/* Indirect addressing (p.67 §6.3.5): the register is modified first -
 * R0-R3 minus 1, R4-R6 plus 1, R7-Rd unchanged - and the new value is the
 * address or register number. Only the integer part is used (inferred,
 * Дьяконов p.22). */
static int indirect(MK56VM *vm, int r) {
    double v = trunc(vm->regs[r]);
    if (r <= 3) v -= 1;
    else if (r <= 6) v += 1;
    vm->regs[r] = v;
    return (v >= 0 && v < 1000) ? (int)v : -1;
}

/* Condition codes share their digit: Fx≠0 = 57, К x≠0 = 7n, etc. */
static bool condition(int code, double x) {
    switch (code) {
    case 0x7: return x != 0;    // x≠0
    case 0x9: return x >= 0;    // x≥0
    case 0xC: return x < 0;     // x<0
    default:  return x == 0;    // x=0
    }
}

static uint8_t wrap(int addr) {
    return (uint8_t)(addr % MK56_PROGRAM_SIZE);
}

static void jump(MK56VM *vm, int target) {
    if (target < 0 || target >= MK56_PROGRAM_SIZE) set_error(vm, ERR_BAD_ADDRESS);
    else vm->pc = (uint8_t)target;
}

static void execute(MK56VM *vm, uint8_t op) {
    uint8_t pc = vm->pc;
    int target = mk56_addr_decode(vm->program[wrap(pc + 1)]);
    double x = X, y = Y;

    vm->pc = wrap(pc + 1);

    if (op <= 0x09) { key_digit(vm, op); return; }
    if (op == MK56_POINT) { key_point(vm); return; }
    if (op == MK56_CHS) { key_chs(vm); return; }
    if (op == MK56_EEX) { key_eex(vm); return; }

    entry_end(vm);
    if (vm->error != ERR_NONE) return;
    x = X;

    int hi = op >> 4, lo = op & 0x0F;

    if (hi == 0x4) { vm->regs[lo] = x; vm->lift = true; return; }
    if (hi == 0x6) { lift_stack(vm); X = vm->regs[lo]; vm->lift = true; return; }

    if (hi >= 0x7) {                         // К-prefixed indirect ops
        int idx;
        switch (hi) {
        case 0x8:                            // К БП
            jump(vm, indirect(vm, lo));
            return;
        case 0xA:                            // К ПП
            return_push(vm, pc);
            jump(vm, indirect(vm, lo));
            return;
        /* A register number outside 0-13 is not an error: programs use
         * "Пn КИПn ИПn" to take the integer part of any number and discard
         * what КИПn loads (Дьяконов 3.1-3.4). Such stores are dropped and
         * loads give 0 (inferred). */
        case 0xB:                            // К x→П
            idx = indirect(vm, lo);
            if (idx >= 0 && idx < MK56_NUM_REGISTERS) vm->regs[idx] = x;
            vm->lift = true;
            return;
        case 0xD:                            // К П→x
            idx = indirect(vm, lo);
            lift_stack(vm);
            X = (idx >= 0 && idx < MK56_NUM_REGISTERS) ? vm->regs[idx] : 0;
            vm->lift = true;
            return;
        default:                             // К x?0: register untouched if it holds (p.70)
            if (!condition(hi, x))
                jump(vm, indirect(vm, lo));
            return;
        }
    }

    switch (op) {
    case MK56_CLX:   X = 0; vm->lift = false; return;
    case MK56_ENTER: lift_stack(vm); vm->lift = false; return;
    case MK56_LASTX: lift_stack(vm); X = vm->lastx; break;

    case MK56_ADD: binary(vm, y + x); break;
    case MK56_SUB: binary(vm, y - x); break;
    case MK56_MUL: binary(vm, y * x); break;
    case MK56_DIV:
        if (x == 0) { set_error(vm, ERR_DOMAIN); return; }
        binary(vm, y / x);
        break;
    case MK56_POW:                           // base X, exponent Y (p.28)
        if (x <= 0) { set_error(vm, ERR_DOMAIN); return; }
        binary(vm, pow(x, y));
        break;
    case MK56_SWAP: X = y; Y = x; break;

    case MK56_EXP10: unary(vm, pow(10.0, x)); break;
    case MK56_EXP:   unary(vm, exp(x)); break;
    case MK56_LOG:
    case MK56_LN:
        if (x <= 0) { set_error(vm, ERR_DOMAIN); return; }
        unary(vm, op == MK56_LOG ? log10(x) : log(x));
        break;
    case MK56_ASIN:
    case MK56_ACOS:
        if (fabs(x) > 1) { set_error(vm, ERR_DOMAIN); return; }
        unary(vm, from_rad(vm, op == MK56_ASIN ? asin(x) : acos(x)));
        break;
    case MK56_ATAN: unary(vm, from_rad(vm, atan(x))); break;
    case MK56_SIN:  unary(vm, sin(to_rad(vm, x))); break;
    case MK56_COS:  unary(vm, cos(to_rad(vm, x))); break;
    case MK56_TAN:  unary(vm, tan(to_rad(vm, x))); break;

    case MK56_PI:                            // also saves X to X1 (Дьяконов p.23)
        vm->lastx = x;
        lift_stack(vm);
        X = MK56_PI_CONST;
        break;
    case MK56_SQRT:
        if (x < 0) { set_error(vm, ERR_DOMAIN); return; }
        unary(vm, sqrt(x));
        break;
    case MK56_SQ:   unary(vm, x * x); break;
    case MK56_INV:
        if (x == 0) { set_error(vm, ERR_DOMAIN); return; }
        unary(vm, 1.0 / x);
        break;
    case MK56_ROT:                           // X→T, T→Z, Z→Y, Y→X; X to X1 (p.35)
        vm->lastx = x;
        X = y;
        Y = vm->stack[2];
        vm->stack[2] = vm->stack[3];
        vm->stack[3] = x;
        break;

    case MK56_HALT:
        vm->state = VM_HALTED;
        return;
    case MK56_JMP:
        jump(vm, target);
        return;
    case MK56_CALL:
        return_push(vm, wrap(pc + 1));
        jump(vm, target);
        return;
    case MK56_RTN:
        vm->pc = wrap(return_pop(vm) + 1);
        return;
    case MK56_NOP:
        return;

    /* Conditional jumps: fall through when the condition holds, jump
     * when it fails (p.65 §6.3.2). */
    case MK56_FX_NE0: case MK56_FX_GE0: case MK56_FX_LT0: case MK56_FX_EQ0:
        if (condition(lo, x)) vm->pc = wrap(pc + 2);
        else jump(vm, target);
        return;

    /* F Ln: Rn - 1; if not zero store it and jump, else fall through with
     * Rn left at 1. 0 - 1 shows -99999999 (p.82, functional test #92-93). */
    case MK56_FL0: case MK56_FL1: case MK56_FL2: case MK56_FL3: {
        int r = op == MK56_FL0 ? 0 : op == MK56_FL1 ? 1 : op == MK56_FL2 ? 2 : 3;
        double v = vm->regs[r] == 0 ? -99999999.0 : vm->regs[r] - 1;
        if (v != 0) { vm->regs[r] = v; jump(vm, target); }
        else vm->pc = wrap(pc + 2);
        return;
    }

    default:
        set_error(vm, ERR_INVALID_OPCODE);
        return;
    }
    vm->lift = true;
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
    memset(vm->program, 0, sizeof vm->program);
    memcpy(vm->program, data, size);
    vm->program_size = size;
    vm->state = VM_STOPPED;
    vm->pc = 0;
    return true;
}

bool vm_load_file(MK56VM *vm, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    uint8_t buf[MK56_PROGRAM_SIZE + 1];
    size_t n = fread(buf, 1, sizeof buf, f);
    fclose(f);
    return vm_load(vm, buf, n);
}

void vm_reset(MK56VM *vm) {
    AngleMode angle = vm->angle;
    uint8_t program[MK56_PROGRAM_SIZE];
    bool breakpoints[MK56_PROGRAM_SIZE];
    size_t size = vm->program_size;
    memcpy(program, vm->program, sizeof program);
    memcpy(breakpoints, vm->breakpoints, sizeof breakpoints);

    vm_init(vm);
    memcpy(vm->program, program, sizeof program);
    memcpy(vm->breakpoints, breakpoints, sizeof breakpoints);
    vm->program_size = size;
    vm->angle = angle;
}

// ============================================================================
// EXECUTION
// ============================================================================

/* After ЕГГОГ the stack is intact and С/П continues with the next step;
 * programs rely on this to report complex roots (Дьяконов 5.32). */
bool vm_step(MK56VM *vm) {
    vm->error = ERR_NONE;
    vm->state = VM_RUNNING;

    uint8_t op = vm->program[vm->pc];
    vm->last_opcode = op;
    vm->cycles++;

    double stack[MK56_STACK_SIZE], lastx = vm->lastx;
    memcpy(stack, vm->stack, sizeof stack);

    if (!mk56_op(op)->valid) set_error(vm, ERR_INVALID_OPCODE);
    else execute(vm, op);

    // Overflow leaves the stack as it was, like ÷0 does (inferred: the
    // machine cannot hold the result, and 5.32 relies on an intact stack)
    if (vm->error == ERR_OVERFLOW) {
        memcpy(vm->stack, stack, sizeof stack);
        vm->lastx = lastx;
    }

    // An error stops a running program (inferred: Дьяконов p.22)
    if (vm->error != ERR_NONE) {
        vm->state = VM_ERROR;
        return false;
    }
    if (vm->state == VM_HALTED) return false;
    vm->state = VM_STOPPED;
    return true;
}

void vm_run(MK56VM *vm) {
    for (long n = 0; n < MK56_STEP_LIMIT; n++) {
        if (n > 0 && vm->breakpoints[vm->pc]) return;
        if (!vm_step(vm)) return;
    }
    vm->error = ERR_STEP_LIMIT;
    vm->state = VM_STOPPED;
}

/* A number the calculator can hold: |x| < 10^100 (manual p.5). */
bool vm_value_ok(double value) {
    return isfinite(value) && fabs(value) < 1e100;
}

void vm_input(MK56VM *vm, double value) {
    if (!vm_value_ok(value)) {
        set_error(vm, ERR_OVERFLOW);
        vm->state = VM_ERROR;
        return;
    }
    if (vm->state == VM_ERROR) {
        vm->state = VM_STOPPED;
        vm->error = ERR_NONE;
    }
    entry_end(vm);
    if (vm->lift) lift_stack(vm);
    X = fix8(vm, value);
    vm->lift = true;
}

double vm_get_x(const MK56VM *vm) {
    return vm->stack[0];
}

double vm_get_stack(const MK56VM *vm, int idx) {
    return (idx >= 0 && idx < MK56_STACK_SIZE) ? vm->stack[idx] : 0;
}

double vm_get_reg(const MK56VM *vm, int idx) {
    return (idx >= 0 && idx < MK56_NUM_REGISTERS) ? vm->regs[idx] : 0;
}

void vm_set_breakpoint(MK56VM *vm, uint16_t addr, bool enabled) {
    if (addr < MK56_PROGRAM_SIZE) vm->breakpoints[addr] = enabled;
}

const char* vm_error_str(VMError err) {
    switch (err) {
    case ERR_NONE:           return "No error";
    case ERR_DOMAIN:         return "ЕГГОГ: invalid operation";
    case ERR_OVERFLOW:       return "ЕГГОГ: overflow";
    case ERR_UNDERFLOW:      return "ЕГГОГ: underflow";
    case ERR_INVALID_OPCODE: return "Undocumented opcode";
    case ERR_BAD_ADDRESS:    return "Jump outside 00-97";
    case ERR_STEP_LIMIT:     return "Step limit reached (endless loop?)";
    default:                 return "Unknown error";
    }
}

/* Natural form for 1 <= |x| < 10^8, otherwise mantissa and exponent;
 * trailing zeros dropped, decimal comma (manual p.21, p.26-28). */
void vm_format_display(const MK56VM *vm, char *buf, size_t size) {
    if (vm->state == VM_ERROR) { snprintf(buf, size, "ЕГГОГ"); return; }
    double x = vm->stack[0];
    if (!vm_value_ok(x)) { snprintf(buf, size, "ЕГГОГ"); return; }
    if (x == 0) { snprintf(buf, size, "0,"); return; }

    char e[32], digits[9];
    snprintf(e, sizeof e, "%.7e", fabs(x));     // "1.2566370e+01"
    digits[0] = e[0];
    memcpy(digits + 1, e + 2, 7);
    digits[8] = '\0';
    int exp = atoi(strchr(e, 'e') + 1);
    const char *sign = x < 0 ? "-" : "";

    if (exp >= 0 && exp <= 7) {
        char frac[9];
        snprintf(frac, sizeof frac, "%s", digits + exp + 1);
        for (int i = (int)strlen(frac) - 1; i >= 0 && frac[i] == '0'; i--) frac[i] = '\0';
        snprintf(buf, size, "%s%.*s,%s", sign, exp + 1, digits, frac);
    } else {
        for (int i = 7; i > 0 && digits[i] == '0'; i--) digits[i] = '\0';
        snprintf(buf, size, "%s%c,%s %s%02d", sign, digits[0], digits + 1,
                 exp < 0 ? "-" : "", abs(exp));
    }
}

int vm_disasm(const MK56VM *vm, uint16_t addr, char *buf, size_t buf_size) {
    return mk56_disasm(vm->program, addr % MK56_PROGRAM_SIZE, true, buf, buf_size);
}
