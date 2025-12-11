# MK56-ASM Instruction Set Quick Reference

## Stack Operations

| Mnemonic | Description | Before | After |
|----------|-------------|--------|-------|
| `ENTER` | Push X to stack | T Z Y **X** | X **X** Y Z |
| `SWAP` | Exchange X, Y | T Z **Y** **X** | T Z **X** **Y** |
| `CLX` | Clear X | T Z Y **X** | T Z Y **0** |
| `ROLLDOWN` | Roll down | **T** Z Y X | X **T** Z Y |
| `ROLLUP` | Roll up | T Z Y **X** | Z Y X **T** |

## Arithmetic

| Mnemonic | Operation | Stack Effect |
|----------|-----------|--------------|
| `ADD` | Y + X → X | T T Z result |
| `SUB` | Y - X → X | T T Z result |
| `MUL` | Y × X → X | T T Z result |
| `DIV` | Y ÷ X → X | T T Z result |
| `CHS` | -X → X | unchanged except X |

## Math Functions

| Mnemonic | Function | Domain |
|----------|----------|--------|
| `SQ` | X² | all |
| `SQRT` | √X | X ≥ 0 |
| `INV` | 1/X | X ≠ 0 |
| `EXP` | eˣ | \|X\| < 230 |
| `EXP10` | 10ˣ | \|X\| < 100 |
| `LN` | ln(X) | X > 0 |
| `LOG` | log₁₀(X) | X > 0 |
| `SIN` | sin(X) | radians |
| `COS` | cos(X) | radians |
| `POW` | Y^X | varies |
| `PI` | push π | - |

## Memory

| Mnemonic | Description |
|----------|-------------|
| `STO Rn` | X → Register n |
| `RCL Rn` | Register n → X |
| `STO+ Rn` | Rn + X → Rn |
| `STO- Rn` | Rn - X → Rn |

**Registers**: R0-R9, RA, RB, RC, RD (14 total)

## Flow Control

| Mnemonic | Description |
|----------|-------------|
| `JMP addr` | Jump unconditionally |
| `JGE addr` | Jump if X ≥ 0 |
| `JLT addr` | Jump if X < 0 |
| `CALL addr` | Call subroutine |
| `RTN` | Return from subroutine |
| `HALT` | Stop program |
| `NOP` | No operation |

## Numeric Literals

```asm
42          ; integer
3.14159     ; decimal
-273.15     ; negative
6.022e23    ; scientific notation
```

## Directives

| Directive | Purpose |
|-----------|---------|
| `.ORG n` | Set address origin |
| `.EQU name val` | Define constant |
| `.END` | End of program |
| `.ASSERT cond` | Test assertion (emulator) |
| `.TRACE` | Debug dump (emulator) |

## Example: Factorial

```asm
; n! - factorial of n
; Input: n in X
; Output: n! in X

        STO R0          ; counter = n
        1               ; result = 1
        STO R1
loop:   RCL R0          ; get counter
        JGE cont        ; if >= 0, continue
        JMP done        ; else done
cont:   RCL R1          ; get result
        RCL R0          ; get counter
        MUL             ; result * counter
        STO R1          ; store result
        RCL R0          ; get counter
        1
        SUB             ; counter - 1
        STO R0          ; store counter
        JMP loop        ; repeat
done:   RCL R1          ; result to X
        HALT
```

## Cyrillic → ASCII Quick Map

| Cyrillic | ASCII |
|----------|-------|
| ИП/П→x | RCL |
| П/x→П | STO |
| БП | JMP |
| С/П | HALT |
| В/О | CALL/RTN |
| x≥0 | JGE |
| x<0 | JLT |
| ВП/↑ | ENTER |
| ↔/XY | SWAP |
| СХ | CLX |
