# MK56-ASM Assembler

Assembles MK56-ASM (`.asm`) and original listings (`.mk56`) into МК-56
machine code. The output has one byte per program step, at most 98 steps.

```bash
make
./mk56asm program.asm                       # writes program.bin
./mk56asm program.mk56 -o out.bin -l out.lst
./mk56asm program.asm -v                    # print the listing
```

| Option | Meaning |
|--------|---------|
| `-o FILE` | Output binary (default: input name with `.bin`) |
| `-l FILE` | Write a listing |
| `-v` | Verbose; prints the listing |

The file extension picks the syntax: `.mk56` is the original listing
notation, and anything else is MK56-ASM. See the
[language spec](../asm/MK56-ASM-SPEC.md).

## Listing

```
ADDR  CODES             KEYS                      SOURCE
00    16                Feˣ                       EXP             ; e^x
01    0E                В↑                        ENTER           ; duplicate: Y=e^x, X=e^x
02    23                F1/x                      INV             ; X = 1/e^x
03    11                −                         SUB             ; X = e^x - 1/e^x
04    02                2                         2               ; push 2
05    13                ÷                         DIV             ; X = (e^x - 1/e^x) / 2
06    50                С/П                       HALT            ; stop, result in X
```

## Errors

The assembler stops at the first error and reports its line:

```
Assembly error: Line 3: Address mismatch: 12: is at address 11
Assembly error: Line 7: ROLLUP is not an MK-56 instruction
Assembly error: Line 9: Unknown key: ИП
```

## Library

`mk56asm.h` is also used by the emulator, which assembles `.asm` and `.mk56`
files on load, and by the TUI editor, which uses `asm_encode_line()` for a
single statement. Opcodes come from [`common/mk56_isa.c`](../common/mk56_isa.c).
