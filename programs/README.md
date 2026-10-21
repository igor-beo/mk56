# Program Library

Programs from В. П. Дьяконов, «Справочник по расчётам на микрокалькуляторах»
(Наука, 1985), which the book gives for the Б3-34, МК-54 and МК-56. Each
program is one MK56-ASM file:

```
; Program 3.15: Factorial n! = 1*2*3*...*n for n >= 1 (0! = 1 is excluded)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.61 (book61.pdf page 62)
; Input: n in X.  Output: n! in X.
;
; Book example: 10! = 3628800
; @input 10
; @expect X=3628800
;
; As printed:
;   00: П0 1 ИП0 × FL0 02 С/П
;
; Each line: instruction ; address, keys, codes

        STO R0          ; 00  П0             40
        1               ; 01  1              01

L02:
        RCL R0          ; 02  ИП0            60
        MUL             ; 03  ×              12
        LOOP0 L02       ; 04  FL0 02         5D 02
        HALT            ; 06  С/П            50
```

- **The header** gives the book page, the input and output, and the book's
  worked example as a test (`; @input` / `; @expect`) that `make test` runs.
- **"As printed"** is the listing exactly as the book prints it, transcribed
  from page images (`references/book61.pdf`) so that it can be compared with
  the page. `make test` checks that it assembles to the same steps as the
  code below.
- **The code** has one step per line, with labels instead of raw jump
  addresses. Each comment gives the address, the keys to press on the
  calculator and the code it shows in programming mode.

```bash
./emulator/mk56emu programs/04-01-sinh.asm                    # TUI
./assembler/mk56asm my-listing.mk56 -s my-listing.asm         # convert your own
```

**Status:** *verified* means our earlier transcription matched the book.
*Corrected* means it had errors, now fixed; the most common was ÷ misread as
+, because the book prints ÷ as a small bold "+". *Transcribed* means the
program was added directly from the book. Details for every program are in
[AUDIT.md](AUDIT.md).

71 of 72 programs reproduce the book's results. 5.16 is a known failure: it
stops only when a Newton correction is exactly zero, which depends on the
last digits of the real chip's sine.

### Introductory examples (ch. 1)

| Program | Book | Status | File |
|---|---|---|---|
| sin(πnft)/(πnft), branching version | p.22–24 (ch.1, unnumbered) | corrected | [01-01-sinc-branch.asm](01-01-sinc-branch.asm) |
| sin(πnft)/(πnft), loop version | p.22–24 (ch.1, unnumbered) | corrected | [01-02-sinc-loop.asm](01-02-sinc-loop.asm) |

### Simple calculations (ch. 3)

| Program | Book | Status | File |
|---|---|---|---|
| 3.1: Integer part of x (1 < x < 10^8) | p.56 | verified | [03-01-int-part.asm](03-01-int-part.asm) |
| 3.2: Fractional part of x (0 < x < 10^8) | p.56 | verified | [03-02-frac-part.asm](03-02-frac-part.asm) |
| 3.3: Truncate x (0 < x < 10^8) to a step eps = 1*10^-n | p.56 | corrected | [03-03-truncate.asm](03-03-truncate.asm) |
| 3.4: Round x of any sign to a step eps = 1*10^-n | p.56 | corrected | [03-04-round.asm](03-04-round.asm) |
| 3.5: Absolute value | p.56 | verified | [03-05-abs.asm](03-05-abs.asm) |
| 3.6: Angle in radians -> degrees, minutes, seconds | p.56–57 | corrected | [03-06-rad-to-dms.asm](03-06-rad-to-dms.asm) |
| 3.7: Angle in degrees, minutes, seconds -> radians | p.57 | corrected | [03-07-dms-to-rad.asm](03-07-dms-to-rad.asm) |
| 3.8: Determinant of order 2 | p.57 | verified | [03-08-det2.asm](03-08-det2.asm) |
| 3.9: Determinant of order 3 | p.57 | verified | [03-09-det3.asm](03-09-det3.asm) |
| 3.10: Determinant of order 4 | p.58 | corrected | [03-10-det4.asm](03-10-det4.asm) |
| 3.11: Addition of 4x3 matrices (any number of them) | p.59 | corrected | [03-11-matrix-add.asm](03-11-matrix-add.asm) |
| 3.12: Product of a 3x4 matrix A and a 4x2 matrix B | p.59–60 | corrected | [03-12-matrix-mul.asm](03-12-matrix-mul.asm) |
| 3.13: Inverse of a 2x2 matrix (result replaces the input) | p.60–61 | corrected | [03-13-inverse2.asm](03-13-inverse2.asm) |
| 3.14: Inverse of a 3x3 matrix (result replaces the input) | p.61 | corrected | [03-14-inverse3.asm](03-14-inverse3.asm) |
| 3.15: Factorial n!, n ≥ 1 | p.61 | verified | [03-15-factorial.asm](03-15-factorial.asm) |
| 3.16: Factorial n!, n ≥ 0 | p.61 | verified | [03-16-factorial-any.asm](03-16-factorial-any.asm) |
| 3.17: Factorial of large n by Stirling's formula | p.61–62 | corrected | [03-17-stirling.asm](03-17-stirling.asm) |
| 3.19: Permutations, arrangements and combinations | p.62 | transcribed | [03-19-combinations.asm](03-19-combinations.asm) |

