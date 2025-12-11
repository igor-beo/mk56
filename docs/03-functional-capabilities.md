# 3. Functional Capabilities

## Overview

The MK-56 "Elektronika" microcalculator provides comprehensive computational capabilities for scientific, engineering, and statistical calculations.

## 3.1 Number System and Range

### Decimal System
- **Base**: Decimal (base-10)
- **Input**: Digit keys 0-9
- **Display**: 12-digit indicator

### Number Range

**Mantissa**: 8 significant digits

**Exponent**: 2 digits (power of 10)

**Range**:
- **Minimum positive**: 1×10⁻⁹⁹
- **Maximum positive**: 9.9999999×10⁹⁹
- **Minimum negative**: -9.9999999×10⁹⁹
- **Maximum negative**: -1×10⁻⁹⁹

### Number Formats

1. **Fixed-point**: For numbers in range -9999999 to 9999999
   - Example: `1234.567`

2. **Scientific notation**: For numbers outside fixed-point range
   - Format: `±m.mmmmmmm ±EE`
   - Example: `1.2345678 50` represents 1.2345678×10⁵⁰

## 3.2 Arithmetic Operations

### Basic Operations

| Operation | Key | Description | Example |
|-----------|-----|-------------|---------|
| Addition | [+] | Add two numbers | 5 + 3 = 8 |
| Subtraction | [−] | Subtract two numbers | 9 - 4 = 5 |
| Multiplication | [×] | Multiply two numbers | 6 × 7 = 42 |
| Division | [÷] | Divide two numbers | 20 ÷ 4 = 5 |

### Operation Sequence
1. Enter first operand
2. Press [ВП] to push to stack
3. Enter second operand
4. Press operation key
5. Result displayed in register X

## 3.3 Mathematical Functions

### Single-Operand Functions

#### Power and Root Functions

| Function | Key Sequence | Description | Domain | Range |
|----------|--------------|-------------|--------|-------|
| x² | [x²] | Square | All real | x² ≥ 0 |
| √x | [√x] | Square root | x ≥ 0 | √x ≥ 0 |
| 1/x | [1/x] | Reciprocal | x ≠ 0 | All real |

#### Exponential Functions

| Function | Key Sequence | Description | Domain | Precision |
|----------|--------------|-------------|--------|-----------|
| 10ˣ | [Г] [10ˣ] | 10 to power x | \|x\| < 99.999999 | 4×10⁻⁷ |
| eˣ | [Г] [eˣ] | e to power x | \|x\| < 100·ln10 | 5×10⁻⁸ |

#### Logarithmic Functions

| Function | Key Sequence | Description | Domain | Precision |
|----------|--------------|-------------|--------|-----------|
| lg x | [Г] [lg] | Log base 10 | x > 0 | 3×10⁻⁷ |
| ln x | [Г] [ln] | Natural log | x > 0 | 3×10⁻⁷ |

#### Trigonometric Functions

**Note**: All angles are in **radians**.

| Function | Key Sequence | Description | Domain | Precision |
|----------|--------------|-------------|--------|-----------|
| sin x | [Г] [sin] | Sine | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |
| cos x | [Г] [cos] | Cosine | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |
| tg x | [Г] [tg] | Tangent | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |

#### Inverse Trigonometric Functions

| Function | Key Sequence | Description | Domain | Precision |
|----------|--------------|-------------|--------|-----------|
| arcsin x | [Г] [arcsin] | Arcsine | \|x\| ≤ 1 | 3×10⁻⁷ |
| arccos x | [Г] [arccos] | Arccosine | \|x\| ≤ 1 | 3×10⁻⁷ |
| arctg x | [Г] [arctg] | Arctangent | \|x\| ≤ 5.9999999×10⁹⁹ | 3×10⁻⁷ |

### Two-Operand Functions

#### Power Function

| Function | Key Sequence | Description | Usage |
|----------|--------------|-------------|-------|
| xʸ | [xʸ] | x to power y | Enter x, [ВП], enter y, [xʸ] |

**Example**: Calculate 2³
- Press: [2] [ВП] [3] [xʸ]
- Result: `8.`

## 3.4 Memory Operations

### Addressable Registers

The calculator provides **14 addressable registers** for data storage:

- **RG0 - RG9**: Directly accessible (10 registers)
- **RG10 - RG13**: Extended access (4 registers)
  - Also designated as RGA, RGБ, RGВ, RGГ

### Memory Commands

| Operation | Key Sequence | Description |
|-----------|--------------|-------------|
| Store to RGn | [x→П] [n] | Store X to register n (0-9) |
| Store to RG10-13 | [x→П] [•] [n] | Store X to register 10-13 (n=0-3) |
| Recall from RGn | [П→x] [n] | Recall register n to X (0-9) |
| Recall from RG10-13 | [П→x] [•] [n] | Recall register 10-13 to X (n=0-3) |
| Add to memory | [П] [+] [n] | Add X to register n |
| Subtract from memory | [П] [−] [n] | Subtract X from register n |

