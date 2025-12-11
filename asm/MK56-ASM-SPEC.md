# MK56-ASM Language Specification

**Version**: 1.0.0  
**Target**: MK-56 "Elektronika" Programmable Calculator  
**Authors**: Winston (Architect), Amelia (Developer)  
**Date**: 2025-12-10

---

## 1. Overview

MK56-ASM is an assembly language for the MK-56 programmable calculator. It provides human-readable ASCII mnemonics that map directly to the calculator's native RPN (Reverse Polish Notation) instruction set.

### 1.1 Design Goals

1. **1:1 Mapping** - Each mnemonic corresponds to exactly one calculator keystroke/operation
2. **ASCII-Only** - No Cyrillic or special Unicode required
3. **Readable** - Clear, self-documenting instruction names
4. **Parseable** - Simple, unambiguous grammar for assembler/emulator
5. **Testable** - Support for assertions and debugging

### 1.2 Calculator Architecture

| Component | Specification |
|-----------|---------------|
| Program Memory | 105 steps (addresses 00-104) |
| Data Registers | 14 registers (R0-R9, RA, RB, RC, RD) |
| Stack | 4 levels (X, Y, Z, T) - RPN stack |
| Display | 8-digit mantissa, 2-digit exponent |
| Number Range | ±1×10⁻⁹⁹ to ±9.9999999×10⁹⁹ |

---

## 2. Syntax

### 2.1 General Format

```
[label:] [INSTRUCTION [operand]] [; comment]
```

- **Labels**: Optional, end with colon, define jump targets
- **Instructions**: Single mnemonic per line
- **Operands**: Register names, addresses, or numeric literals
- **Comments**: Start with `;` or `//`, continue to end of line

### 2.2 Examples

```asm
; This is a comment
start:          ; This is a label
        ENTER           ; Push X to stack
        STO R0          ; Store X to register 0
        JMP loop        ; Jump to label 'loop'
        42              ; Push numeric literal
        3.14159         ; Push floating-point literal
```

### 2.3 Case Sensitivity

- **Instructions**: Case-insensitive (`ENTER`, `Enter`, `enter` are equivalent)
- **Labels**: Case-sensitive (`Loop` ≠ `loop`)
- **Registers**: Case-insensitive (`R0`, `r0`, `RA`, `ra` are equivalent)

### 2.4 Numeric Literals

| Format | Example | Description |
|--------|---------|-------------|
| Integer | `42` | Pushed to X register |
| Decimal | `3.14159` | Floating-point literal |
| Scientific | `1.5e-3` | 1.5 × 10⁻³ |
| Negative | `-7.5` | Negative number |

### 2.5 Whitespace

- Leading/trailing whitespace ignored
- Multiple spaces treated as single separator
- Blank lines ignored
- Tab characters equivalent to spaces

---

## 3. Instruction Set

### 3.1 Stack Operations

| Mnemonic | Keystroke | Description | Stack Effect |
|----------|-----------|-------------|--------------|
| `ENTER` | [ВП] | Push X to stack | T←Z, Z←Y, Y←X |
| `SWAP` | [↔] | Exchange X and Y | X↔Y |
| `CLX` | [СХ] | Clear X register | X←0 |
| `ROLLDOWN` | [↓] | Roll stack down | X←Y←Z←T←X |
| `ROLLUP` | [↑] | Roll stack up | T←Z←Y←X←T |

### 3.2 Arithmetic Operations

| Mnemonic | Keystroke | Description | Operation |
|----------|-----------|-------------|-----------|
| `ADD` | [+] | Addition | X ← Y + X, drop |
| `SUB` | [−] | Subtraction | X ← Y - X, drop |
| `MUL` | [×] | Multiplication | X ← Y × X, drop |
| `DIV` | [÷] | Division | X ← Y ÷ X, drop |
| `CHS` | [/~/] | Change sign | X ← -X |

### 3.3 Mathematical Functions

| Mnemonic | Keystroke | Description | Domain |
|----------|-----------|-------------|--------|
| `SQ` | [x²] | Square | X ← X² |
| `SQRT` | [√x] | Square root | X ≥ 0 |
| `INV` | [1/x] | Reciprocal | X ≠ 0 |
| `POW` | [xʸ] | Power | X ← Y^X |
| `EXP` | [Г][eˣ] | Exponential | X ← e^X |
| `EXP10` | [Г][10ˣ] | Power of 10 | X ← 10^X |
| `LN` | [Г][ln] | Natural log | X > 0 |
| `LOG` | [Г][lg] | Log base 10 | X > 0 |
| `SIN` | [Г][sin] | Sine (radians) | any |
| `COS` | [Г][cos] | Cosine (radians) | any |
| `PI` | [π] | Push π | X ← 3.1415927 |

