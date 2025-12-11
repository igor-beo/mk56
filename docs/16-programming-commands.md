# 16. Programming Commands Reference

## Overview

This document provides a comprehensive reference for all programming commands available on the MK-56 calculator.

## Command Categories

### 1. Mode Control Commands

| Command | Key Sequence | Description |
|---------|--------------|-------------|
| Enter Programming Mode | [ПРГ] | Toggle between Automatic and Programming modes |
| Exit Programming Mode | [ПРГ] | Return to Automatic mode |

### 2. Program Flow Control

#### Unconditional Jump

| Command | Key Sequence | Description | Example |
|---------|--------------|-------------|---------|
| Jump to address | [БП] [nn] | Jump program execution to address nn | [БП] [2] [5] jumps to address 25 |

**Usage**:
- Creates loops
- Skips code sections
- Implements program structure

**Address Range**: 00 to 99 (or 104 for extended memory)

#### Conditional Jumps

| Command | Key Sequence | Description | Condition |
|---------|--------------|-------------|-----------|
| Jump if X ≥ 0 | [x≥0] [nn] | Jump to address nn if X ≥ 0 | X register value ≥ 0 |
| Jump if X < 0 | [x<0] [nn] | Jump to address nn if X < 0 | X register value < 0 |

**Usage**:
- Conditional execution
- Loop termination
- Decision making

**Example**:
```
10: [x≥0] [2] [0]  ; If X ≥ 0, jump to address 20
11: [...]           ; Executed if X < 0
...
20: [...]           ; Executed if X ≥ 0
```

### 3. Subroutine Commands

| Command | Key Sequence | Description | Stack Effect |
|---------|--------------|-------------|--------------|
| Call subroutine | [В/О] [nn] | Call subroutine at address nn | Saves return address |
| Return | [В/О] | Return from subroutine | Restores return address |

**Usage**:
- Modular programming
- Code reuse
- Nested subroutines (limited depth)

**Example**:
```
Main Program:
00: [В/О] [5] [0]  ; Call subroutine at 50
01: [С/П]          ; Stop after return

Subroutine:
50: [x²]           ; Square X
51: [5]            ; Add 5
52: [+]
53: [В/О]          ; Return to address 01
```

### 4. Execution Control

| Command | Key Sequence | Description | Mode |
|---------|--------------|-------------|------|
| Stop program | [С/П] | Halt program execution | Programming |
| Continue program | [С/П] | Resume execution | Automatic (when stopped) |
| Start program | [В/О] | Start from address 00 | Automatic |

**Usage**:
- Pause for user input
- Display intermediate results
- Debug programs
- Mark program end

### 5. Memory Commands

#### Store Operations

| Command | Key Sequence | Description | Registers |
|---------|--------------|-------------|-----------|
| Store X to RGn | [x→П] [n] | Store X to register n | 0-9 |
| Store X to RG10-13 | [x→П] [•] [n] | Store X to register 10-13 | 0-3 (for RG10-13) |

#### Recall Operations

| Command | Key Sequence | Description | Registers |
|---------|--------------|-------------|-----------|
| Recall RGn to X | [П→x] [n] | Recall register n to X | 0-9 |
| Recall RG10-13 to X | [П→x] [•] [n] | Recall register 10-13 to X | 0-3 (for RG10-13) |

#### Memory Arithmetic

| Command | Key Sequence | Description | Effect |
|---------|--------------|-------------|--------|
| Add X to RGn | [П] [+] [n] | Add X to register n | RGn = RGn + X |
| Subtract X from RGn | [П] [−] [n] | Subtract X from register n | RGn = RGn - X |

**Usage in Programs**:
- Store intermediate results
- Implement counters
- Save constants
- Preserve values across operations

### 6. Arithmetic Commands

All arithmetic operations available in Automatic mode can be used in programs:

| Command | Key | Description | Operands |
|---------|-----|-------------|----------|
| Add | [+] | Addition | Y + X → X |
| Subtract | [−] | Subtraction | Y - X → X |
| Multiply | [×] | Multiplication | Y × X → X |
| Divide | [÷] | Division | Y ÷ X → X |

### 7. Mathematical Function Commands

All mathematical functions can be programmed:

#### Single-Operand Functions

| Function | Key Sequence | Description | Input | Output |
|----------|--------------|-------------|-------|--------|
| Square | [x²] | Square of X | X | X² |
| Square root | [√x] | Square root of X | X ≥ 0 | √X |
| Reciprocal | [1/x] | 1 divided by X | X ≠ 0 | 1/X |
| Power of 10 | [Г] [10ˣ] | 10 to power X | X | 10^X |
| Exponential | [Г] [eˣ] | e to power X | X | e^X |
| Decimal log | [Г] [lg] | Log base 10 | X > 0 | log₁₀(X) |
| Natural log | [Г] [ln] | Natural log | X > 0 | ln(X) |
| Sine | [Г] [sin] | Sine (radians) | X | sin(X) |
| Cosine | [Г] [cos] | Cosine (radians) | X | cos(X) |

