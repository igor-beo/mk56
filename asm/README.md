# MK-56 Development Environment

A complete development environment for the MK-56 programmable calculator, including an assembly language, assemblers, and an emulator.

## Overview

```
.asm source  ──▶  assembler  ──▶  .bin binary  ──▶  emulator  ──▶  result
```

## Components

| Component | Language | Description |
|-----------|----------|-------------|
| [MK56-ASM-SPEC.md](MK56-ASM-SPEC.md) | - | Assembly language specification |
| [INSTRUCTION-SET.md](INSTRUCTION-SET.md) | - | Quick reference card |
| [assembler-c/](assembler-c/) | C | High-performance assembler |
| [assembler-python/](assembler-python/) | Python | Cross-platform assembler |
| [emulator/](emulator/) | C | Interactive emulator with TUI |
| [examples/](examples/) | MK56-ASM | Example programs |

## Quick Start

### 1. Build the Tools

```bash
# Build C assembler
cd assembler-c && make && cd ..

# Build emulator
cd emulator && make && cd ..
```

### 2. Write a Program

```asm
; square.asm - Calculate x²
        SQ              ; Square X
        HALT            ; Stop
.END
```

### 3. Assemble

```bash
# Using C assembler
./assembler-c/mk56asm square.asm

# Or using Python assembler
python3 assembler-python/mk56asm.py square.asm
```

### 4. Run

```bash
# Interactive TUI
./emulator/mk56emu square.bin

# Console mode with input
./emulator/mk56emu square.bin -c -i 5
# Result: X = 25
```

## Directory Structure

```
asm/
├── README.md               # This file
├── MK56-ASM-SPEC.md        # Language specification
├── INSTRUCTION-SET.md      # Quick reference
│
├── assembler-c/            # C assembler
│   ├── README.md
│   ├── mk56asm.h           # Header/API
│   ├── mk56asm.c           # Core implementation
│   ├── main.c              # CLI
│   └── Makefile
│
├── assembler-python/       # Python assembler
│   ├── README.md
│   └── mk56asm.py          # Single-file implementation
│
├── emulator/               # MK-56 emulator
│   ├── README.md
│   ├── mk56emu.h           # VM structures/API
│   ├── mk56emu.c           # Core emulator
│   ├── mk56ui.c            # ncurses TUI
│   ├── main.c              # CLI
│   └── Makefile
│
└── examples/               # Example programs
    ├── sinh.asm            # Hyperbolic sine
    ├── cosh.asm            # Hyperbolic cosine
    ├── arsinh.asm          # Inverse hyperbolic sine
    ├── factorial.asm       # n! calculation
    ├── det2x2.asm          # 2×2 matrix determinant
    ├── quadratic.asm       # Quadratic equation solver
    └── sum_integers.asm    # Sum 1+2+...+n
```

## MK56-ASM Language

### Instruction Categories

| Category | Instructions |
|----------|--------------|
| Stack | `ENTER`, `SWAP`, `CLX`, `ROLLDOWN`, `ROLLUP` |
| Arithmetic | `ADD`, `SUB`, `MUL`, `DIV`, `CHS` |
| Math | `SQ`, `SQRT`, `INV`, `POW`, `EXP`, `LN`, `LOG`, `SIN`, `COS`, `PI` |
| Memory | `STO Rn`, `RCL Rn`, `STO+ Rn`, `STO- Rn` |
| Flow | `JMP`, `JGE`, `JLT`, `CALL`, `RTN`, `HALT` |

### Example Program

```asm
; Factorial: n! = 1 × 2 × ... × n
; Input: n in X
; Output: n! in X

        STO R0          ; R0 = counter
        1
        STO R1          ; R1 = result

loop:
        RCL R0
        1
        SUB
        JLT done        ; if counter < 1, done
        STO R0
        RCL R1
        RCL R0
        1
        ADD
        MUL
        STO R1
        JMP loop

done:
        RCL R1          ; result to X
        HALT

.END
```

## Testing

```bash
# Test all example programs
cd emulator
./mk56emu ../examples/sinh.bin -c -i 1       # sinh(1) ≈ 1.1752
./mk56emu ../examples/factorial.bin -c -i 5   # 5! = 120
./mk56emu ../examples/factorial.bin -c -i 10  # 10! = 3628800
```

## Calculator Specifications

| Feature | Value |
|---------|-------|
| Program steps | 105 max |
| Registers | 14 (R0-R9, RA-RD) |
| Stack levels | 4 (X, Y, Z, T) |
| Number range | ±10⁻⁹⁹ to ±10⁹⁹ |
| Precision | 8 significant digits |

## License

Part of the MK-56 documentation and tools project.