### Elementary and special functions (ch. 4)

| Program | Book | Status | File |
|---|---|---|---|
| 4.1: Hyperbolic sine sh(x) = (eˣ − 1/eˣ)/2 | p.64 | verified | [04-01-sinh.asm](04-01-sinh.asm) |
| 4.2: Hyperbolic cosine ch(x) = (eˣ + 1/eˣ)/2 | p.64 | verified | [04-02-cosh.asm](04-02-cosh.asm) |
| 4.3: Hyperbolic tangent th(x) = sh(x)/sqrt(1 + sh²(x)) | p.64 | verified | [04-03-tanh.asm](04-03-tanh.asm) |
| 4.4: Inverse hyperbolic sine arsh(x) = ln(x + sqrt(1 + x²)), any x | p.64 | verified | [04-04-arsh.asm](04-04-arsh.asm) |
| 4.5: Inverse hyperbolic cosine arch(x) = ln(x + sqrt(x² − 1)), x > 1 | p.64 | verified | [04-05-arch.asm](04-05-arch.asm) |
| 4.6: Inverse hyperbolic tangent arth(x) = ln sqrt((x + 1)/(1 − x)), −1 < x < 1 | p.64 | corrected | [04-06-arth.asm](04-06-arth.asm) |
| 4.7: Inverse hyperbolic cotangent arcth(x) = ln sqrt(1 + 2/(x − 1)), x > 1 | p.65 | verified | [04-07-arcth.asm](04-07-arcth.asm) |
| 4.8: Continued fraction f = a0 + b1/(a1 + b2/(a2 + b3/(a3 + ...))) | p.65 | corrected | [04-08-contfrac.asm](04-08-contfrac.asm) |
| 4.9: Rational function f(x) = (15 − 21x² + x⁴)/(15 − 6x²) | p.65 | verified | [04-09-ratfunc.asm](04-09-ratfunc.asm) |
| 4.10: Real polynomial of degree n ≤ 11 (Horner) | p.65–66 | corrected | [04-10-horner.asm](04-10-horner.asm) |
| 4.11: Polynomial of degree n ≤ 10 of a complex variable | p.66 | corrected | [04-11-complex-poly.asm](04-11-complex-poly.asm) |
| 4.12: Sum of integers S = 1 + 2 + ... + n | p.66–67 | verified | [04-12-sum-int.asm](04-12-sum-int.asm) |
| 4.13: Sum of factorials S(n!) = 1! + 2! + ... + n! | p.67 | verified | [04-13-sum-fact.asm](04-13-sum-fact.asm) |
| 4.14: Product of factorials P(n!) = 1!·2!·3!·...·n! | p.67 | verified | [04-14-prod-fact.asm](04-14-prod-fact.asm) |
| 4.15: y = sum of kⁿ for k = 1..m | p.67–68 | verified | [04-15-sum-powers.asm](04-15-sum-powers.asm) |
| 4.18: Coefficients of the Hermite polynomial Hn(x) | p.69 | corrected | [04-18-hermite-coef.asm](04-18-hermite-coef.asm) |
| 4.19: Coefficients of the Chebyshev polynomial Tn(x) | p.69 | corrected | [04-19-chebyshev-coef.asm](04-19-chebyshev-coef.asm) |
| 4.20: Laguerre polynomial Ln(x) | p.69–70 | corrected | [04-20-laguerre.asm](04-20-laguerre.asm) |

### Numerical methods (ch. 5)

