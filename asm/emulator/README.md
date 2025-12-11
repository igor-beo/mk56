# MK-56 Emulator

A feature-rich emulator for the MK-56 programmable calculator with a **Turbo C style** TUI (ncurses) and console mode.

## Features

- **Full MK-56 instruction set** - All opcodes, math functions, flow control
- **Turbo C style TUI** - Classic DOS-era aesthetic with popup dialogs
- **Dropdown menus** - File, Run, Debug, Help menus
- **Console mode** - Batch execution for automated testing
- **Debugging** - Breakpoints, single-stepping, state inspection
- **Disassembler** - Built-in program disassembly

## Requirements

- C11 compatible compiler (gcc, clang)
- ncurses library
- Math library (-lm)

## Building

```bash
# Using Make
make

# Or manually
gcc -O2 -Wall -std=c11 -o mk56emu mk56emu.c mk56ui.c main.c -lm -lncurses

# Clean
make clean
```

## Usage

### TUI Mode (Interactive)

```bash
./mk56emu program.bin
```

### Console Mode (Batch)

```bash
# Run with input value
./mk56emu program.bin -c -i 5

# Set registers before execution
./mk56emu program.bin -c -r R0=10 -r R8=3.14

# Disassemble only (no execution)
./mk56emu program.bin -d
```

## Command Line Options

| Option | Description |
|--------|-------------|
| `-c` | Console mode (no TUI) |
| `-i VALUE` | Input value to X register |
| `-r Rn=VAL` | Set register value (e.g., `-r R0=5`) |
| `-d` | Disassemble and exit |
| `-h` | Show help message |

## TUI Interface

The emulator features a classic Borland Turbo C style interface:

```
  File  Run  Debug  Help                    MK-56 Emulator
┌────── Stack ───────┐┌─────────────────── Program ───────────────────┐
│                    ││ >000: STO  R0                                 │
│ X:           120   ││  001: PUSH 1                                  │
│ Y:            -1   ││  010: STO  R1                                 │
│ Z:             0   ││ *011: RCL  R0          <- breakpoint          │
│ T:           120   ││  012: PUSH 1                                  │
├────────────────────┤│  ...                                          │
│ LastX:          1  ││                                               │
└────────────────────┘│                                               │
┌──── Registers ─────┐│                                               │
│                    ││                                               │
│ R0:    0  R7:    0 ││                                               │
│ R1:  120  R8:    5 ││                                               │
│ ...                ││                                               │
└────────────────────┘└───────────────────────────────────────────────┘
 F1Help SpcStep rRun RReset Input Edit Break Quit    [HALTED] PC:052
```

### Popup Dialogs

Input dialogs appear as popup windows with shadows:

```
        ┌────────── Input Value ──────────┐
        │                                 │
        │ Enter value for X register:     │
        │ ┌─────────────────────────────┐ │
        │ │ 3.14159_                    │ │
        │ └─────────────────────────────┘ │
        │     [ OK ]      [ Cancel ]      │
        └─────────────────────────────────┘
          ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓   <- shadow
```

### Key Bindings

| Key | Action |
|-----|--------|
| `F1` / `?` | Help dialog |
| `Space` / `s` | Step one instruction |
| `r` | Run until halt/breakpoint |
| `R` | Reset VM (keep program) |
| `I` | Input value to X (popup dialog) |
| `E` | Edit register (popup dialog) |
| `B` | Toggle breakpoint at PC |
| `C` | Clear all breakpoints |
| `↑` / `↓` | Scroll program view |
| `PgUp` / `PgDn` | Scroll by page |
| `G` | Go to PC |
| `0-9` | Quick digit input to X |
| `Q` | Quit |

### Menu Keys

| Key | Menu |
|-----|------|
| `F` | File menu |
| `D` | Debug menu |
| `H` | Help menu |
| `←` / `→` | Switch menus (when open) |
| `Enter` / `ESC` | Close menu |

## Example Session

```bash
# Compute 5! (factorial)
$ ./mk56emu factorial.bin -c -i 5

Loaded: factorial.bin (53 bytes)
Input: X = 5
Running program (53 bytes)...

=== Execution Complete ===
State: HALTED
Cycles: 79

Stack:
  X = 120
  Y = -1
  Z = 0
  T = 120

Registers (non-zero):
  R1 = 120
```

## Project Structure

```
emulator/
├── mk56emu.h       # VM structures, opcodes, API
├── mk56emu.c       # Core emulator engine
├── mk56ui.c        # ncurses TUI
├── main.c          # CLI entry point
├── Makefile        # Build configuration
└── README.md       # This file
```

## API

The emulator can be embedded in other programs:

```c
#include "mk56emu.h"

MK56VM vm;

// Initialize
vm_init(&vm);

// Load program
vm_load_file(&vm, "program.bin");

// Set input
vm_input(&vm, 5.0);

// Run
vm_run(&vm);

// Get result
double result = vm_get_x(&vm);
printf("Result: %g\n", result);
```

### API Functions

| Function | Description |
|----------|-------------|
| `vm_init()` | Initialize VM state |
| `vm_load()` | Load binary from memory |
| `vm_load_file()` | Load binary from file |
| `vm_reset()` | Reset VM (keep program) |
| `vm_step()` | Execute one instruction |
| `vm_run()` | Run until halt/break |
| `vm_input()` | Push value to X |
| `vm_get_x()` | Get X register |
| `vm_get_stack()` | Get stack value |
| `vm_get_reg()` | Get register value |
| `vm_set_breakpoint()` | Set/clear breakpoint |
| `vm_disasm()` | Disassemble instruction |
| `vm_error_str()` | Get error message |

## Error Handling

| Error | Description |
|-------|-------------|
| `ERR_DIV_ZERO` | Division by zero |
| `ERR_SQRT_NEG` | Square root of negative |
| `ERR_LOG_DOMAIN` | Log of zero/negative |
| `ERR_OVERFLOW` | Result overflow |
| `ERR_INVALID_OPCODE` | Unknown instruction |
| `ERR_CALL_OVERFLOW` | Call stack full |
| `ERR_PC_OVERFLOW` | PC out of bounds |

## Testing

```bash
# Run built-in tests
make test

# Test specific programs
./mk56emu ../examples/sinh.bin -c -i 1       # sinh(1) = 1.1752
./mk56emu ../examples/factorial.bin -c -i 5   # 5! = 120
./mk56emu ../examples/det2x2.bin -c -r R8=5 -r R9=4 -r R5=1.5 -r R6=3  # = 9
```

## Related Files

- [MK56-ASM-SPEC.md](../MK56-ASM-SPEC.md) - Assembly language specification
- [assembler-c/](../assembler-c/) - C assembler
- [assembler-python/](../assembler-python/) - Python assembler
- [examples/](../examples/) - Example programs
