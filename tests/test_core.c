/**
 * MK-56 emulator core tests.
 *
 * Programs are raw machine codes as printed in the original manual
 * (references/MK-56 inst.pdf). Page numbers refer to the manual's own
 * numbering, not the PDF page.
 */

#include "mk56emu.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

static int failures = 0;
static int checks = 0;

#define CHECK_NUM(name, got, want) do {                                     \
    double g_ = (got), w_ = (want);                                         \
    checks++;                                                               \
    if (!(fabs(g_ - w_) <= 1e-7 * fmax(1.0, fabs(w_)))) {                   \
        failures++;                                                         \
        printf("  FAIL %s: got %.10g, want %.10g\n", name, g_, w_);         \
    }                                                                       \
} while (0)

#define CHECK_TRUE(name, cond) do {                                         \
    checks++;                                                               \
    if (!(cond)) { failures++; printf("  FAIL %s\n", name); }               \
} while (0)

static void load(MK56VM *vm, const uint8_t *code, size_t n) {
    vm_init(vm);
    vm_load(vm, code, n);
}

static void run(MK56VM *vm) {
    vm->pc = 0;
    vm_run(vm);
}

/* Manual p.68-69, table 9: indirect jumps К БП 3 / К БП 4 / К БП а
 * compute (4 + 2) * 3. R3 is decremented, R4 incremented, Ra unchanged. */
static void test_indirect_jumps_table9(void) {
    static const uint8_t code[] = {
        0x04, 0x0E, 0x83, 0x21, 0x02, 0x10, 0x84,
        0x10, 0x03, 0x12, 0x8A, 0x11, 0x50
    };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm.regs[3] = 5;
    vm.regs[4] = 7;
    vm.regs[10] = 12;
    run(&vm);
    puts("table 9: indirect jumps");
    CHECK_TRUE("halted", vm.state == VM_HALTED);
    CHECK_NUM("X", vm_get_x(&vm), 18);
    CHECK_NUM("R3 decremented", vm_get_reg(&vm, 3), 4);
    CHECK_NUM("R4 incremented", vm_get_reg(&vm, 4), 8);
    CHECK_NUM("Ra unchanged", vm_get_reg(&vm, 10), 12);
}

/* Manual p.65 §6.3.2: if the condition holds, execution falls through;
 * if it fails, execution jumps to the address after the command.
 *   00 F x?0  04 / 02 1 / 03 С/П / 04 2 / 05 С/П
 * -> result 1 when the condition holds, 2 when it fails. */
static double run_conditional(uint8_t op, double x) {
    const uint8_t code[] = { op, 0x04, 0x01, 0x50, 0x02, 0x50 };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm_input(&vm, x);
    run(&vm);
    return vm_get_x(&vm);
}

static void test_conditionals(void) {
    puts("conditional jumps (p.65)");
    CHECK_NUM("Fx=0 holds",  run_conditional(0x5E, 0),  1);
    CHECK_NUM("Fx=0 fails",  run_conditional(0x5E, 5),  2);
    CHECK_NUM("Fx!=0 holds", run_conditional(0x57, 5),  1);
    CHECK_NUM("Fx!=0 fails", run_conditional(0x57, 0),  2);
    CHECK_NUM("Fx<0 holds",  run_conditional(0x5C, -3), 1);
    CHECK_NUM("Fx<0 fails",  run_conditional(0x5C, 3),  2);
    CHECK_NUM("Fx>=0 holds", run_conditional(0x59, 0),  1);
    CHECK_NUM("Fx>=0 fails", run_conditional(0x59, -3), 2);
}

/* Manual p.66-67, table 8: ПП (53) calls, В/О (52) returns.
 *   00 3 / 01 ПП 05 / 03 С/П / 04 НОП / 05 Fx² / 06 В/О */
