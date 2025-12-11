# 8. Calculation Examples

## Overview

This document provides practical examples of calculations and programs for the MK-56 calculator, demonstrating both Automatic and Programming modes.

## 7. Calculation Examples by Programs

### 7.1 Finding Complex Percentage

**Problem**: Calculate a complex percentage value.

**Example**: Find what percentage 15 is of 60.

#### Solution in Automatic Mode

**Formula**: (15 ÷ 60) × 100

**Key Sequence**:
1. [1] [5] - Enter 15
2. [ВП] - Push to stack
3. [6] [0] - Enter 60
4. [÷] - Divide (15 ÷ 60 = 0.25)
5. [1] [0] [0] - Enter 100
6. [×] - Multiply (0.25 × 100 = 25)

**Result**: `25.` (15 is 25% of 60)

#### Alternative Method

**Key Sequence**:
1. [1] [5] - Enter 15
2. [ВП] - Push to stack
3. [6] [0] - Enter 60
4. [÷] - Divide
5. [1] [0] [0] - Enter 100
6. [×] - Multiply

**Result**: `25.`

### 7.2 Calculating Sum (Σ) or Product (P) of Number Sequence

**Problem**: Calculate the sum or product of a sequence of numbers.

#### Example: Sum of Numbers

Calculate: 3 + 7 + 12 + 8

**Key Sequence**:
1. [3] - Enter first number
2. [ВП] - Push to stack
3. [7] - Enter second number
4. [+] - Add (3 + 7 = 10)
5. [1] [2] - Enter third number
6. [+] - Add (10 + 12 = 22)
7. [8] - Enter fourth number
8. [+] - Add (22 + 8 = 30)

**Result**: `30.`

#### Example: Product of Numbers

Calculate: 2 × 3 × 4 × 5

**Key Sequence**:
1. [2] - Enter first number
2. [ВП] - Push to stack
3. [3] - Enter second number
4. [×] - Multiply (2 × 3 = 6)
5. [4] - Enter third number
6. [×] - Multiply (6 × 4 = 24)
7. [5] - Enter fourth number
8. [×] - Multiply (24 × 5 = 120)

**Result**: `120.`

### 7.3 Mathematical Expectation Calculation

**Problem**: Calculate statistical mathematical expectation.

**Formula**: E(X) = Σ(xi × pi) where xi are values and pi are probabilities

#### Example

Given data:
- x₁ = 2, p₁ = 0.3
- x₂ = 5, p₂ = 0.5
- x₃ = 8, p₃ = 0.2

Calculate: E(X) = (2 × 0.3) + (5 × 0.5) + (8 × 0.2)

**Key Sequence**:
1. [2] [ВП] [0] [•] [3] [×] - Calculate 2 × 0.3 = 0.6
2. [5] [ВП] [0] [•] [5] [×] [+] - Calculate 5 × 0.5 = 2.5, add to 0.6 = 3.1
3. [8] [ВП] [0] [•] [2] [×] [+] - Calculate 8 × 0.2 = 1.6, add to 3.1 = 4.7

**Result**: `4.7`

### 7.4 "Radiological" Problem - Body Decay Under Influence

**Problem**: Calculate radioactive decay or similar exponential decay process.

**Formula**: N(t) = N₀ × e^(-λt)

Where:
- N(t) = amount at time t
- N₀ = initial amount
- λ = decay constant
- t = time

#### Example

Given: N₀ = 1000, λ = 0.693, t = 2

Calculate: N(2) = 1000 × e^(-0.693 × 2)

**Key Sequence**:
1. [0] [•] [6] [9] [3] - Enter λ = 0.693
2. [2] - Enter t = 2
3. [×] - Multiply: 0.693 × 2 = 1.386
4. [/~/] - Change sign: -1.386
5. [Г] [eˣ] - Calculate e^(-1.386) ≈ 0.25
6. [1] [0] [0] [0] - Enter N₀ = 1000
7. [×] - Multiply: 0.25 × 1000 = 250

**Result**: `250.` (approximately)

## Programming Examples

### Example 1: Square and Add Constant

**Program**: Calculate x² + 5 for any input x

#### Program Entry

| Address | Key | Command | Description |
|---------|-----|---------|-------------|
| 00 | [x²] | Square | Square the input |
| 01 | [5] | Constant | Enter constant 5 |
| 02 | [+] | Add | Add to squared value |
| 03 | [С/П] | Stop | Display result |

#### Program Usage

1. Enter Programming mode: [ПРГ]
2. Enter program as shown above
3. Exit Programming mode: [ПРГ]
4. Enter value: [7]
5. Run program: [В/О]
6. Result: `54.` (7² + 5 = 49 + 5 = 54)

### Example 2: Resistance in Parallel Circuit

**Program**: Calculate total resistance of parallel resistors

**Formula**: 1/Rtotal = 1/R1 + 1/R2 + 1/R3 + 1/R4

#### Task 1: Chain of 4 Resistors

Given: R1=220 Ω, R2=4000 Ω, R3=560 Ω, R4=1200 Ω

Calculate: Rtotal = 1 / (1/R1 + 1/R2 + 1/R3 + 1/R4)

**Key Sequence**:
1. [2] [2] [0] [1/x] - Calculate 1/220
2. [4] [0] [0] [0] [1/x] [+] - Calculate 1/4000, add
3. [5] [6] [0] [1/x] [+] - Calculate 1/560, add
4. [1] [2] [0] [0] [1/x] [+] - Calculate 1/1200, add
5. [1/x] - Take reciprocal of sum

