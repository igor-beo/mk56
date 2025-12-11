# MK56-ASM Assembler (C)

A high-performance C implementation of the MK56-ASM assembler for the MK-56 programmable calculator.

## Features

- Full MK56-ASM language support
- Fast two-pass assembly
- Label resolution with byte-accurate addressing
- Assembly listing generation
- Compact binary (~35KB)
- No external dependencies

## Requirements

- C11 compatible compiler (gcc, clang)
- Make (optional, for build automation)

## Building

```bash
# Using Make
make

# Or manually with gcc
gcc -O2 -Wall -std=c11 -o mk56asm mk56asm.c main.c -lm

# Clean build artifacts
make clean
```

## Usage

```bash
# Basic assembly
./mk56asm input.asm

# With custom output file
./mk56asm input.asm -o output.bin

# Generate listing file
./mk56asm input.asm -l listing.lst

# Verbose output
./mk56asm input.asm -v

# All options combined
./mk56asm input.asm -o program.bin -l program.lst -v
```

## Command Line Options

| Option | Description |
|--------|-------------|
| `-o FILE` | Output binary file (default: input.bin) |
| `-l FILE` | Generate assembly listing file |
| `-v` | Verbose output with debug info |
| `-h` | Show help message |

## Example

```bash
$ ./mk56asm ../examples/sinh.asm -v -l sinh.lst

Assembling: ../examples/sinh.asm
  Parsed 7 instructions
  Found 1 labels
Output: ../examples/sinh.bin (15 bytes)
Listing: sinh.lst

Assembly Listing:
ADDR  BYTES                 SOURCE
======================================================================
000  24                            EXP             ; e^x
001  01                            ENTER           ; duplicate
002  22                            INV             ; X = 1/e^x
003  11                            SUB             ; X = e^x - 1/e^x
004  80 00 00 00 00 00 00 00       2               ; push 2
013  13                            DIV             ; divide by 2
014  75                            HALT            ; result in X
```

## Project Structure

```
assembler-c/
├── mk56asm.h       # Header: opcodes, structures, API
├── mk56asm.c       # Core assembler implementation
├── main.c          # CLI entry point
├── Makefile        # Build configuration
└── README.md       # This file
```

## API

The assembler exposes a clean C API:

```c
#include "mk56asm.h"

Assembler as;

// Initialize
asm_init(&as);

// Assemble source code
if (asm_assemble(&as, source_code)) {
    // Get binary output
    size_t size;
    const uint8_t *binary = asm_get_binary(&as, &size);
    
    // Get listing
    char listing[8192];
    asm_get_listing(&as, listing, sizeof(listing));
} else {
    // Handle error
    printf("Error: %s\n", asm_get_error(&as));
}
```

## Binary Format

| Instruction Type | Size | Format |
|-----------------|------|--------|
| Simple opcode | 1 byte | `[opcode]` |
| Register op | 1 byte | `[opcode + reg]` |
| Jump/Call | 2 bytes | `[opcode] [address]` |
| Literal | 9 bytes | `[0x80] [8-byte double LE]` |

## Testing

```bash
# Run built-in tests
make test
```

## Related Files

- [MK56-ASM-SPEC.md](../MK56-ASM-SPEC.md) - Language specification
- [INSTRUCTION-SET.md](../INSTRUCTION-SET.md) - Quick reference
- [assembler-python/](../assembler-python/) - Python implementation
- [emulator/](../emulator/) - MK-56 emulator