static void test_subroutine_table8(void) {
    static const uint8_t code[] = { 0x03, 0x53, 0x05, 0x50, 0x54, 0x22, 0x52 };
    MK56VM vm;
    load(&vm, code, sizeof code);
    run(&vm);
    puts("table 8: ПП / В/О");
    CHECK_TRUE("halted", vm.state == VM_HALTED);
    CHECK_NUM("X = 3^2", vm_get_x(&vm), 9);
    CHECK_NUM("stopped after С/П at 03", vm.pc, 4);
}

/* Multi-digit entry: consecutive digit codes build one number. */
static void test_number_entry(void) {
    static const uint8_t code[] = { 0x01, 0x02, 0x0E, 0x03, 0x10, 0x50 };
    MK56VM vm;
    load(&vm, code, sizeof code);
    run(&vm);
    puts("number entry");
    CHECK_NUM("12 В↑ 3 + = 15", vm_get_x(&vm), 15);
}

/* FL0 nn: decrement R0, jump to nn while it is not zero.
 * Sums R0 + (R0-1) + ... + 1 into Rd. */
static void test_loop_fl0(void) {
    static const uint8_t code[] = {
        0x00, 0x4D, 0x6D, 0x60, 0x10, 0x4D, 0x5D, 0x02, 0x6D, 0x50
    };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm.regs[0] = 5;
    run(&vm);
    puts("FL0 loop");
    CHECK_NUM("sum 1..5", vm_get_x(&vm), 15);
}

/* Transcendental results on the real machine differ from IEEE values in
 * the last digits (manual Table 1 allows up to 5e-6 relative error). */
#define CHECK_APPROX(name, got, want) do {                                  \
    double g_ = (got), w_ = (want);                                         \
    checks++;                                                               \
    if (!(fabs(g_ - w_) <= 1e-5 * fmax(1.0, fabs(w_)))) {                   \
        failures++;                                                         \
        printf("  FAIL %s: got %.10g, want %.10g\n", name, g_, w_);         \
    }                                                                       \
} while (0)

static void run_from(MK56VM *vm, int addr) {
    vm->pc = (uint8_t)addr;
    vm_run(vm);
}

/* Manual p.58, table 5: circle area πd²/4, d in R2. Exact printed digits
 * (8-digit truncating arithmetic, π = 3,1415926). */
static void test_circle_table5(void) {
    static const uint8_t code[] = { 0x62, 0x22, 0x0E, 0x20, 0x12, 0x04, 0x13, 0x50 };
    MK56VM vm;
    puts("table 5: circle area");
    const double d[] = { 4, 5, 1.8 }, want[] = { 12.56637, 19.634953, 2.54469 };
    for (int i = 0; i < 3; i++) {
        load(&vm, code, sizeof code);
        vm.regs[2] = d[i];
        run(&vm);
        CHECK_NUM("S", vm_get_x(&vm), want[i]);
    }
}

/* Manual p.71-73, table 10: y = -9x² + e^2x, then + sin x or + tg x
 * chosen by К x<0 в. Printed values are hardware digits. */
static void test_branch_table10(void) {
    static const uint8_t code[] = {
        0x01, 0x09, 0x4B, 0x09, 0x61, 0x22, 0x12, 0x42, 0x61, 0x02, 0x12,
        0x16, 0x62, 0x11, 0xCB, 0x61, 0x1E, 0x10, 0x50, 0x61, 0x1C, 0x10, 0x50
    };
    const double want[] = { -5.35365e-02, 19.507444, 322.56986, 2836.2007 };
    MK56VM vm;
    puts("table 10: К x<0 branch");
    for (int x = 1; x <= 4; x++) {
        load(&vm, code, sizeof code);
        vm.regs[1] = x;
        run(&vm);
        CHECK_APPROX("y", vm_get_x(&vm), want[x - 1]);
    }
}

