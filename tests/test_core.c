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
    printf("\n%d/%d checks passed\n", checks - failures, checks);
    return failures ? 1 : 0;
}
