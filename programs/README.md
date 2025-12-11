# MK-56 Program Listings

Programs extracted from V.P. Dyakonov's "Reference Manual for Calculations on Microcalculators" (1985).

## Note on Calculator Compatibility

The book primarily contains programs for:
- **B3-34/MK-54** - Soviet RPN (Reverse Polish Notation) calculators
- **TI-58C/TI-59** - Texas Instruments algebraic calculators
- **Various Sharp/Casio** - Foreign algebraic calculators

**MK-56** uses algebraic logic similar to B3-38, but with Soviet-style notation. Programs from B3-34 require translation to algebraic notation.

## Program Categories

1. [Basic Operations](01-basic-operations.md) - Integer/fractional parts, rounding, angles
2. [Matrix Operations](02-matrix-operations.md) - Determinants 2×2 to 4×4, matrix inversion
3. [Polynomial Evaluation](03-polynomials.md) - Horner scheme, Hermite, Chebyshev, Laguerre
4. [Special Functions](04-special-functions.md) - Hyperbolic functions, continued fractions
5. [Numerical Methods](05-numerical-methods.md) - Linear systems, Newton-Raphson, integration
6. [Factorial & Combinatorics](06-factorial-combinatorics.md) - Factorial, combinations, permutations
7. [Scientific/Engineering](07-scientific-engineering.md) - Coil inductance, transistors, circuits
8. [Statistics & Sequences](08-statistics-sequences.md) - Mean, variance, sums, products

## Programs Index

### Chapter 3: Simple Calculations
| Program | Description | Page |
|---------|-------------|------|
| 3.1 | Integer part extraction | 56 |
| 3.2 | Fractional part extraction | 56 |
| 3.3 | Number truncation | 56 |
| 3.4 | Rounding with sign correction | 56 |
| 3.5 | Absolute value | 56 |
| 3.6 | Angle: radians → degrees/min/sec | 57 |
| 3.7 | Angle: degrees/min/sec → radians | 57 |
| 3.8 | 2×2 Determinant | 57 |
| 3.9 | 3×3 Determinant | 57 |
| 3.10 | 4×4 Determinant | 58 |
| 3.11 | 4×3 Matrix addition | 59 |
| 3.12 | 3×4 × 4×2 Matrix multiplication | 59 |
| 3.13 | 2×2 Matrix inversion | 60 |
| 3.14 | 3×3 Matrix inversion | 61 |
| 3.15 | Factorial n! (n≥1) | 61 |
| 3.16 | Factorial n! (any n) | 61 |
| 3.17 | Factorial (Stirling) | 61 |

### Chapter 4: Elementary Functions
| Program | Description | Page |
|---------|-------------|------|
| 4.1 | Hyperbolic sine sh(x) | 64 |
| 4.2 | Hyperbolic cosine ch(x) | 64 |
| 4.3 | Hyperbolic tangent th(x) | 64 |
| 4.4 | Inverse hyperbolic sine arsh(x) | 64 |
| 4.5 | Inverse hyperbolic cosine arch(x) | 64 |
| 4.6 | Inverse hyperbolic tangent arth(x) | 64 |
| 4.7 | Inverse hyperbolic cotangent arcth(x) | 65 |
| 4.8 | Continued fractions | 65 |
| 4.9 | Fractional-rational function | 65 |
| 4.10 | Real polynomial (Horner) | 65 |
| 4.11 | Complex polynomial | 66 |
| 4.12 | Sum of integers | 67 |
| 4.13 | Sum of factorials | 67 |
| 4.14 | Product of factorials | 67 |
| 4.15 | Power sequence sum | 67 |
| 4.18 | Hermite polynomial coefficients | 69 |
| 4.19 | Chebyshev polynomial coefficients | 69 |
| 4.20 | Laguerre polynomial | 69 |

### Chapter 5: Numerical Methods
| Program | Description | Page |
|---------|-------------|------|
| 5.1 | Linear equation system (n≤4) | 79 |
| 5.15 | Simple iteration method | 89 |
| 5.16 | Newton's method (machine zero) | 89 |
| 5.17 | Newton's method with tolerance | 89 |
| 5.32 | Fifth-degree polynomial equation | 99 |

### Chapter 7: Electrical Engineering
| Program | Description | Page |
|---------|-------------|------|
| 7.8 | Armored core coil inductance | 179 |
| 7.9 | Closed core coil calculation | 179 |

## Notation Reference

### B3-34 Style (RPN)
| Symbol | Meaning |
|--------|---------|
| ИП N | Recall from register N |
| П N | Store to register N |
| БП | Unconditional jump |
| С/П | Stop/Run |
| FL0-3 | Loop operators |
| Fx<0, Fx=0, Fx≥0 | Conditional jumps |

### MK-56 Algebraic Style
| Symbol | Meaning |
|--------|---------|
| П→x N | Recall from register N |
| x→П N | Store to register N |
| БП | Unconditional jump |
| С/П | Stop/Run |
| x≥0, x<0 | Conditional jumps |
