# MK56-ASM Language

Assembly language for the МК-56, and the original listing notation.

| File | Description |
|------|-------------|
| [MK56-ASM-SPEC.md](MK56-ASM-SPEC.md) | Language specification: syntax, listing notation, test directives |
| [INSTRUCTION-SET.md](INSTRUCTION-SET.md) | Every machine code, from the shared opcode table |
| [examples/](examples/) | Example programs with tests |

## The same program, two ways

A factorial loop in MK56-ASM:

```asm
; @input 5
; @expect X=120
        STO R0          ; R0 = n
        1
        STO R1          ; R1 = result
loop:   RCL R1
        RCL R0
        MUL
        STO R1
        LOOP0 loop      ; R0 - 1, repeat while not zero
        RCL R1
        HALT
```

The same program in the original listing notation:

```
; @input 5
; @expect X=120
00: П0 1 П1
03: ИП1 ИП0 × П1 FL0 03
09: ИП1 С/П
```

Both assemble to the same 11 steps:
`40 01 41 61 60 12 41 5D 03 61 50`.

## Running

```bash
make                                          # from the project root
./emulator/mk56emu asm/examples/factorial.asm -c -i 5   # Display: 120,
./emulator/mk56emu asm/examples/factorial.asm           # TUI
./assembler/mk56asm asm/examples/factorial.asm -l factorial.lst
make test                                     # all programs with @expect
```