/* Manual p.74-75, table 11: quadratic equation through К ПП 7. */
static void test_quadratic_table11(void) {
    static const uint8_t code[] = {
        0x01, 0x09, 0x47, 0xA7, 0x10, 0x6A, 0x13, 0x02, 0x13, 0x41, 0xA7,
        0x14, 0x11, 0x6A, 0x13, 0x02, 0x13, 0x42, 0x50, 0x6A, 0x6C, 0x12,
        0x04, 0x12, 0x6B, 0x22, 0x14, 0x11, 0x21, 0x6B, 0x0B, 0x52
    };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm.regs[10] = 3;
    vm.regs[11] = 2;
    vm.regs[12] = -1;
    run(&vm);
    puts("table 11: quadratic via К ПП");
    CHECK_NUM("x2", vm_get_x(&vm), -1);
    CHECK_NUM("x1 in R1", vm_get_reg(&vm, 1), 0.33333333);

    load(&vm, code, sizeof code);
    vm.regs[10] = 1;
    vm.regs[11] = 0;
    vm.regs[12] = 1;
    run(&vm);
    CHECK_TRUE("negative discriminant -> ЕГГОГ", vm.state == VM_ERROR);
}

/* Manual p.79-85, tables 13 and 14: Σ(2·tg(xᵢ/3)+4), counter by
 * К П→x 3 and by F L0. */
static void test_sum_tables13_14(void) {
    static const uint8_t t13[] = {
        0x43, 0xD3, 0x63, 0x5E, 0x07, 0x65, 0x50, 0x03, 0x13, 0x1E,
        0x02, 0x12, 0x04, 0x10, 0x65, 0x10, 0x45, 0x51, 0x01
    };
    static const uint8_t t14[] = {
        0x40, 0x60, 0x03, 0x13, 0x1E, 0x02, 0x12, 0x04, 0x10, 0x65,
        0x10, 0x45, 0x5D, 0x01, 0x50
    };
    MK56VM vm;
    puts("tables 13/14: К П→x counter and F L0 loop");
    load(&vm, t13, sizeof t13);
    vm_input(&vm, 5);
    run(&vm);
    CHECK_APPROX("table 13 sum", vm_get_x(&vm), 29.644467);

    load(&vm, t14, sizeof t14);
    vm_input(&vm, 4);
    run(&vm);
    CHECK_APPROX("table 14 sum", vm_get_x(&vm), 29.644467);
    CHECK_NUM("R0 left at 1", vm_get_reg(&vm, 0), 1);
}

/* Manual p.86-89, table 16: compound interest, entry point 38 computes K. */
static void test_interest_table16(void) {
    static const uint8_t code[] = {
        0x53, 0x46, 0x18, 0x46, 0x65, 0x64, 0x13, 0x18, 0x66, 0x13,
        0x42, 0x50, 0x65, 0x0E, 0x64, 0x13, 0x0E, 0x62, 0x23, 0x14,
        0x24, 0x01, 0x11, 0x01, 0x00, 0x00, 0x12, 0x43, 0x50, 0x53,
        0x46, 0x24, 0x23, 0x0E, 0x65, 0x12, 0x44, 0x50, 0x53, 0x46,
        0x24, 0x0E, 0x64, 0x12, 0x45, 0x50, 0x63, 0x01, 0x00, 0x00,
        0x13, 0x01, 0x10, 0x0E, 0x62, 0x14, 0x52
    };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm.regs[2] = 6;
    vm.regs[3] = 7.5;
    vm.regs[4] = 270;
    run_from(&vm, 38);
    puts("table 16: compound interest");
    CHECK_APPROX("K", vm_get_x(&vm), 416.6914);
}

/* Manual p.91, table 19: sum (+ at 08) or product (× at 08) of 1..n. */
static void test_sum_product_table19(void) {
    uint8_t code[] = {
        0x42, 0x01, 0x11, 0x43, 0x57, 0x13, 0x0E, 0x62, 0x10,
        0x42, 0x63, 0x51, 0x01, 0x62, 0x50, 0x51, 0x00
    };
    MK56VM vm;
    puts("table 19: sum / product of 1..n");
    load(&vm, code, sizeof code);
    vm_input(&vm, 5);
    run(&vm);
    CHECK_NUM("S(5)", vm_get_x(&vm), 15);

    code[8] = 0x12;
    load(&vm, code, sizeof code);
    vm_input(&vm, 5);
    run(&vm);
    CHECK_NUM("P(5)", vm_get_x(&vm), 120);
}

