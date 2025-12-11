# 6. Automatic Mode Operation

## Overview

Automatic mode is the primary operating mode for performing calculations directly on the MK-56. In this mode, operations are executed immediately when keys are pressed, and results are displayed instantly.

## 5.1 Calculation Modes

The calculator operates in two calculation modes within Automatic mode:

### 5.1.1 Computational Mode
- Direct execution of arithmetic and mathematical operations
- Immediate display of results
- Interactive calculation workflow

### 5.1.2 Display Mode on Indicator

Numbers are displayed on the 12-digit indicator showing:
- 8 mantissa digits
- 2 exponent digits  
- Sign indicators

## 5.2 Number Display on Indicator

The indicator displays numbers in the following formats:

### Fixed-Point Notation
For numbers within normal range: `-9999999` to `9999999`

Example: `1234.567` displays as `1234.567`

### Scientific Notation  
For numbers outside normal range:

- **Format**: `±m.mmmmmmm ±EE`
- **Mantissa**: 8 significant digits
- **Exponent**: 2 digits with sign

Example: `1.2345678×10⁵⁰` displays as `1.2345678 50`

## 5.3 Number Entry

### Basic Number Entry

To enter a number:

1. Press digit keys [0]-[9] to enter digits
2. Press [•] to enter decimal point
3. The number appears in register X as you type

**Example**: To enter `123.45`:
- Press: [1] [2] [3] [•] [4] [5]
- Display shows: `123.45`

### Entering Numbers with Exponents

To enter numbers in scientific notation:

1. Enter the mantissa (up to 8 digits)
2. Press [ВП] (Enter)
3. Enter the exponent value
4. Press [/~/] if exponent is negative

**Example**: To enter `5.2×10⁻³`:
- Press: [5] [•] [2] [ВП] [3] [/~/]
- Display shows: `5.2 -03`

## 5.4 Incorrect Operations and Overflow

### Error Indication

When an incorrect operation occurs or a result exceeds the calculator's range, an error is indicated on the display.

**Error conditions include**:
- Division by zero
- Square root of negative number
- Logarithm of zero or negative number
- Result overflow (|x| ≥ 10¹⁰⁰)
- Result underflow (|x| < 10⁻⁹⁹)

### Clearing Errors

To clear an error and continue:
1. Press [СХ] to clear register X
2. Re-enter the correct values
3. Continue calculation

## 5.5 Single-Operand Operations

Single-operand operations work on the value currently in register X.

### Available Functions

- **[x²]**: Square
- **[√x]**: Square root
- **[1/x]**: Reciprocal
- **[Г] [10ˣ]**: 10 to the power x
- **[Г] [eˣ]**: e to the power x
- **[Г] [lg]**: Decimal logarithm
- **[Г] [ln]**: Natural logarithm
- **[Г] [sin]**: Sine
- **[Г] [cos]**: Cosine

### Operation Sequence

1. Enter the number
2. Press the function key
3. Result appears in register X

**Example**: Calculate √16
- Press: [1] [6] [√x]
- Display shows: `4.`

**Example**: Calculate sin(30°) - Note: angles must be in radians
- Convert 30° to radians: 30 × π/180 ≈ 0.5236
- Press: [0] [•] [5] [2] [3] [6] [Г] [sin]
- Display shows: `0.5` (approximately)

## 5.6 Two-Operand Operations

Two-operand operations require two numbers and work with registers X and Y.

### Available Operations

- **[+]**: Addition
- **[−]**: Subtraction
- **[×]**: Multiplication
- **[÷]**: Division
- **[xʸ]**: Power function

### Operation Sequence

When performing two-operand operations, the calculator operates with a number in register X and a number in register Y. The information in the stack registers is transferred following the operation.

1. Enter first number (goes to register X)
2. Press [ВП] (transfers X to Y, prepares for next number)
3. Enter second number (goes to register X)
4. Press operation key
5. Result appears in register X

**Example**: Calculate 15 + 8
- Press: [1] [5] [ВП] [8] [+]
- Display shows: `23.`

**Example**: Calculate 12 × 7
- Press: [1] [2] [ВП] [7] [×]
- Display shows: `84.`

### Before Key Press Table

| Register | Content |
|----------|---------|
| T | 1. |
| Z | 1. |
| Y | 2. |
| X | 975. (Indicator) |

### After Key Press Table

| Register | Content |
|----------|---------|
| T | 1. |
| Z | 1. |
| Y | 2. |
| X | 19.364916 (Number 975 squared displayed in register X) |

## 5.7 Stack Operations

The calculator maintains a four-level stack (T, Z, Y, X) for intermediate calculations.

### Stack Clearing

To clear all stack registers:
- Press [СХ] [ВП] [СХ] [ВП]