| Program | Book | Status | File |
|---|---|---|---|
| 5.1: System of n ≤ 4 linear equations | p.79 | corrected | [05-01-linsys.asm](05-01-linsys.asm) |
| 5.15: Root of x = f(x) by simple iteration, stopping at "machine zero" | p.89 | corrected | [05-15-iteration.asm](05-15-iteration.asm) |
| 5.16: Newton's method, stopping at machine zero | p.89 | corrected · known failure | [05-16-newton.asm](05-16-newton.asm) |
| 5.17: Newton's method, stopping when (x(n+1) − x(n))² < eps² | p.89 | verified | [05-17-newton-eps.asm](05-17-newton-eps.asm) |
| 5.22: Root by halving the interval (bisection) | p.92 | transcribed | [05-22-bisection.asm](05-22-bisection.asm) |
| 5.29: Quadratic equation | p.97 | transcribed | [05-29-quadratic.asm](05-29-quadratic.asm) |
| 5.30: Quadratic equation, reduced error for real roots | p.97 | transcribed | [05-30-quadratic-precise.asm](05-30-quadratic-precise.asm) |
| 5.32a: Roots of a 4th-degree equation | p.98–99 | corrected | [05-32-quartic.asm](05-32-quartic.asm) |
| 5.32b: Roots of a 5th-degree equation | p.98–99 | corrected | [05-32-quintic.asm](05-32-quintic.asm) |
| 5.46: Numerical integration by the trapezoid rule | p.107 | transcribed | [05-46-trapezoid.asm](05-46-trapezoid.asm) |
| 5.47: Numerical integration by Simpson's rule | p.107 | transcribed | [05-47-simpson.asm](05-47-simpson.asm) |
| 5.67: RC-circuit response (combined Euler method) | p.118 | transcribed | [05-67-rc-circuit.asm](05-67-rc-circuit.asm) |
| 5.80: Moments, mean, variance, asymmetry, excess | p.135 | transcribed | [05-80-moments.asm](05-80-moments.asm) |
| 5.81: Auxiliary coefficients U3, U4 | p.136 | transcribed | [05-81-u3-u4.asm](05-81-u3-u4.asm) |
| 5.82: Sample correlation coefficient | p.136 | transcribed | [05-82-correlation.asm](05-82-correlation.asm) |
| 5.85: Uniform random numbers, V = D(37V) | p.138 | transcribed | [05-85-random.asm](05-85-random.asm) |
| 5.86: Uniform random numbers, V = D(11V + π) | p.138 | transcribed | [05-86-random-pi.asm](05-86-random-pi.asm) |
| 5.87: Uniform random numbers in [a, b] | p.139 | transcribed | [05-87-random-ab.asm](05-87-random-ab.asm) |
| 5.88: Normal random numbers | p.139 | transcribed | [05-88-random-normal.asm](05-88-random-normal.asm) |
| 5.89: Least-squares line y = b0 + b1·x | p.140 | transcribed | [05-89-regression.asm](05-89-regression.asm) |

### Probability (ch. 6)

| Program | Book | Status | File |
|---|---|---|---|
| 6.31: Probability integral Φ(y) by power series | p.167 | transcribed | [06-31-erf-series.asm](06-31-erf-series.asm) |
| 6.32: Φ(y) for y > 4 by asymptotic expansion | p.167 | transcribed | [06-32-erf-asymptotic.asm](06-32-erf-asymptotic.asm) |
| 6.33: Φ(y) for any y (series below 4, asymptotic from 4) | p.168 | transcribed | [06-33-erf-any.asm](06-33-erf-any.asm) |
| 6.34: Φ(x) = erf(x), 3-coefficient approximation (A–S 7.1.25) | p.168 | transcribed | [06-34-erf-approx3.asm](06-34-erf-approx3.asm) |
| 6.35: Φ(x) = erf(x), rounded-coefficient approximation | p.169 | transcribed | [06-35-erf-approx3-short.asm](06-35-erf-approx3-short.asm) |
| 6.36: Φ(x) = erf(x), 5-coefficient approximation (A–S 7.1.26) | p.169 | transcribed | [06-36-erf-approx5.asm](06-36-erf-approx5.asm) |

### Engineering calculations (ch. 7)

| Program | Book | Status | File |
|---|---|---|---|
| 7.8: Number of turns w of a coil on a pot (armoured) core (fig. 7.6) | p.179 | corrected | [07-08-coil-pot-core.asm](07-08-coil-pot-core.asm) |
| 7.9: Number of turns w of a coil with a closed core (fig. 7.7) | p.179–180 | corrected | [07-09-coil-closed-core.asm](07-09-coil-closed-core.asm) |
| 7.28: Rectifier working into a filter capacitor | p.190 | transcribed | [07-28-rectifier.asm](07-28-rectifier.asm) |
| 7.29: Transistor physical parameters from h-parameters | p.191 | transcribed | [07-29-transistor-h-to-phys.asm](07-29-transistor-h-to-phys.asm) |
| 7.30: Transistor h-parameters from physical parameters | p.192 | transcribed | [07-30-transistor-phys-to-h.asm](07-30-transistor-phys-to-h.asm) |
| 7.31: Amplifier stage, common base | p.194 | transcribed | [07-31-amp-common-base.asm](07-31-amp-common-base.asm) |
| 7.32: Amplifier stage, common emitter | p.195 | transcribed | [07-32-amp-common-emitter.asm](07-32-amp-common-emitter.asm) |
| 7.33: Amplifier stage, common collector | p.195 | transcribed | [07-33-amp-common-collector.asm](07-33-amp-common-collector.asm) |

## Removed entries

An earlier version of this library had 18 entries that are not in the book:
generic outlines for a quadratic equation, Newton's method, trapezoid
integration, bisection, combinatorics, statistics and circuit calculations.
Several used keys the МК-56 does not have. They were replaced by the book's
own programs for the same topics (3.19, 5.22, 5.29–5.30, 5.46–5.47, 5.67,
5.80–5.82, 5.85–5.89, 6.31–6.36, 7.28–7.33). The book has no double-factorial program,
so that entry has no replacement. See [AUDIT.md](AUDIT.md).