/* Manual p.92, table 20: running mean, one value per С/П. */
static void test_mean_table20(void) {
    static const uint8_t code[] = {
        0x42, 0x01, 0x43, 0x62, 0x50, 0x0E, 0x62, 0x10, 0x42, 0x63,
        0x01, 0x10, 0x43, 0x0E, 0x62, 0x14, 0x13, 0x50, 0x51, 0x05
    };
    const double in[] = { 2, 4, 9 }, want[] = { 2, 3, 5 };
    MK56VM vm;
    puts("table 20: running mean");
    load(&vm, code, sizeof code);
    for (int i = 0; i < 3; i++) {
        vm_input(&vm, in[i]);
        vm_run(&vm);
        CHECK_NUM("mean", vm_get_x(&vm), want[i]);
    }
}

/* Manual p.93-94, table 22: S = v²·sin α / g in degrees, α В↑ v С/П. */
static void test_ballistic_table22(void) {
    static const uint8_t code[] = {
        0x22, 0x14, 0x1C, 0x12, 0x09, 0x0A, 0x08, 0x01, 0x13, 0x50, 0x51, 0x00
    };
    MK56VM vm;
    load(&vm, code, sizeof code);
    vm.angle = ANGLE_DEG;
    vm_input(&vm, 30);
    vm.stack[1] = 30;       /* α В↑ */
    vm.stack[0] = 10;       /* v    */
    run(&vm);
    puts("table 22: ballistic (degrees, decimal entry)");
    CHECK_APPROX("S", vm_get_x(&vm), 5.0968399);
}

static void test_arithmetic_digits(void) {
    /* 1/560 shows 1,7857142 -03 (p.29): truncated, not rounded */
    static const uint8_t inv[] = { 0x23, 0x50 };
    MK56VM vm;
    puts("8-digit truncation");
    load(&vm, inv, sizeof inv);
    vm_input(&vm, 560);
    run(&vm);
    CHECK_TRUE("1/560 = 1.7857142e-3", vm_get_x(&vm) == 1.7857142e-3);

    /* 0,4 В↑ Fπ × 25 × 2,25 = 70,685831 (p.34) */
    static const uint8_t chain[] = {
        0x00, 0x0A, 0x04, 0x0E, 0x20, 0x12, 0x02, 0x05, 0x12,
        0x02, 0x0A, 0x02, 0x05, 0x12, 0x50
    };
    load(&vm, chain, sizeof chain);
    run(&vm);
    CHECK_TRUE("0.4·π·25·2.25 = 70.685831", vm_get_x(&vm) == 70.685831);
}

/* ---- manual examples in automatic mode ---------------------------------- */

/* ---- automatic-mode keystrokes (public API only) ---------------------- */
/* Press one programmable key as the user would in АВТ: run it as a single
 * step from a scratch cell and keep the PC where it was. Not for БП/В/О/С/П/ПП. */
static void press(MK56VM *vm, uint8_t op) {
    uint8_t pc = vm->pc, saved = vm->program[96];
    vm->program[96] = op;
    vm->pc = 96;
    vm_step(vm);
    vm->program[96] = saved;
    vm->pc = pc;
}
#define PRESS(vm, ...) do { const uint8_t k_[] = { __VA_ARGS__ };            \
    for (size_t i_ = 0; i_ < sizeof k_; i_++) press(vm, k_[i_]); } while (0)

#define CHECK_DISPLAY(name, vm, want) do {                                  \
    char b_[32]; vm_format_display(vm, b_, sizeof b_); checks++;            \
    if (strcmp(b_, want) != 0) { failures++;                                \
        printf("  FAIL %s: shows \"%s\", want \"%s\"\n", name, b_, want); } \
} while (0)

#define CHECK_STACK(name, vm, t, z, y, x) do {                              \
    CHECK_NUM(name " T", (vm)->stack[3], t); CHECK_NUM(name " Z", (vm)->stack[2], z); \
    CHECK_NUM(name " Y", (vm)->stack[1], y); CHECK_NUM(name " X", (vm)->stack[0], x); \
} while (0)

