# Assembly Language Reference

## Syntax Overview

```asm
[label:] [INSTRUCTION [operand]] [; comment]
```

## Stack Operations

| Mnemonic | Description | Stack Effect |
|----------|-------------|--------------|
| `ENTER` | Push X to stack | T←Z, Z←Y, Y←X |
| `SWAP` | Exchange X and Y | X↔Y |
| `CLX` | Clear X register | X←0 |
| `ROLLDOWN` | Roll stack down | X←Y←Z←T←X |
| `ROLLUP` | Roll stack up | T←Z←Y←X←T |

## Arithmetic

| Mnemonic | Operation | Notes |
|----------|-----------|-------|
| `ADD` | X ← Y + X | Drops stack |
| `SUB` | X ← Y - X | Drops stack |
| `MUL` | X ← Y × X | Drops stack |
| `DIV` | X ← Y ÷ X | Error if X=0 |
| `CHS` | X ← -X | Change sign |

## Math Functions

| Mnemonic | Function | Domain |
|----------|----------|--------|
| `SQ` | X² | All |
| `SQRT` | √X | X ≥ 0 |
| `INV` | 1/X | X ≠ 0 |
| `POW` | Y^X | Varies |
| `EXP` | e^X | \|X\| < 230 |
| `EXP10` | 10^X | \|X\| < 100 |
| `LN` | ln(X) | X > 0 |
| `LOG` | log₁₀(X) | X > 0 |
| `SIN` | sin(X) | Radians |
| `COS` | cos(X) | Radians |
| `PI` | Push π | - |

## Memory Operations

| Mnemonic | Description |
|----------|-------------|
| `STO Rn` | Store X to register n |
| `RCL Rn` | Recall register n to X |
| `STO+ Rn` | Add X to register n |
| `STO- Rn` | Subtract X from register n |

**Registers**: R0-R9, RA, RB, RC, RD (14 total)

## Flow Control

| Mnemonic | Description |
|----------|-------------|
| `JMP addr` | Unconditional jump |
| `JGE addr` | Jump if X ≥ 0 |
| `JLT addr` | Jump if X < 0 |
| `CALL addr` | Call subroutine |
| `RTN` | Return from subroutine |
| `HALT` | Stop program |
| `NOP` | No operation |

## Directives

| Directive | Purpose |
|-----------|---------|
| `.ORG n` | Set origin address |
| `.EQU name val` | Define constant |
| `.END` | End of program |

## Numeric Literals

```asm
42          ; Integer
3.14159     ; Decimal
-273.15     ; Negative
6.022e23    ; Scientific notation
```

## Labels

```asm
loop:       ; Define label
        RCL R0
        JGE loop    ; Reference label
```

Labels are case-sensitive.