### Stack Registers

The calculator maintains a **4-level stack** for intermediate calculations:

- **X**: Display register (current value)
- **Y**: Second operand register
- **Z**: Third level
- **T**: Top level

**Stack Operations**:
- [ВП]: Push X to stack (X → Y, Y → Z, Z → T)
- [↔]: Exchange X and Y
- [СХ]: Clear X register

## 3.5 Programming Capabilities

### Program Memory

- **Capacity**: 105 program steps
- **Address range**: 00 to 104
- **Storage**: Non-volatile (retained when powered off)

### Programming Commands

| Command | Key Sequence | Description |
|---------|--------------|-------------|
| Enter programming | [ПРГ] | Toggle programming mode |
| Unconditional jump | [БП] [nn] | Jump to address nn |
| Conditional jump | [x≥0] [nn] | Jump if X ≥ 0 |
| Conditional jump | [x<0] [nn] | Jump if X < 0 |
| Call subroutine | [В/О] [nn] | Call subroutine at address nn |
| Return | [В/О] | Return from subroutine |
| Stop/Continue | [С/П] | Stop program or continue |

### Program Features

1. **Loops**: Using counters and conditional jumps
2. **Subroutines**: Modular code with call/return
3. **Conditional execution**: Based on register values
4. **Address calculation**: Dynamic jump addresses
5. **Nested calls**: Multiple subroutine levels

## 3.6 Display Features

### Display Format

**12-digit indicator**:
- 8 mantissa digits
- 2 exponent digits
- Mantissa sign indicator
- Exponent sign indicator

### Display Modes

1. **Normal mode**: Shows current value in X register
2. **Programming mode**: Shows current program address
3. **Error indication**: Special display for errors

### Number Representation

**Fixed-point**: `-9999999.` to `9999999.`

**Scientific**: `±m.mmmmmmm ±EE`

**Examples**:
- `123.45` - Fixed-point
- `1.2345678 50` - Scientific (1.2345678×10⁵⁰)
- `-5.6789012 -23` - Scientific negative (-5.6789012×10⁻²³)

## 3.7 Special Functions

### Sign Change

| Function | Key | Description |
|----------|-----|-------------|
| Change mantissa sign | [/~/] | Toggle sign of mantissa |
| Change exponent sign | [/~/] | Toggle sign of exponent (during entry) |

### Register Exchange

| Function | Key | Description |
|----------|-----|-------------|
| Exchange X and Y | [↔] | Swap contents of X and Y registers |

### Clear Functions

| Function | Key | Description |
|----------|-----|-------------|
| Clear X | [СХ] | Reset X register to 0 |
| Backspace | [←] | Delete last entered digit |

## 3.8 Execution Times

### Arithmetic Operations

- **Basic operations** (+, −, ×, ÷): < 0.5 seconds
- **1/x, x²**: ≤ 3.5 seconds
- **√x**: ≤ 3.5 seconds

### Mathematical Functions

- **Trigonometric** (sin, cos, tg, arcsin, arccos, arctg): ≤ 2 seconds
- **Logarithmic** (ln, lg): ≤ 2 seconds
- **Exponential** (eˣ, 10ˣ): ≤ 3.5 seconds
- **Power** (xʸ): Variable, depends on operands

## 3.9 Error Conditions

### Error Indicators

The calculator displays an error when:

1. **Division by zero**: Attempting x ÷ 0
2. **Invalid domain**: √(negative), ln(zero or negative)
3. **Overflow**: Result > 9.9999999×10⁹⁹
4. **Underflow**: Result < 1×10⁻⁹⁹
5. **Invalid operation**: Incompatible operation sequence

### Error Recovery

To clear an error:
1. Press [СХ] to clear X register
2. Re-enter correct values
3. Continue calculation

## 3.10 Precision and Accuracy

### Computational Precision

The calculator maintains:
- **Internal precision**: Higher than display precision
- **Display precision**: 8 significant digits
- **Rounding**: Automatic to 8 digits

### Relative Errors

See table in [Device Overview](02-device-overview.md) for detailed error specifications for each function.

### Accumulated Errors

In long calculations:
- Errors may accumulate
- Use intermediate rounding when appropriate
- Store and recall intermediate results to manage precision

## Related Documents

- [Key Functions Reference](15-key-reference.md) - Detailed key descriptions
- [Automatic Mode Operation](06-automatic-mode.md) - Using functions
- [Programming Mode](07-programming-mode.md) - Programming features
- [Calculation Examples](08-examples.md) - Practical examples
- [Device Overview](02-device-overview.md) - Technical specifications