enum { PT = MK56_POINT, CHS = MK56_CHS, EEX = MK56_EEX, CX = MK56_CLX,
       UP = MK56_ENTER, ADD = MK56_ADD, SUB = MK56_SUB, MUL = MK56_MUL,
       DIV = MK56_DIV, SWP = MK56_SWAP, ROT = MK56_ROT, BX = MK56_LASTX };

/* p.22-24: entry, ВП, /-/ in the exponent, 8-digit lock, ЕГГОГ recovery */
static void test_entry_p22(void) {
    MK56VM vm;
    puts("p.22-24: number entry");
    vm_init(&vm); PRESS(&vm, 1, 4, 8, PT, 1, 2, CHS);
    CHECK_DISPLAY("148,12 /-/", &vm, "-148,12");
    PRESS(&vm, EEX, 1, 5, CHS);
    CHECK_NUM("-148,12 ВП 15 /-/", vm_get_x(&vm), -148.12e-15);
    vm_init(&vm); PRESS(&vm, 1, 4, 8, PT, 1, 2, CHS, EEX, 4, UP);
    CHECK_DISPLAY("В↑ normalises", &vm, "-1481200,");
    vm_init(&vm); PRESS(&vm, EEX, 1, 2, 3);           /* mantissa 0 -> 1; 1 shifts out */
    CHECK_NUM("ВП on 0, exponent 23", vm_get_x(&vm), 1e23);
    vm_init(&vm); PRESS(&vm, 1, 2, 3, 4, 5, 6, 7, 8, 9);
    CHECK_NUM("9th digit locked", vm_get_x(&vm), 12345678);
    vm_init(&vm); PRESS(&vm, 4, CHS, MK56_SQRT);
    CHECK_DISPLAY("4 /-/ F√", &vm, "ЕГГОГ");
    PRESS(&vm, 2, 5);
    CHECK_DISPLAY("then 25", &vm, "25,");
}

/* p.29-30: chain calculations, exact printed digits */
static void test_chain_p29(void) {
    MK56VM vm;
    puts("p.29-30: chain calculations");
    vm_init(&vm);
    PRESS(&vm, 2, 2, 0, MK56_INV, 4, 0, 0, 0, MK56_INV, ADD);
    CHECK_DISPLAY("1/220+1/4000", &vm, "4,7954545 -03");
    PRESS(&vm, 5, 6, 0, MK56_INV, ADD, 1, 2, 0, 0, MK56_INV, ADD);
    CHECK_DISPLAY("+1/560+1/1200", &vm, "7,414502 -03");
    PRESS(&vm, MK56_INV);
    CHECK_DISPLAY("R total", &vm, "134,87082");
    vm_init(&vm);
    PRESS(&vm, 1, 2, 0, 0, 0, UP, 2, DIV, MK56_PI, DIV, 5, 0, DIV);
    CHECK_DISPLAY("L = 12000/(2πf)", &vm, "38,197186");
    vm_init(&vm); PRESS(&vm, 0, PT, 2, CHS, UP);
    CHECK_DISPLAY("-0,2 В↑", &vm, "-2, -01");
    PRESS(&vm, 4, MK56_POW);
    CHECK_DISPLAY("4^-0,2", &vm, "7,5785828 -01");
}

