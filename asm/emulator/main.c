/**
 * MK56 Emulator - Main Entry Point
 * 
 * Usage:
 *   mk56emu program.bin           - Run with TUI
 *   mk56emu program.bin -c        - Console mode (no UI)
 *   mk56emu program.bin -c -i 5   - Console with input value
 */

#include "mk56emu.h"
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
    printf("Usage: %s program.bin [options]\n\n", prog);
    printf("Options:\n");
    printf("  -c          Console mode (no TUI)\n");
    printf("  -i VALUE    Input value to X register\n");
    printf("  -r R0=VAL   Set register value (e.g., -r R0=5)\n");
    printf("  -d          Disassemble and exit\n");
    printf("  -h          Show this help\n");
    printf("\nTUI Controls:\n");
    printf("  SPACE/s  Step    r  Run     R  Reset\n");
    printf("  i  Input         b  Break   q  Quit\n");
    printf("  ?  Help\n");
}

static void console_run(MK56VM *vm) {
    printf("Running program (%zu bytes)...\n\n", vm->program_size);
    
    vm_run(vm);
    
    printf("=== Execution Complete ===\n");
    printf("State: %s\n", 
        vm->state == VM_HALTED ? "HALTED" :
        vm->state == VM_ERROR ? "ERROR" : "STOPPED");
    
    if (vm->error != ERR_NONE) {
        printf("Error: %s\n", vm_error_str(vm->error));
    }
    
    printf("Cycles: %llu\n\n", (unsigned long long)vm->cycles);
    
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
            if (i < 10) snprintf(name, sizeof(name), "R%d", i);
            else snprintf(name, sizeof(name), "R%c", 'A' + i - 10);
            printf("  %s = %.10g\n", name, v);
        }
    }
}

static void disassemble(MK56VM *vm) {
    printf("Disassembly (%zu bytes):\n\n", vm->program_size);
    printf("ADDR  BYTES     INSTRUCTION\n");
    printf("----  --------  -----------\n");
    
    uint16_t addr = 0;
    while (addr < vm->program_size) {
        char disasm[32];
        int size = vm_disasm(vm, addr, disasm, sizeof(disasm));
        
        // Print bytes
        printf("%03d   ", addr);
        for (int i = 0; i < size && i < 4; i++) {
            printf("%02X ", vm->program[addr + i]);
        }
        for (int i = size; i < 4; i++) {
            printf("   ");
        }
        printf("  %s\n", disasm);
        
        addr += size;
    }
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
        }
        else if (strcmp(argv[i], "-r") == 0 && i + 1 < argc) {
            // Will handle after VM init
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
    
    if (!vm_load_file(&vm, prog_path)) {
        fprintf(stderr, "Error: Cannot load program: %s\n", prog_path);
        return 1;
    }
    
    printf("Loaded: %s (%zu bytes)\n", prog_path, vm.program_size);
    
    // Handle -r options (set registers)
    for (int i = 1; i < argc; i++) {
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
                if (reg >= 0 && eq) {
                    vm.regs[reg] = atof(eq + 1);
                    printf("Set R%X = %g\n", reg, vm.regs[reg]);
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
