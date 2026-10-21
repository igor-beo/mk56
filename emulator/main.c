/**
 * MK56 Emulator - Main Entry Point
 * 
 * Usage:
 *   mk56emu program.bin           - Run with TUI (.asm / .mk56 are assembled)
 *   mk56emu program.bin -c        - Console mode (no UI)
 *   mk56emu program.bin -c -i 5   - Console with input value
 */

#include "mk56emu.h"
#include "mk56asm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Forward declarations from mk56ui.c
extern void ui_init(MK56VM *vm);
extern void ui_run(void);
extern void ui_cleanup(void);

static void print_usage(const char *prog) {
    printf("MK56 Emulator v1.0\n\n");
    printf("Usage: %s program.bin|program.asm|program.mk56 [options]\n\n", prog);
    printf("Options:\n");
    printf("  -c          Console mode (no TUI)\n");
    printf("  -i VALUE    Input value to X register\n");
    printf("  -r R0=VAL   Set register value (e.g., -r R0=5, -r Ra=12)\n");
    printf("  -a MODE     Angle switch: rad (default), deg, grad\n");
    printf("  -d          Disassemble and exit\n");
    printf("  -h          Show this help\n");
    printf("\nTUI keys:\n");
    printf("  F7 Step   F8 Run   F9 Reset   F5 Input X   F4 Edit step\n");
    printf("  F6 Breakpoint   G Angle   F1 Help   F10 Menu   Q Quit\n");
}

static void console_run(MK56VM *vm) {
    printf("Running program (%zu steps)...\n\n", vm->program_size);
    
    vm_run(vm);
    
    printf("=== Execution Complete ===\n");
    printf("State: %s\n", 
        vm->state == VM_HALTED ? "HALTED" :
        vm->state == VM_ERROR ? "ERROR" : "STOPPED");
    
    if (vm->error != ERR_NONE) {
        printf("Error: %s\n", vm_error_str(vm->error));
    }
    
    printf("Steps executed: %llu\n", (unsigned long long)vm->cycles);
    char shown[40];
    vm_format_display(vm, shown, sizeof shown);
    printf("Display: %s\n\n", shown);
    
    printf("Stack:\n");
    printf("  X = %.10g\n", vm_get_stack(vm, 0));
    printf("  Y = %.10g\n", vm_get_stack(vm, 1));
    printf("  Z = %.10g\n", vm_get_stack(vm, 2));
    printf("  T = %.10g\n", vm_get_stack(vm, 3));
    
    printf("\nRegisters (non-zero):\n");
    for (int i = 0; i < 14; i++) {
        double v = vm_get_reg(vm, i);
        if (v != 0) {
            char name[4];
            snprintf(name, sizeof(name), "R%s", mk56_reg_name(i));
            printf("  %s = %.10g\n", name, v);
        }
    }
}

static void disassemble(MK56VM *vm) {
    printf("Disassembly (%zu steps):\n\n", vm->program_size);
    printf("ADDR  CODES  KEYS          MK56-ASM\n");
    printf("----  -----  ------------  -----------\n");
    
    uint16_t addr = 0;
    while (addr < vm->program_size) {
        char disasm[32], key[40], codes[8];
        int size = vm_disasm(vm, addr, disasm, sizeof(disasm));
        mk56_disasm(vm->program, addr, false, key, sizeof(key));
        if (size == 2) snprintf(codes, sizeof codes, "%02X %02X", vm->program[addr],
                                vm->program[(addr + 1) % MK56_PROGRAM_SIZE]);
        else snprintf(codes, sizeof codes, "%02X", vm->program[addr]);
        
        // Pad the UTF-8 key column by characters, not bytes
        int width = 0;
        for (const char *c = key; *c; c++) if ((*c & 0xC0) != 0x80) width++;
        printf("%02d    %-5s  %s%*s  %s\n", addr, codes, key, 12 - width, "", disasm);
        
        addr += size;
    }
}