**Result**: `134.87082` Ω (approximately)

### Example 3: Loop Program - Factorial Calculation

**Program**: Calculate n! (factorial)

#### Program Structure

| Address | Key | Command | Description |
|---------|-----|---------|-------------|
| 00 | [x→П] [0] | Store n | Store input in RG0 |
| 01 | [1] | Initialize | Start with 1 |
| 02 | [x→П] [1] | Store result | Store in RG1 |
| 03 | [П→x] [0] | Recall n | Get counter |
| 04 | [x≥0] [0] [8] | Check | If n ≥ 0, continue |
| 05 | [П→x] [1] | Get result | Recall result |
| 06 | [С/П] | Stop | Display result |
| 07 | [БП] [0] [0] | Jump | Should not reach |
| 08 | [П→x] [1] | Get result | Recall current result |
| 09 | [П→x] [0] | Get counter | Recall counter |
| 10 | [×] | Multiply | result × counter |
| 11 | [x→П] [1] | Store | Save new result |
| 12 | [П→x] [0] | Get counter | Recall counter |
| 13 | [1] | Constant | Enter 1 |
| 14 | [−] | Decrement | counter - 1 |
| 15 | [x→П] [0] | Store | Save new counter |
| 16 | [БП] [0] [3] | Loop | Jump back to check |

#### Usage

1. Enter program in Programming mode
2. Exit to Automatic mode
3. Enter number: [5]
4. Run: [В/О]
5. Result: `120.` (5! = 5 × 4 × 3 × 2 × 1 = 120)

### Example 4: Quadratic Equation Solver

**Program**: Solve ax² + bx + c = 0

**Formula**: x = (-b ± √(b² - 4ac)) / 2a

#### Program for Positive Root

| Address | Key | Command | Description |
|---------|-----|---------|-------------|
| 00 | [x→П] [2] | Store c | Store c in RG2 |
| 01 | [x→П] [1] | Store b | Store b in RG1 |
| 02 | [x→П] [0] | Store a | Store a in RG0 |
| 03 | [П→x] [1] | Recall b | Get b |
| 04 | [x²] | Square | b² |
| 05 | [4] | Constant | Enter 4 |
| 06 | [П→x] [0] | Recall a | Get a |
| 07 | [×] | Multiply | 4a |
| 08 | [П→x] [2] | Recall c | Get c |
| 09 | [×] | Multiply | 4ac |
| 10 | [−] | Subtract | b² - 4ac |
| 11 | [√x] | Square root | √(b² - 4ac) |
| 12 | [П→x] [1] | Recall b | Get b |
| 13 | [/~/] | Negate | -b |
| 14 | [+] | Add | -b + √(b² - 4ac) |
| 15 | [2] | Constant | Enter 2 |
| 16 | [П→x] [0] | Recall a | Get a |
| 17 | [×] | Multiply | 2a |
| 18 | [÷] | Divide | Result / 2a |
| 19 | [С/П] | Stop | Display result |

#### Usage

**Example**: Solve x² - 5x + 6 = 0 (a=1, b=-5, c=6)

1. Enter program
2. Enter coefficients in reverse order:
   - [6] [ВП] - Enter c = 6
   - [5] [/~/] [ВП] - Enter b = -5
   - [1] - Enter a = 1
3. Run: [В/О]
4. Result: `3.` (one root)

To find second root, modify program to use minus instead of plus before square root.

### Example 5: Series Sum Calculation

**Program**: Calculate sum of series: Σ(1/n) for n = 1 to N

#### Program

| Address | Key | Command | Description |
|---------|-----|---------|-------------|
| 00 | [x→П] [0] | Store N | Store limit in RG0 |
| 01 | [0] | Initialize | Start sum at 0 |
| 02 | [x→П] [1] | Store sum | Store in RG1 |
| 03 | [1] | Initialize | Start counter at 1 |
| 04 | [x→П] [2] | Store counter | Store in RG2 |
| 05 | [П→x] [2] | Get counter | Recall counter |
| 06 | [П→x] [0] | Get limit | Recall limit |
| 07 | [−] | Compare | counter - limit |
| 08 | [x≥0] [1] [5] | Check | If done, jump to end |
| 09 | [П→x] [2] | Get counter | Recall counter |
| 10 | [1/x] | Reciprocal | 1/counter |
| 11 | [П→x] [1] | Get sum | Recall sum |
| 12 | [+] | Add | sum + 1/counter |
| 13 | [x→П] [1] | Store sum | Save new sum |
| 14 | [П→x] [2] | Get counter | Recall counter |
| 15 | [1] | Constant | Enter 1 |
| 16 | [+] | Increment | counter + 1 |
| 17 | [x→П] [2] | Store counter | Save new counter |
| 18 | [БП] [0] [5] | Loop | Jump back |
| 19 | [П→x] [1] | Get sum | Recall final sum |
| 20 | [С/П] | Stop | Display result |

#### Usage

Calculate sum for N = 10:
1. Enter program
2. Enter: [1] [0]
3. Run: [В/О]
4. Result: `2.9289682` (approximately)

## Related Documents

- [Automatic Mode Operation](06-automatic-mode.md) - Basic operation details
- [Programming Mode](07-programming-mode.md) - Programming instructions
- [Key Functions Reference](15-key-reference.md) - Key descriptions
- [Programming Commands](16-programming-commands.md) - Command reference
