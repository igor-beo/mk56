# MK56-ASM Assembler (Python)

A Python implementation of the MK56-ASM assembler for the MK-56 programmable calculator.

## Features

- Full MK56-ASM language support
- Label resolution with byte-accurate addressing
- Assembly listing generation
- Verbose debug output
- Cross-platform (Python 3.6+)

## Requirements

- Python 3.6 or higher
- No external dependencies (stdlib only)

## Usage

```bash
# Basic assembly
python3 mk56asm.py input.asm

# With custom output file
python3 mk56asm.py input.asm -o output.bin

# Generate listing file
python3 mk56asm.py input.asm -l listing.lst

# Verbose output
python3 mk56asm.py input.asm -v

# All options combined
python3 mk56asm.py input.asm -o program.bin -l program.lst -v
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
$ python3 mk56asm.py ../examples/sinh.asm -v -l sinh.lst

Assembling: ../examples/sinh.asm
  Tokenized 10 lines
  Parsed 7 instructions
  Labels: {'sinh': 0}
  Generated 15 bytes
Output: ../examples/sinh.bin (15 bytes)
Listing: sinh.lst

Assembly Listing:
ADDR  BYTES                 LABEL        SOURCE
======================================================================
000  24                     sinh:        EXP             ; e^x
001  01                                  ENTER           ; duplicate
002  22                                  INV             ; X = 1/e^x
003  11                                  SUB             ; X = e^x - 1/e^x
004  80 00 00 00 00 00 00 00 40          2               ; push 2
013  13                                  DIV             ; divide by 2
014  75                                  HALT            ; result in X
```

## Binary Format

The assembler outputs a binary file with the following encoding:

| Instruction Type | Size | Format |
|-----------------|------|--------|
| Simple opcode | 1 byte | `[opcode]` |
| Register op | 1 byte | `[opcode + reg]` |
| Jump/Call | 2 bytes | `[opcode] [address]` |
| Literal | 9 bytes | `[0x80] [8-byte double LE]` |

## API Usage

The assembler can also be used as a Python module:

```python
from mk56asm import Lexer, Parser, Assembler

source = """
        1
        2
        ADD
        HALT
"""

# Tokenize
lexer = Lexer(source)
tokenized = lexer.tokenize()

# Parse
parser = Parser()
instructions = parser.parse(tokenized, source.split('\n'))

# Assemble
assembler = Assembler(instructions, parser.labels)
binary = assembler.assemble()

print(f"Generated {len(binary)} bytes")
print(assembler.get_listing())
```

## Related Files

- [MK56-ASM-SPEC.md](../MK56-ASM-SPEC.md) - Language specification
- [INSTRUCTION-SET.md](../INSTRUCTION-SET.md) - Quick reference
- [assembler-c/](../assembler-c/) - C implementation
- [emulator/](../emulator/) - MK-56 emulator
