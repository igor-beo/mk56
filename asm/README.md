# MK56-ASM Language

Assembly language specification and examples for the MK-56 programmable calculator.

## Contents

| File | Description |
|------|-------------|
| [MK56-ASM-SPEC.md](MK56-ASM-SPEC.md) | Complete language specification |
| [INSTRUCTION-SET.md](INSTRUCTION-SET.md) | Quick reference card |
| [examples/](examples/) | Example programs |

## Quick Reference

### Instruction Categories

| Category | Instructions |
|----------|--------------|
| **Stack** | `ENTER`, `SWAP`, `CLX`, `ROLLDOWN`, `ROLLUP` |
| **Arithmetic** | `ADD`, `SUB`, `MUL`, `DIV`, `CHS` |
| **Math** | `SQ`, `SQRT`, `INV`, `POW`, `EXP`, `LN`, `LOG`, `SIN`, `COS`, `PI` |
| **Memory** | `STO Rn`, `RCL Rn`, `STO+ Rn`, `STO- Rn` |
| **Flow** | `JMP`, `JGE`, `JLT`, `CALL`, `RTN`, `HALT` |

### Example

```asm
; factorial.asm - Calculate n!
; Input: n in X
; Output: n! in X

        STO R0          ; R0 = counter
        1
        STO R1          ; R1 = result

loop:   RCL R0
        1
        SUB
        JLT done
        STO R0
        RCL R1
        RCL R0
        1
        ADD
        MUL
        STO R1
        JMP loop

done:   RCL R1
        HALT

.END
```

## Tools

- **Assembler**: `../assembler/` - Compiles `.asm` to `.bin`
- **Emulator**: `../emulator/` - Runs `.bin` files

## Testing Examples

```bash
# From project root
./assembler/mk56asm asm/examples/factorial.asm -o factorial.bin
./emulator/mk56emu factorial.bin -c -i 5    # Result: 120
```

## Related Documentation

- [Device Documentation](../docs/) - Complete MK-56 technical documentation
- [Program Library](../programs/) - Mathematical programs from Dyakonov's reference