/* p.36-43: stack movement tables */
static void test_stack_p36(void) {
    MK56VM vm;
    puts("p.36-43: stack movement");
    vm_init(&vm); PRESS(&vm, 4, UP, 3, UP, 2, UP, 1);
    CHECK_STACK("4В↑3В↑2В↑1", &vm, 4, 3, 2, 1);
    PRESS(&vm, UP);  CHECK_STACK("В↑", &vm, 3, 2, 1, 1);
    PRESS(&vm, ROT); CHECK_STACK("F⟳", &vm, 1, 3, 2, 1);
    PRESS(&vm, ROT); CHECK_STACK("F⟳ again", &vm, 1, 1, 3, 2);
    PRESS(&vm, SWP); CHECK_STACK("↔", &vm, 1, 1, 2, 3);
    PRESS(&vm, CX);  CHECK_STACK("Cx", &vm, 1, 1, 2, 0);
    PRESS(&vm, 3, 7, 5); CHECK_STACK("375 after Cx: no lift", &vm, 1, 1, 2, 375);
    PRESS(&vm, MK56_SQRT); CHECK_NUM("X1 = 375 (p.38)", vm.lastx, 375);

    vm_init(&vm); PRESS(&vm, 4, UP, UP, UP, 1, 6, MUL, ROT);
    CHECK_STACK("constant 16·4 then F⟳ (p.40)", &vm, 64, 4, 4, 4);
    PRESS(&vm, 2, 3); CHECK_STACK("digit after F⟳ lifts", &vm, 4, 4, 4, 23);
    PRESS(&vm, MUL);  CHECK_NUM("23·4", vm_get_x(&vm), 92);

    vm_init(&vm); vm.stack[0] = 35;  /* p.41: Y35 after (12+3)·7÷3 */
    vm.lift = true;
    PRESS(&vm, 3, UP, 7, UP, 3, UP, 1, 2);
    CHECK_STACK("four numbers (p.42)", &vm, 3, 7, 3, 12);
    PRESS(&vm, ADD); CHECK_STACK("+ (T duplicated)", &vm, 3, 3, 7, 15);
    PRESS(&vm, MUL, SWP, DIV); CHECK_STACK("× ↔ ÷", &vm, 3, 3, 3, 35);
    CHECK_NUM("X1 = 3", vm.lastx, 3);
}

/* p.45-48: X1, F Bx and F⟳ with sin 2° (degrees). Values from the
 * machine differ in the last digit, so check the stack movement. */
static void test_x1_p45(void) {
    MK56VM vm;
    puts("p.45-48: X1 / F Bx");
    vm_init(&vm); vm.angle = ANGLE_DEG;
    vm.stack[0] = 35; vm.stack[1] = vm.stack[2] = vm.stack[3] = 3;
    vm.lastx = 3; vm.lift = true;
    PRESS(&vm, 1, 4, UP, 2, MK56_SIN);
    CHECK_NUM("X1 = 2", vm.lastx, 2);
    PRESS(&vm, MUL);
    double s = vm.lastx, p = vm_get_x(&vm);
    CHECK_APPROX("sin 2°", s, 3.4899495e-2);
    PRESS(&vm, BX);  CHECK_STACK("F Bx lifts", &vm, 3, 35, p, s);
    PRESS(&vm, ROT); CHECK_STACK("F⟳ restores", &vm, s, 3, 35, p);
    PRESS(&vm, 4, SUB); CHECK_NUM("X1 = 4", vm.lastx, 4);
    PRESS(&vm, BX, DIV);
    CHECK_APPROX("[(14 sin 2°)-4]/4", vm_get_x(&vm), -8.7785177e-1);
    CHECK_STACK("final stack", &vm, 3, 3, 35, vm_get_x(&vm));
}

