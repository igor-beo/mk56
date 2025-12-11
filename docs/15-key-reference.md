# 15. Key Functions Reference

## Keyboard Layout

The MK-56 calculator keyboard consists of multiple rows of function keys organized by purpose.

## Key Designations

### Table 1: Primary Function Keys

| Key | Function | Description |
|-----|----------|-------------|
| [0] ... [9] | Digit keys | Input digits 0 through 9 into register X |
| [•] | Decimal point | Key for entering decimal point |
| [ВП] | Enter | Key for transferring contents of register X to register Y without transferring information to the stack |
| [СХ] | Clear X | Key for clearing (resetting) register X |
| [←] | Backspace | Key for deleting operation |
| [−] | Subtraction | Subtraction operation key |
| [+] | Addition | Addition operation key |
| [×] | Multiplication | Multiplication operation key |
| [÷] | Division | Division operation key |
| [↔] | Exchange | Key for exchanging contents between registers X and Y |
| [/~/] | Sign change | Key for changing sign of number or exponent |
| [ВП] | Enter number | Preparatory key for entering numbers |
| [?] | Prefix key | Prefix key used when executing operations with second function on number panel |
| [Г] [10ˣ] | Power of 10 | Computation of power function 10ˣ |
| [Г] [eˣ] | Exponential | Computation of exponential function eˣ |
| [Г] [lg] | Logarithm base 10 | Computation of decimal logarithm |
| [Г] [ln] | Natural logarithm | Computation of natural logarithm |
| [Г] [sin] | Sine | Computation of sine function |
| [Г] [cos] | Cosine | Computation of cosine function |

### Table 2: Programming and Control Keys

| Key | Function | Description |
|-----|----------|-------------|
| [ПРГ] | Program mode | "Program" key. Enables programming mode for entering programs and changing addresses |
| [П] | Store | Preparatory key for entering numbers into memory |
| [↑] | Recall | Prefix key. Used when executing operations with keyboard second function, applied to number panel |
| [x→П] | Store to memory | Store value from X to memory register |
| [П→x] | Recall from memory | Recall value from memory register to X |
| [БП] | Unconditional jump | Unconditional jump command for entering jump address |
| [В/О] | Call/Return | Call subroutine or return command |
| [С/П] | Stop/Run | Stop program execution or continue |

### Table 3: Advanced Function Keys

| Key | Primary Function | Secondary Function (with [Г]) |
|-----|------------------|-------------------------------|
| [x²] | Square | x² - Square of number in register X |
| [√x] | Square root | √x - Square root |
| [1/x] | Reciprocal | 1/x - Reciprocal value |
| [xʸ] | Power | xʸ - Raise x to power y |
| [10ˣ] | Power of 10 | 10ˣ - Ten to the power x |
| [eˣ] | Exponential | eˣ - e to the power x |
| [lg] | Log base 10 | lg x - Decimal logarithm |
| [ln] | Natural log | ln x - Natural logarithm |
| [sin] | Sine | sin x - Sine function |
| [cos] | Cosine | cos x - Cosine function |

## Key Usage Notes

### Digit Entry ([0] - [9])
- Press digit keys to enter numbers into register X
- Numbers appear on the display as entered
- Up to 8 significant digits can be entered

### Decimal Point [•]
- Press to enter decimal point in number
- Only one decimal point allowed per number

### Enter Key [ВП]
- Transfers current value from X register to Y register
- Prepares calculator for next operation
- Does not clear X register

### Clear Key [СХ]
- Clears (resets) register X to zero
- Does not affect other registers or stack

### Backspace [←]
- Deletes last entered digit or operation
- Useful for correcting entry errors

### Arithmetic Operations
- **[+]**: Addition
- **[−]**: Subtraction  
- **[×]**: Multiplication
- **[÷]**: Division

Standard operation sequence:
1. Enter first number
2. Press [ВП]
3. Enter second number
4. Press operation key

### Exchange Key [↔]
- Swaps contents of registers X and Y
- Useful for reordering operands

### Sign Change [/~/]
- Changes sign of mantissa or exponent
- Press once to change mantissa sign
- Use with exponent entry to change exponent sign

### Prefix Key [Г]
- Activates secondary functions on keys
- Must be pressed before the function key
- Example: [Г] [10ˣ] computes 10 to the power x

### Programming Keys

#### [ПРГ] - Program Mode
- Toggles between Automatic and Programming modes
- In Programming mode, keystrokes are recorded as program steps
- Display shows current program address

#### [П] - Store to Memory
- Followed by register number (0-9, then [0]-[3] for 10-13)
- Stores value from X register to specified memory register
- Example: [П] [5] stores X to register RG5

#### [↑] - Recall from Memory
- Followed by register number
- Recalls value from memory register to X
- Example: [↑] [5] recalls RG5 to X

#### [БП] - Unconditional Jump
- Followed by address
- Jumps program execution to specified address
- Used for loops and program flow control

#### [В/О] - Call/Return
- **Call**: Jumps to subroutine, saving return address
- **Return**: Returns from subroutine to saved address
- Enables modular programming

#### [С/П] - Stop/Run
- **Stop**: Halts program execution
- **Run**: Resumes program execution
- Useful for debugging and step-by-step execution

## Function Key Details

### Mathematical Functions

All mathematical functions operate on the value in register X:

- **[x²]**: Computes x², result in X
- **[√x]**: Computes √x, result in X (x must be ≥ 0)
- **[1/x]**: Computes 1/x, result in X (x must be ≠ 0)
- **[Г] [10ˣ]**: Computes 10ˣ, result in X
- **[Г] [eˣ]**: Computes eˣ, result in X
- **[Г] [lg]**: Computes log₁₀(x), result in X (x must be > 0)
- **[Г] [ln]**: Computes ln(x), result in X (x must be > 0)
- **[Г] [sin]**: Computes sin(x), x in radians, result in X
- **[Г] [cos]**: Computes cos(x), x in radians, result in X

### Two-Operand Functions

- **[xʸ]**: Computes x^y
  - Enter x, press [ВП]
  - Enter y
  - Press [xʸ]
  - Result in X

## Special Key Combinations

### Memory Operations
- **Store**: [x→П] [n] - Store X to register n
- **Recall**: [П→x] [n] - Recall register n to X
- **Add to memory**: [П] [+] [n] - Add X to register n
- **Subtract from memory**: [П] [−] [n] - Subtract X from register n

### Stack Operations
- **[Cx]**: Clear X register
- **[↔]**: Exchange X and Y
- **[ВП]**: Push X to stack (copy to Y)

## Programming Command Summary

When in Programming mode ([ПРГ]), keys record program steps:

| Command | Function |
|---------|----------|
| [БП] [nn] | Jump to address nn |
| [В/О] | Call subroutine / Return |
| [С/П] | Stop / Pause program |
| [x→П] [n] | Store X to register n |
| [П→x] [n] | Recall register n to X |
| [x≥0] [nn] | Conditional jump if X ≥ 0 to address nn |
| [ПРГ] | Exit programming mode |

## Related Documents

- [Automatic Mode Operation](06-automatic-mode.md) - Using keys in automatic mode
- [Programming Mode](07-programming-mode.md) - Programming with keys
- [Functional Capabilities](03-functional-capabilities.md) - Complete function descriptions
- [Calculation Examples](08-examples.md) - Practical key usage examples