### 3.4 Memory Operations

| Mnemonic | Keystroke | Description | Example |
|----------|-----------|-------------|---------|
| `STO Rn` | [x→П][n] | Store X to register | `STO R0` |
| `RCL Rn` | [П→x][n] | Recall register to X | `RCL R5` |
| `STO+ Rn` | [П][+][n] | Add X to register | `STO+ R0` |
| `STO- Rn` | [П][−][n] | Subtract X from register | `STO- R1` |

**Register Names**:
- `R0` through `R9` - Registers 0-9
- `RA`, `RB`, `RC`, `RD` - Registers 10-13

### 3.5 Program Flow Control

| Mnemonic | Keystroke | Description | Example |
|----------|-----------|-------------|---------|
| `JMP addr` | [БП][nn] | Unconditional jump | `JMP 25`, `JMP loop` |
| `JGE addr` | [x≥0][nn] | Jump if X ≥ 0 | `JGE done` |
| `JLT addr` | [x<0][nn] | Jump if X < 0 | `JLT negative` |
| `CALL addr` | [В/О][nn] | Call subroutine | `CALL sqrt_sub` |
| `RTN` | [В/О] | Return from subroutine | `RTN` |
| `HALT` | [С/П] | Stop/pause program | `HALT` |
| `NOP` | - | No operation | `NOP` |

### 3.6 Data Entry (Numeric Literals)

Numbers can be entered directly as instructions:

```asm
        42              ; Push integer 42 to X
        3.14159         ; Push pi approximation
        -273.15         ; Push negative number
        6.022e23        ; Avogadro's number in scientific notation
```

---

## 4. Addressing Modes

### 4.1 Direct Addressing

Jump/call to specific address (00-104):

```asm
        JMP 25          ; Jump to address 25
        CALL 50         ; Call subroutine at address 50
```

### 4.2 Label Addressing

Jump/call to labeled location:

```asm
loop:   RCL R0
        1
        SUB
        STO R0
        JGE loop        ; Jump to 'loop' label if X ≥ 0
```

### 4.3 Register Addressing

Access registers by name:

```asm
        STO R0          ; Store to register 0
        STO RA          ; Store to register 10 (A)
        RCL RD          ; Recall from register 13 (D)
```

---

## 5. Assembler Directives

Directives control assembly but don't generate code:

| Directive | Description | Example |
|-----------|-------------|---------|
| `.ORG addr` | Set origin address | `.ORG 50` |
| `.EQU name value` | Define constant | `.EQU PI 3.14159` |
| `.END` | End of program | `.END` |

### 5.1 Testing/Debug Directives (Emulator Only)

| Directive | Description | Example |
|-----------|-------------|---------|
| `.ASSERT condition` | Verify condition | `.ASSERT X == 1.5` |
| `.TRACE` | Dump registers/stack | `.TRACE` |
| `.BREAK` | Breakpoint | `.BREAK` |
| `.INPUT value` | Simulate input | `.INPUT 5.0` |

---

## 6. Program Structure

### 6.1 Minimal Program

```asm
; Minimal MK56-ASM program
        SQ              ; Square the input
        HALT            ; Stop and display result
.END
```

### 6.2 Standard Program Template

```asm
; ============================================
; Program: [Name]
; Purpose: [Description]
; Input:   [What goes in X, registers, etc.]
; Output:  [What's in X when done]
; Registers Used: [R0, R1, etc.]
; ============================================

.ORG 0

start:
        ; Program body here
        HALT

; Subroutines (if any)
sub1:
        ; ...
        RTN

.END
```

---

## 7. Instruction Encoding

For emulator implementation, each instruction maps to an opcode:

| Opcode | Mnemonic | Opcode | Mnemonic |
|--------|----------|--------|----------|
| 0x00 | NOP | 0x20 | STO R0 |
| 0x01 | ENTER | 0x21 | STO R1 |
| 0x02 | SWAP | ... | ... |
| 0x03 | CLX | 0x30 | RCL R0 |
| 0x04 | ADD | 0x31 | RCL R1 |
| 0x05 | SUB | ... | ... |
| 0x06 | MUL | 0x40 | JMP |
| 0x07 | DIV | 0x41 | JGE |
| 0x08 | CHS | 0x42 | JLT |
| 0x10 | SQ | 0x43 | CALL |
| 0x11 | SQRT | 0x44 | RTN |
| 0x12 | INV | 0x45 | HALT |
| 0x13 | EXP | 0x50 | PI |
| 0x14 | LN | 0x60 | LITERAL |
| 0x15 | LOG | | |
| 0x16 | EXP10 | | |
| 0x17 | SIN | | |
| 0x18 | COS | | |
| 0x19 | POW | | |

---

## 8. Error Handling

### 8.1 Assembly Errors

| Error | Description |
|-------|-------------|
| `UNDEFINED_LABEL` | Label referenced but not defined |
| `DUPLICATE_LABEL` | Same label defined twice |
| `INVALID_REGISTER` | Unknown register name |
| `ADDRESS_OUT_OF_RANGE` | Address > 104 |
| `INVALID_INSTRUCTION` | Unknown mnemonic |

### 8.2 Runtime Errors (Emulator)

| Error | Description |
|-------|-------------|
| `DIV_BY_ZERO` | Division by zero |
| `SQRT_NEGATIVE` | Square root of negative |
| `LOG_DOMAIN` | Log of zero or negative |
| `OVERFLOW` | Result > 9.9999999×10⁹⁹ |
| `UNDERFLOW` | Result < 1×10⁻⁹⁹ |
| `STACK_ERROR` | Invalid stack operation |

---

## 9. Translation Reference

### 9.1 Cyrillic to MK56-ASM

| Original | MK56-ASM | Description |
|----------|----------|-------------|
| `ИП N` / `П→x N` | `RCL Rn` | Recall register |
| `П N` / `x→П N` | `STO Rn` | Store to register |
| `БП` | `JMP` | Unconditional jump |
| `С/П` | `HALT` | Stop/run |
| `В/О nn` | `CALL` | Call subroutine |
| `В/О` | `RTN` | Return |
| `x≥0` / `Fx≥0` | `JGE` | Jump if ≥ 0 |
| `x<0` / `Fx<0` | `JLT` | Jump if < 0 |
| `ВП` / `↑` | `ENTER` | Push to stack |
| `↔` / `XY` | `SWAP` | Exchange X,Y |
| `СХ` | `CLX` | Clear X |
| `Feˣ` | `EXP` | Exponential |
| `F1/x` | `INV` | Reciprocal |
| `F√` / `√x` | `SQRT` | Square root |
| `Fx²` / `x²` | `SQ` | Square |
| `Fπ` | `PI` | Push π |
| `Fsin` | `SIN` | Sine |
| `Fcos` | `COS` | Cosine |
| `Fln` | `LN` | Natural log |
| `Flg` | `LOG` | Log base 10 |
| `/−/` | `CHS` | Change sign |

---

## 10. Related Documents

- [INSTRUCTION-SET.md](INSTRUCTION-SET.md) - Quick reference card
- [examples/](examples/) - Translated example programs
- [../docs/16-programming-commands.md](../docs/16-programming-commands.md) - Original MK-56 commands
- [../programs/](../programs/) - Original B3-34 style programs

---

## Appendix A: Complete Instruction List (Alphabetical)

```
ADD     - Addition (Y + X → X)
CALL    - Call subroutine
CHS     - Change sign
CLX     - Clear X register
COS     - Cosine
DIV     - Division (Y ÷ X → X)
ENTER   - Push X to stack
EXP     - Exponential (e^X)
EXP10   - Power of 10 (10^X)
HALT    - Stop program
INV     - Reciprocal (1/X)
JGE     - Jump if X ≥ 0
JLT     - Jump if X < 0
JMP     - Unconditional jump
LN      - Natural logarithm
LOG     - Logarithm base 10
MUL     - Multiplication (Y × X → X)
NOP     - No operation
PI      - Push π constant
POW     - Power (Y^X → X)
RCL     - Recall from register
RTN     - Return from subroutine
SIN     - Sine
SQ      - Square (X² → X)
SQRT    - Square root
STO     - Store to register
STO+    - Add to register
STO-    - Subtract from register
SUB     - Subtraction (Y - X → X)
SWAP    - Exchange X and Y
```