/* p.77-78: К x→П and К П→x from the keyboard */
static void test_indirect_keys_p77(void) {
    MK56VM vm;
    puts("p.77-78: К x→П / К П→x");
    vm_init(&vm);
    PRESS(&vm, 1, 4, MK56_STO + 0, MK56_K_STO + 0);
    CHECK_DISPLAY("К x→П 0", &vm, "14,");
    CHECK_NUM("R0 = 13", vm.regs[0], 13);
    CHECK_NUM("Rd = 14", vm.regs[13], 14);
    PRESS(&vm, MK56_RCL + 0);  CHECK_DISPLAY("П→x 0", &vm, "00000013,");
    PRESS(&vm, MK56_RCL + 13); CHECK_DISPLAY("П→x d", &vm, "14,");
    PRESS(&vm, 5, MK56_K_STO + 0);
    CHECK_NUM("R0 = 12", vm.regs[0], 12);
    CHECK_NUM("Rc = 5", vm.regs[12], 5);
    PRESS(&vm, MK56_RCL + 0);  CHECK_DISPLAY("П→x 0 again", &vm, "00000012,");
    PRESS(&vm, MK56_RCL + 12); CHECK_DISPLAY("П→x c", &vm, "5,");
    vm_init(&vm);
    PRESS(&vm, 4, MK56_STO + 4, 1, 0, MK56_STO + 5, 2, 0, MK56_STO + 6, 3, 0, MK56_STO + 7);
    PRESS(&vm, MK56_K_RCL + 4); CHECK_DISPLAY("К П→x 4 = R5", &vm, "10,");
    PRESS(&vm, MK56_RCL + 4);   CHECK_DISPLAY("П→x 4", &vm, "00000005,");
    PRESS(&vm, MK56_K_RCL + 4); CHECK_DISPLAY("К П→x 4 = R6", &vm, "20,");
    PRESS(&vm, MK56_RCL + 4);   CHECK_DISPLAY("П→x 4 again", &vm, "00000006,");
    CHECK_NUM("R4 = 6", vm.regs[4], 6);
    /* A code is an ordinary number to arithmetic */
    PRESS(&vm, 1, ADD);         CHECK_DISPLAY("code + 1", &vm, "7,");
    PRESS(&vm, MK56_RCL + 4, 1, SWP);
    CHECK_DISPLAY("↔ moves the code", &vm, "00000006,");
    PRESS(&vm, 3, MK56_STO + 4, MK56_RCL + 4);
    CHECK_DISPLAY("x→П replaces the code", &vm, "3,");
}

/* p.70: after table 9 the registers hold modified addresses. */
static void test_codes_p70(void) {
    static const uint8_t code[] = {
        0x04, 0x0E, 0x83, 0x21, 0x02, 0x10, 0x84,
        0x10, 0x03, 0x12, 0x8A, 0x11, 0x50
    };
    MK56VM vm;
    puts("p.70: modified addresses show leading zeros");
    load(&vm, code, sizeof code);
    vm.regs[3] = 5; vm.regs[4] = 7; vm.regs[10] = 12;
    run(&vm);
    vm.state = VM_STOPPED;
    press(&vm, MK56_RCL + 3);  CHECK_DISPLAY("П→x 3", &vm, "00000004,");
    press(&vm, MK56_RCL + 4);  CHECK_DISPLAY("П→x 4", &vm, "00000008,");
    press(&vm, MK56_RCL + 10); CHECK_DISPLAY("П→x a", &vm, "00000012,");
}