### Before Stack Clear

| Register | Content |
|----------|---------|
| T | 1. |
| Z | 1. |
| Y | 2. |
| X | 19.364916 (Indicator) |

### After Stack Clear

| Register | Content |
|----------|---------|
| T | 0. |
| Z | 0. |
| Y | 0. |
| X | 0. (Indicator) |

## 5.7.8 Two-Operand Operations with Stack

When performing two-operand operations, the microcalculator operates with numbers in registers X and Y. Upon execution, the information in the stack registers is transferred (shifted) as follows:

### Operation Flow Diagram

```
T ────→ T
Z ────→ Z  
Y ────→ Y
X ────→ X (Result)
```

Information is transferred and the stack collapses by one level after each operation.

### Example: Stack Operations During Calculation

Calculate: 34 + 12

**Step 1**: Enter 34
| Register | Content |
|----------|---------|
| T | 0. |
| Z | 0. |
| Y | 0. |
| X | 34. |

**Step 2**: Press [ВП]
| Register | Content |
|----------|---------|
| T | 0. |
| Z | 0. |
| Y | 34. |
| X | 34. |

**Step 3**: Enter 12
| Register | Content |
|----------|---------|
| T | 0. |
| Z | 0. |
| Y | 34. |
| X | 12. |

**Step 4**: Press [+]
| Register | Content |
|----------|---------|
| T | 0. |
| Z | 0. |
| Y | 0. |
| X | 46. (Number 34 in register Y and number 12 in register XI) |

After entering numbers 34 and 12, the information in stack registers will be arranged as follows:

## 5.8 Using Previous Result Register

The calculator can use the result from the previous calculation automatically.

### Automatic Result Retention

After any operation, the result remains in register X and can be used immediately in the next operation.

**Example**: Calculate (15 + 8) × 2

1. Calculate 15 + 8:
   - Press: [1] [5] [ВП] [8] [+]
   - Display shows: `23.`

2. Multiply by 2:
   - Press: [2] [×]
   - Display shows: `46.`

## 5.9 Using Addressable Registers

The MK-56 provides 14 addressable memory registers (RG0 through RG13) for storing intermediate results.

### 5.9.1 Storing Values

To store the value from register X to a memory register:

**For registers RG0 - RG9**:
- Press: [x→П] [n] where n is 0-9

**For registers RG10 - RG13** (RGA, RGБ, RGВ, RGГ):
- Press: [x→П] [•] [n] where n is 0-3

**Example**: Store 6.02 in register RG7:
- Enter: [6] [•] [0] [2]
- Press: [x→П] [7]
- Display shows: `6.02` (value remains in X)

### 5.9.2 Recalling Values

To recall a value from memory register to register X:

**For registers RG0 - RG9**:
- Press: [П→x] [n] where n is 0-9

**For registers RG10 - RG13**:
- Press: [П→x] [•] [n] where n is 0-3

**Example**: Recall value from register RG7:
- Press: [П→x] [7]
- Display shows the value stored in RG7

### 5.9.3 Memory Register Operations

You can perform operations directly with memory registers:

**Add to memory**: [П] [+] [n]
**Subtract from memory**: [П] [−] [n]

**Example**: Add current X value to RG5:
- Press: [П] [+] [5]

### 5.9.4 Recalling Numbers with Sign Change

To recall a number from addressable register and change its sign:

1. Press [П→x] [n]
2. Press [/~/]

Or use the direct sequence for negative recall.

**Example**: Recall negative value from register RG1:
- Press: [П→x] [1] [/~/]

### 5.9.5 Clearing Addressable Registers

To clear a specific register:

1. Press [СХ] to clear X (shows 0)
2. Press [x→П] [n] to store 0 in register n

**Example**: Clear register RG5:
- Press: [СХ] [x→П] [5]

To clear register RG1:
- Press: [x→П] [•] [0] [•] [Г] [•] [1] [•] [С] [•] [/~/]

For example, to clear register RG1, it is necessary to:

| Key Sequence | Display |
|--------------|---------|
| [П→x] [1] | 6.02 (Value recalled from register RG1 to register X) |

## 5.10 Resetting Erroneously Pressed Key [Г]

If the [Г] prefix key is pressed by mistake:

- Press [Г] again to cancel the prefix
- Or press [СХ] to clear and start over

The [Г] key toggles the prefix state, so pressing it twice returns to normal mode.

## Related Documents

- [Key Functions Reference](15-key-reference.md) - Complete key descriptions
- [Calculation Examples](08-examples.md) - Practical calculation examples
- [Programming Mode](07-programming-mode.md) - Advanced programming features
- [Functional Capabilities](03-functional-capabilities.md) - Available operations
