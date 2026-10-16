/**
 * mk56test - assemble programs and run the test directives in their
 * comments.
 *
 *   ; @angle rad|deg|grad      angle switch (default rad)
 *   ; @reg R0=5 Ra=12          set registers
 *   ; @stack X=10 Y=30         set stack registers
 *   ; @start 38                set the program counter
 *   ; @input 5                 key 5 into X, press С/П, run until stop
 *   ; @run                     press С/П without new input
 *   ; @expect X=416.6914       check X / Y / Z / T / R0-Rd
 *   ; @expect R1=0.5 tol=1e-5  tolerance (default 1e-6), times max(1, |v|)
 *   ; @expect error            expect ЕГГОГ
 *   ; @reset                   clear stack and registers, PC = 00
 *   ; @xfail reason            known failure: reported, does not fail the run
 *
 * *.mk56 files are original listings, anything else MK56-ASM.
 * Usage: mk56test [-v] file...   Exit status 1 if any check fails.
 */

#include "mk56asm.h"
#include "mk56emu.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool verbose;

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((size_t)len + 1);
    if (buf && fread(buf, 1, (size_t)len, f) != (size_t)len) { free(buf); buf = NULL; }
    if (buf) buf[len] = '\0';
    fclose(f);
    return buf;
}

/* "X" "Y" "Z" "T" -> stack slot, "R3" "Ra" -> register. */
static double *target(MK56VM *vm, const char *name) {
    static const char stack_names[] = "XYZT";
    char c = (char)toupper((unsigned char)name[0]);
    if (!name[1]) {
        const char *s = strchr(stack_names, c);
        return s ? &vm->stack[s - stack_names] : NULL;
    }
    if (c == 'R' && name[1] && !name[2]) {
        char r = (char)toupper((unsigned char)name[1]);
        if (r >= '0' && r <= '9') return &vm->regs[r - '0'];
        if (r >= 'A' && r <= 'D') return &vm->regs[10 + r - 'A'];
    }
    return NULL;
}

typedef struct { int checks, failures; bool xfail; } Result;

static void fail(Result *res, const char *path, int line, const char *msg) {
    res->failures++;
    printf("  %s %s:%d: %s\n", res->xfail ? "XFAIL" : "FAIL", path, line, msg);
}

static void run_directive(MK56VM *vm, char *d, const char *path, int line, Result *res) {
    char *word = strtok(d, " \t");
    if (!word) return;
    char msg[160];

    if (strcmp(word, "@angle") == 0) {
        char *a = strtok(NULL, " \t");
        vm->angle = !a ? ANGLE_RAD : strcmp(a, "deg") == 0 ? ANGLE_DEG
                  : strcmp(a, "grad") == 0 ? ANGLE_GRAD : ANGLE_RAD;
    } else if (strcmp(word, "@reg") == 0 || strcmp(word, "@stack") == 0) {
        for (char *a = strtok(NULL, " \t"); a; a = strtok(NULL, " \t")) {
            char *eq = strchr(a, '=');
            if (!eq) continue;
            *eq = '\0';
            double *t = target(vm, a);
            if (t) *t = atof(eq + 1);
            else { snprintf(msg, sizeof msg, "unknown register %s", a); fail(res, path, line, msg); }
        }
    } else if (strcmp(word, "@start") == 0) {
        char *a = strtok(NULL, " \t");
        vm->pc = (uint8_t)(a ? atoi(a) : 0);
    } else if (strcmp(word, "@input") == 0 || strcmp(word, "@run") == 0) {
        if (word[1] == 'i') {
            char *a = strtok(NULL, " \t");
            vm_input(vm, a ? atof(a) : 0);
        }
        vm_run(vm);
        if (verbose) printf("    %s -> X = %.10g (%s)\n", word, vm_get_x(vm),
                            vm->state == VM_ERROR ? vm_error_str(vm->error) : "stopped");
    } else if (strcmp(word, "@xfail") == 0) {
        res->xfail = true;
    } else if (strcmp(word, "@reset") == 0) {
        vm_reset(vm);
    } else if (strcmp(word, "@expect") == 0) {
        char *what = strtok(NULL, " \t");
        res->checks++;
        if (what && strcmp(what, "error") == 0) {
            if (vm->state != VM_ERROR) fail(res, path, line, "expected ЕГГОГ");
            return;
        }
        if (vm->error == ERR_STEP_LIMIT) { fail(res, path, line, "program never stopped"); return; }
        char *eq = what ? strchr(what, '=') : NULL;
        if (!eq) { fail(res, path, line, "bad @expect"); return; }
        *eq = '\0';
        double want = atof(eq + 1), tol = 1e-6;
        char *t = strtok(NULL, " \t");
        if (t && strncmp(t, "tol=", 4) == 0) tol = atof(t + 4);
        double *slot = target(vm, what);
        if (!slot) { fail(res, path, line, "bad @expect register"); return; }
        if (!(fabs(*slot - want) <= tol * fmax(1.0, fabs(want)))) {
            snprintf(msg, sizeof msg, "%s = %.10g, expected %.10g%s%s", what, *slot, want,
                     vm->state == VM_ERROR ? " after " : "",
                     vm->state == VM_ERROR ? vm_error_str(vm->error) : "");
            fail(res, path, line, msg);
        }
    } else {
        snprintf(msg, sizeof msg, "unknown directive %s", word);
        fail(res, path, line, msg);
    }
}

static Result test_file(const char *path) {
    Result res = { 0, 0, false };
    char *src = read_file(path);
    if (src && strstr(src, "@xfail")) res.xfail = true;
    if (!src) { printf("  FAIL %s: cannot read\n", path); res.failures = 1; return res; }

    const char *ext = strrchr(path, '.');
    Assembler *as = malloc(sizeof *as);
    if (!as || !asm_assemble_ex(as, src, ext && strcmp(ext, ".mk56") == 0)) {
        printf("  FAIL %s: %s\n", path, as ? asm_get_error(as) : "out of memory");
        res.failures = 1;
        free(as);
        free(src);
        return res;
    }

    MK56VM vm;
    vm_init(&vm);
    size_t size;
    const uint8_t *bin = asm_get_binary(as, &size);
    vm_load(&vm, bin, size);

    int line = 1;
    for (char *p = src; *p; line++) {
        char *eol = strchr(p, '\n');
        if (eol) *eol = '\0';
        char *semi = strchr(p, ';');
        char *at = semi ? strchr(semi, '@') : NULL;
        if (at) run_directive(&vm, at, path, line, &res);
        if (!eol) break;
        p = eol + 1;
    }
    if (res.checks == 0) { printf("  FAIL %s: no @expect\n", path); res.failures++; }
    free(as);
    free(src);
    return res;
}

int main(int argc, char **argv) {
    int files = 0, failed_files = 0, xfails = 0, checks = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) { verbose = true; continue; }
        if (verbose) printf("%s\n", argv[i]);
        Result r = test_file(argv[i]);
        files++;
        checks += r.checks;
        if (r.failures && r.xfail) xfails++;
        else if (r.failures) failed_files++;
        else if (r.xfail) printf("  XPASS %s: remove @xfail\n", argv[i]);
    }
    printf("%d/%d programs passed (%d checks)", files - failed_files - xfails, files, checks);
    if (xfails) printf(", %d known failure%s", xfails, xfails == 1 ? "" : "s");
    printf("\n");
    return failed_files ? 1 : 0;
}