/* Appendix p.96-100: functional test program, tests 14-102. */
static void test_functional_test(void) {
    static const uint8_t code[] = {
        0xB0, 0x5D, 0x13, 0x5B, 0x09, 0x01, 0x07, 0x43, 0x83, 0x6D, 0x13,
        0x51, 0x03, 0x60, 0x51, 0x00, 0x12, 0x67, 0x10, 0x58, 0x25, 0x5A,
        0x25, 0x51, 0x27, 0x51, 0x21, 0xB4, 0x5C, 0x31, 0x54, 0x5E, 0x35,
        0x51, 0x39, 0x53, 0x54, 0x59, 0x33, 0x69, 0x11, 0x57, 0x60, 0x04,
        0x07, 0x46, 0x14, 0x96, 0xE6, 0x76, 0xC6, 0x22, 0x51, 0x57, 0x21,
        0x23, 0x52, 0x06, 0x02, 0x4B, 0xAB, 0x50, 0x0F, 0x16, 0x52
    };
    MK56VM vm;
    puts("appendix: functional test 14-102");
    load(&vm, code, sizeof code);
    vm.stack[0] = 99.999552;                      /* after test 13 */
    PRESS(&vm, CX, MK56_STO + 4, 1, 4, MK56_STO + 0);
    run(&vm);                                     /* 86 В/О, 87 С/П */
    CHECK_TRUE("#87 halted", vm.state == VM_HALTED);
    CHECK_APPROX("#87 e^x", vm_get_x(&vm), 6.187848e-5);
    PRESS(&vm, ROT);         CHECK_DISPLAY("#88", &vm, "62,");
    PRESS(&vm, ROT);         CHECK_APPROX("#89", vm_get_x(&vm), 93.902651);
    PRESS(&vm, ROT);         CHECK_DISPLAY("#90", &vm, "47,");
    PRESS(&vm, MK56_RCL + 1); CHECK_DISPLAY("#91", &vm, "10,428571");
    PRESS(&vm, MK56_RCL + 2); CHECK_DISPLAY("#92", &vm, "-99999999,");
    PRESS(&vm, MK56_RCL + 3); CHECK_DISPLAY("#93", &vm, "00000001,");
    PRESS(&vm, MK56_RCL + 4); CHECK_DISPLAY("#94", &vm, "00000001,");
    PRESS(&vm, MK56_RCL + 5); CHECK_DISPLAY("#95", &vm, "6,");
    PRESS(&vm, MK56_RCL + 8); CHECK_DISPLAY("#96", &vm, "0,");
    PRESS(&vm, MK56_RCL + 10); CHECK_DISPLAY("#97", &vm, "0,");
    PRESS(&vm, MK56_RCL + 13); CHECK_DISPLAY("#98", &vm, "14,");
    PRESS(&vm, MK56_RCL + 13, CHS); CHECK_DISPLAY("#99", &vm, "-14,");
    PRESS(&vm, MK56_SQRT);   CHECK_DISPLAY("#100", &vm, "ЕГГОГ");
    PRESS(&vm, CX);          CHECK_DISPLAY("#101", &vm, "0,");
    PRESS(&vm, EEX);         CHECK_NUM("#102 ВП", vm_get_x(&vm), 1);
}

/* p.24: range limits */
static void test_range_p24(void) {
    MK56VM vm;
    puts("p.24: overflow / underflow");
    vm_init(&vm); PRESS(&vm, 1, EEX, 9, 9, CHS, UP, 1, 0, DIV);
    CHECK_TRUE("underflow -> ЕГГОГ", vm.state == VM_ERROR);
    CHECK_NUM("underflow sets X = 0", vm_get_x(&vm), 0);
    vm_init(&vm); PRESS(&vm, 1, EEX, 9, 9, MK56_SQ);
    CHECK_TRUE("overflow -> ЕГГОГ", vm.state == VM_ERROR);
    CHECK_NUM("overflow keeps X", vm_get_x(&vm), 1e99);
    vm_init(&vm); PRESS(&vm, 5, 0, EEX, 9, 9, UP);
    CHECK_TRUE("keyed 5e100 -> ЕГГОГ", vm.state == VM_ERROR);
    vm_init(&vm); PRESS(&vm, PT, 1, 2, 3, 4, 5, 6, 7, 8);
    CHECK_NUM(",12345678: leading 0 takes a digit", vm_get_x(&vm), 0.1234567);
    vm_init(&vm); PRESS(&vm, 6, PT, 0, 2, EEX, 2, 3);
    PRESS(&vm, UP);
    CHECK_DISPLAY("6,02 ВП 23 (p.48)", &vm, "6,02 23");
}

int main(void) {
    test_indirect_jumps_table9();
    test_conditionals();
    test_subroutine_table8();
    test_number_entry();
    test_loop_fl0();
    test_circle_table5();
    test_branch_table10();
    test_quadratic_table11();
    test_sum_tables13_14();
    test_interest_table16();
    test_sum_product_table19();
    test_mean_table20();
    test_ballistic_table22();
    test_arithmetic_digits();
    test_entry_p22();
    test_chain_p29();
    test_stack_p36();
    test_x1_p45();
    test_indirect_keys_p77();
    test_codes_p70();
    test_functional_test();
    test_range_p24();
    printf("\n%d/%d checks passed\n", checks - failures, checks);
    return failures ? 1 : 0;
}
