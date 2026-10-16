# MK56-ASM Assembler

Assembles MK56-ASM (`.asm`) and original listings (`.mk56`) into МК-56
machine code. The output has one byte per program step, at most 98 steps.

```bash
make
./mk56asm program.asm                       # writes program.bin
./mk56asm program.mk56 -o out.bin -l out.lst
./mk56asm program.asm -v                    # print the listing
./mk56asm program.mk56 -s program.asm       # book listing -> MK56-ASM
```

| Option | Meaning |
|--------|---------|
| `-o FILE` | Output binary (default: input name with `.bin`) |
| `-l FILE` | Write a listing |
| `-s FILE` | Write the program as MK56-ASM source (`-` for stdout) |
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

## Converting a listing to MK56-ASM

`-s` writes any program, whatever its input syntax, as MK56-ASM: one step
per line, labels for jump targets (`L12`) and subroutines (`sub42`), and
digit runs as number literals. The comment on each line gives the address,
the keys as printed and the codes. The input's leading comments, including
test directives, are copied. The result is checked by reassembling it, and
`-s` fails if the program would change.

```
sub42:
        RCL RD          ; 42  ИПd            6D
        RCL RC          ; 43  ИПc            6C
        MUL             ; 44  ×              12
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