/* .asm and .mk56 sources are assembled in place; anything else is binary. */
static bool load_program(MK56VM *vm, const char *path) {
    const char *ext = strrchr(path, '.');
    bool listing = ext && strcmp(ext, ".mk56") == 0;
    if (!listing && !(ext && strcmp(ext, ".asm") == 0)) return vm_load_file(vm, path);
    
    FILE *f = fopen(path, "rb");
    if (!f) return false;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *src = malloc((size_t)len + 1);
    Assembler *as = malloc(sizeof *as);
    bool ok = src && as && fread(src, 1, (size_t)len, f) == (size_t)len;
    fclose(f);
    if (ok) {
        src[len] = '\0';
        ok = asm_assemble_ex(as, src, listing);
        if (ok) {
            size_t size;
            const uint8_t *bin = asm_get_binary(as, &size);
            ok = vm_load(vm, bin, size);
        } else {
            fprintf(stderr, "Assembly error: %s\n", asm_get_error(as));
        }
    }
    free(src);
    free(as);
    return ok;
}

int main(int argc, char **argv) {
    const char *prog_path = NULL;
    bool console_mode = false;
    bool disasm_mode = false;
    double input_value = 0;
    bool has_input = false;
    
    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
        else if (strcmp(argv[i], "-c") == 0) {
            console_mode = true;
        }
        else if (strcmp(argv[i], "-d") == 0) {
            disasm_mode = true;
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_value = atof(argv[++i]);
            has_input = true;
            if (!vm_value_ok(input_value)) {
                fprintf(stderr, "Error: -i %s is outside the calculator's range (|x| < 1e100)\n", argv[i]);
                return 1;
            }
        }
        else if ((strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-a") == 0) && i + 1 < argc) {
            // Handled after VM init
            i++;
        }
        else if (argv[i][0] != '-') {
            prog_path = argv[i];
        }
    }
    
    if (!prog_path) {
        print_usage(argv[0]);
        return 1;
    }
    
    // Initialize VM
    MK56VM vm;
    vm_init(&vm);
    
    if (!load_program(&vm, prog_path)) {
        fprintf(stderr, "Error: Cannot load program: %s\n", prog_path);
        return 1;
    }
    
    printf("Loaded: %s (%zu steps)\n", prog_path, vm.program_size);
    
    // Handle -r (set registers) and -a (angle switch)
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0 && i + 1 < argc) {
            const char *mode = argv[++i];
            vm.angle = strcmp(mode, "deg") == 0 ? ANGLE_DEG
                     : strcmp(mode, "grad") == 0 ? ANGLE_GRAD : ANGLE_RAD;
            continue;
        }
        if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            char *spec = argv[++i];
            // Parse R0=5 format
            if (spec[0] == 'R' || spec[0] == 'r') {
                int reg = -1;
                char c = spec[1];
                if (c >= '0' && c <= '9') reg = c - '0';
                else if (c >= 'A' && c <= 'D') reg = 10 + c - 'A';
                else if (c >= 'a' && c <= 'd') reg = 10 + c - 'a';
                
                char *eq = strchr(spec, '=');
                if (reg >= 0 && eq && !vm_value_ok(atof(eq + 1))) {
                    fprintf(stderr, "Error: -r %s is outside the calculator's range (|x| < 1e100)\n", spec);
                    return 1;
                }
                if (reg >= 0 && eq) {
                    vm.regs[reg] = atof(eq + 1);
                    printf("Set R%s = %g\n", mk56_reg_name(reg), vm.regs[reg]);
                }
            }
        }
    }
    
    // Set input value
    if (has_input) {
        vm_input(&vm, input_value);
        printf("Input: X = %g\n", input_value);
    }
    
    // Disassemble mode
    if (disasm_mode) {
        disassemble(&vm);
        return 0;
    }
    
    // Console or TUI mode
    if (console_mode) {
        console_run(&vm);
    } else {
        ui_init(&vm);
        ui_run();
        ui_cleanup();
    }
    
    return 0;
}