#### Two-Operand Functions

| Function | Key | Description | Operands | Result |
|----------|-----|-------------|----------|--------|
| Power | [xʸ] | X to power Y | Y (base), X (exponent) | Y^X |

### 8. Stack Manipulation Commands

| Command | Key | Description | Effect |
|---------|-----|-------------|--------|
| Enter | [ВП] | Push X to stack | X→Y, Y→Z, Z→T |
| Exchange X and Y | [↔] | Swap X and Y | X↔Y |
| Clear X | [СХ] | Clear X register | X = 0 |

### 9. Data Entry Commands

In programs, you can enter constants:

| Command | Key | Description |
|---------|-----|-------------|
| Digit entry | [0]-[9] | Enter digit |
| Decimal point | [•] | Enter decimal point |
| Sign change | [/~/] | Change sign of mantissa or exponent |

**Example**: Enter constant 3.14159
```
10: [3]
11: [•]
12: [1]
13: [4]
14: [1]
15: [5]
16: [9]
```

### 10. Address Manipulation

#### Direct Addressing

Standard addressing uses two-digit addresses (00-99):
```
[БП] [2] [5]  ; Jump to address 25
```

#### Extended Addressing

For addresses 100-104 (if supported):
```
[БП] [1] [0] [0]  ; Jump to address 100
```

## Programming Patterns

### Pattern 1: Simple Loop

Decrementing counter loop:
```
00: [1] [0]        ; Initialize counter to 10
01: [x→П] [0]      ; Store in RG0
02: ...            ; Loop body
10: [П→x] [0]      ; Recall counter
11: [1]            ; Enter 1
12: [−]            ; Decrement
13: [x→П] [0]      ; Store counter
14: [x≥0] [0] [2]  ; If ≥ 0, loop back
15: [С/П]          ; Stop
```

### Pattern 2: Conditional Execution

If-then-else structure:
```
00: [x≥0] [1] [0]  ; If X ≥ 0, jump to "then" part
01: ...            ; "else" part
05: [БП] [2] [0]   ; Skip "then" part
10: ...            ; "then" part
20: ...            ; Continue
```

### Pattern 3: Subroutine with Parameters

Pass parameters via registers:
```
Main:
00: [5]            ; Parameter 1
01: [x→П] [0]      ; Store parameter
02: [3]            ; Parameter 2
03: [x→П] [1]      ; Store parameter
04: [В/О] [5] [0]  ; Call subroutine
05: [С/П]          ; Stop

Subroutine:
50: [П→x] [0]      ; Get parameter 1
51: [П→x] [1]      ; Get parameter 2
52: [+]            ; Add them
53: [В/О]          ; Return (result in X)
```

### Pattern 4: Nested Loops

Outer and inner loops:
```
00: [5]            ; Outer loop count
01: [x→П] [0]      ; Store outer counter
02: [3]            ; Inner loop count
03: [x→П] [1]      ; Store inner counter
04: ...            ; Inner loop body
10: [П→x] [1]      ; Decrement inner counter
11: [1]
12: [−]
13: [x→П] [1]
14: [x≥0] [0] [4]  ; Loop back if ≥ 0
15: [П→x] [0]      ; Decrement outer counter
16: [1]
17: [−]
18: [x→П] [0]
19: [x≥0] [0] [2]  ; Loop back if ≥ 0
20: [С/П]          ; Stop
```

## Command Execution Times

| Command Type | Typical Time |
|--------------|--------------|
| Jump commands | < 0.1 seconds |
| Memory operations | < 0.2 seconds |
| Arithmetic operations | < 0.5 seconds |
| Mathematical functions | 2-3.5 seconds |
| Subroutine call/return | < 0.2 seconds |

## Programming Tips

### 1. Efficient Memory Use
- Use registers for frequently accessed values
- Minimize register usage for longer programs
- Reuse registers when values no longer needed

### 2. Loop Optimization
- Place loop condition check at end for efficiency
- Use countdown loops (easier to test for zero)
- Minimize operations inside loops

### 3. Subroutine Design
- Keep subroutines focused and small
- Document parameter passing conventions
- Ensure proper return at end

### 4. Error Handling
- Check for division by zero before dividing
- Validate input ranges for functions
- Use conditional jumps to skip invalid operations

### 5. Debugging
- Use [С/П] to pause at key points
- Display intermediate values
- Test subroutines independently
- Verify loop counters

## Program Documentation

When documenting programs, include:

1. **Purpose**: What the program calculates
2. **Inputs**: Required input values and registers
3. **Outputs**: Result location and format
4. **Registers used**: Which registers are modified
5. **Program listing**: Step-by-step commands
6. **Example**: Sample calculation

## Related Documents

- [Programming Mode](07-programming-mode.md) - Programming mode operation
- [Calculation Examples](08-examples.md) - Example programs
- [Key Functions Reference](15-key-reference.md) - Key descriptions
- [Automatic Mode Operation](06-automatic-mode.md) - Basic operations
