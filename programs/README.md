# Program Library

Programs from В. П. Дьяконов, «Справочник по расчётам на микрокалькуляторах»
(Наука, 1985), which the book gives for the Б3-34, МК-54 and МК-56. Each
listing:

- was transcribed from page images of the book (`references/book61.pdf`) and
  checked step by step;
- is written in the original notation as a `.mk56` file, with a `NN:`
  address on every line;
- carries the book's worked example as a test (`; @input` / `; @expect`),
  which `make test` runs.

```bash
./emulator/mk56emu programs/listings/04-01-sinh.mk56          # TUI
./tests/mk56test programs/listings/*.mk56                     # run all tests
```

**Status:** *verified* means our earlier transcription matched the book.
*Corrected* means it had errors, now fixed; the most common was ÷ misread as
+, because the book prints ÷ as a small bold "+". Details for every program
are in [AUDIT.md](AUDIT.md).

44 of 45 programs reproduce the book's results. 5.16 is a known failure: it
stops only when a Newton correction is exactly zero, which depends on the
last digits of the real chip's sine.

### Introductory examples (ch. 1)

| Program | Book | Status | Listing |
|---|---|---|---|
| sin(πnft)/(πnft), branching version | p.22–24 (ch.1, unnumbered) | corrected | [01-01-sinc-branch.mk56](listings/01-01-sinc-branch.mk56) |
| sin(πnft)/(πnft), loop version | p.22–24 (ch.1, unnumbered) | corrected | [01-02-sinc-loop.mk56](listings/01-02-sinc-loop.mk56) |

### Simple calculations (ch. 3)

| Program | Book | Status | Listing |
|---|---|---|---|
| 3.1: Integer part of x (1 < x < 10^8) | p.56 | verified | [03-01-int-part.mk56](listings/03-01-int-part.mk56) |
| 3.2: Fractional part of x (0 < x < 10^8) | p.56 | verified | [03-02-frac-part.mk56](listings/03-02-frac-part.mk56) |
| 3.3: Truncate x (0 < x < 10^8) to a step eps = 1*10^-n | p.56 | corrected | [03-03-truncate.mk56](listings/03-03-truncate.mk56) |
| 3.4: Round x of any sign to a step eps = 1*10^-n | p.56 | corrected | [03-04-round.mk56](listings/03-04-round.mk56) |
| 3.5: Absolute value | p.56 | verified | [03-05-abs.mk56](listings/03-05-abs.mk56) |
| 3.6: Angle in radians -> degrees, minutes, seconds | p.56–57 | corrected | [03-06-rad-to-dms.mk56](listings/03-06-rad-to-dms.mk56) |
| 3.7: Angle in degrees, minutes, seconds -> radians | p.57 | corrected | [03-07-dms-to-rad.mk56](listings/03-07-dms-to-rad.mk56) |
| 3.8: Determinant of order 2 | p.57 | verified | [03-08-det2.mk56](listings/03-08-det2.mk56) |
| 3.9: Determinant of order 3 | p.57 | verified | [03-09-det3.mk56](listings/03-09-det3.mk56) |
| 3.10: Determinant of order 4 | p.58 | corrected | [03-10-det4.mk56](listings/03-10-det4.mk56) |
| 3.11: Addition of 4x3 matrices (any number of them) | p.59 | corrected | [03-11-matrix-add.mk56](listings/03-11-matrix-add.mk56) |
| 3.12: Product of a 3x4 matrix A and a 4x2 matrix B | p.59–60 | corrected | [03-12-matrix-mul.mk56](listings/03-12-matrix-mul.mk56) |
| 3.13: Inverse of a 2x2 matrix (result replaces the input) | p.60–61 | corrected | [03-13-inverse2.mk56](listings/03-13-inverse2.mk56) |
| 3.14: Inverse of a 3x3 matrix (result replaces the input) | p.61 | corrected | [03-14-inverse3.mk56](listings/03-14-inverse3.mk56) |
| 3.15: Factorial n!, n ≥ 1 | p.61 | verified | [03-15-factorial.mk56](listings/03-15-factorial.mk56) |
| 3.16: Factorial n!, n ≥ 0 | p.61 | verified | [03-16-factorial-any.mk56](listings/03-16-factorial-any.mk56) |
| 3.17: Factorial of large n by Stirling's formula | p.61–62 | corrected | [03-17-stirling.mk56](listings/03-17-stirling.mk56) |

### Elementary and special functions (ch. 4)

| Program | Book | Status | Listing |
|---|---|---|---|
| 4.1: Hyperbolic sine sh(x) = (eˣ − 1/eˣ)/2 | p.64 | verified | [04-01-sinh.mk56](listings/04-01-sinh.mk56) |
| 4.2: Hyperbolic cosine ch(x) = (eˣ + 1/eˣ)/2 | p.64 | verified | [04-02-cosh.mk56](listings/04-02-cosh.mk56) |
| 4.3: Hyperbolic tangent th(x) = sh(x)/sqrt(1 + sh²(x)) | p.64 | verified | [04-03-tanh.mk56](listings/04-03-tanh.mk56) |
| 4.4: Inverse hyperbolic sine arsh(x) = ln(x + sqrt(1 + x²)), any x | p.64 | verified | [04-04-arsh.mk56](listings/04-04-arsh.mk56) |
| 4.5: Inverse hyperbolic cosine arch(x) = ln(x + sqrt(x² − 1)), x > 1 | p.64 | verified | [04-05-arch.mk56](listings/04-05-arch.mk56) |
| 4.6: Inverse hyperbolic tangent arth(x) = ln sqrt((x + 1)/(1 − x)), −1 < x < 1 | p.64 | corrected | [04-06-arth.mk56](listings/04-06-arth.mk56) |
| 4.7: Inverse hyperbolic cotangent arcth(x) = ln sqrt(1 + 2/(x − 1)), x > 1 | p.65 | verified | [04-07-arcth.mk56](listings/04-07-arcth.mk56) |
| 4.8: Continued fraction f = a0 + b1/(a1 + b2/(a2 + b3/(a3 + ...))) | p.65 | corrected | [04-08-contfrac.mk56](listings/04-08-contfrac.mk56) |
| 4.9: Rational function f(x) = (15 − 21x² + x⁴)/(15 − 6x²) | p.65 | verified | [04-09-ratfunc.mk56](listings/04-09-ratfunc.mk56) |
| 4.10: Real polynomial of degree n ≤ 11 (Horner) | p.65–66 | corrected | [04-10-horner.mk56](listings/04-10-horner.mk56) |
| 4.11: Polynomial of degree n ≤ 10 of a complex variable | p.66 | corrected | [04-11-complex-poly.mk56](listings/04-11-complex-poly.mk56) |
| 4.12: Sum of integers S = 1 + 2 + ... + n | p.66–67 | verified | [04-12-sum-int.mk56](listings/04-12-sum-int.mk56) |
| 4.13: Sum of factorials S(n!) = 1! + 2! + ... + n! | p.67 | verified | [04-13-sum-fact.mk56](listings/04-13-sum-fact.mk56) |
| 4.14: Product of factorials P(n!) = 1!·2!·3!·...·n! | p.67 | verified | [04-14-prod-fact.mk56](listings/04-14-prod-fact.mk56) |
| 4.15: y = sum of kⁿ for k = 1..m | p.67–68 | verified | [04-15-sum-powers.mk56](listings/04-15-sum-powers.mk56) |
| 4.18: Coefficients of the Hermite polynomial Hn(x) | p.69 | corrected | [04-18-hermite-coef.mk56](listings/04-18-hermite-coef.mk56) |
| 4.19: Coefficients of the Chebyshev polynomial Tn(x) | p.69 | corrected | [04-19-chebyshev-coef.mk56](listings/04-19-chebyshev-coef.mk56) |
| 4.20: Laguerre polynomial Ln(x) | p.69–70 | corrected | [04-20-laguerre.mk56](listings/04-20-laguerre.mk56) |

### Numerical methods (ch. 5)

| Program | Book | Status | Listing |
|---|---|---|---|
| 5.1: System of n ≤ 4 linear equations | p.79 | corrected | [05-01-linsys.mk56](listings/05-01-linsys.mk56) |
| 5.15: Root of x = f(x) by simple iteration, stopping at "machine zero" | p.89 | corrected | [05-15-iteration.mk56](listings/05-15-iteration.mk56) |
| 5.16: Newton's method, stopping at machine zero | p.89 | corrected · known failure | [05-16-newton.mk56](listings/05-16-newton.mk56) |
| 5.17: Newton's method, stopping when (x(n+1) − x(n))² < eps² | p.89 | verified | [05-17-newton-eps.mk56](listings/05-17-newton-eps.mk56) |
| 5.32a: Roots of a 4th-degree equation | p.98–99 | corrected | [05-32-quartic.mk56](listings/05-32-quartic.mk56) |
| 5.32b: Roots of a 5th-degree equation | p.98–99 | corrected | [05-32-quintic.mk56](listings/05-32-quintic.mk56) |

### Engineering calculations (ch. 7)

| Program | Book | Status | Listing |
|---|---|---|---|
| 7.8: Number of turns w of a coil on a pot (armoured) core (fig. 7.6) | p.179 | corrected | [07-08-coil-pot-core.mk56](listings/07-08-coil-pot-core.mk56) |
| 7.9: Number of turns w of a coil with a closed core (fig. 7.7) | p.179–180 | corrected | [07-09-coil-closed-core.mk56](listings/07-09-coil-closed-core.mk56) |

## Not in this library

An earlier version of this library had 18 entries that do not exist in the
book: generic outlines for a quadratic equation, Newton's method, trapezoid
integration, bisection, combinatorics, statistics and circuit calculations.
Several used keys the МК-56 does not have. They were removed. The book's
own programs for these topics are listed in [AUDIT.md](AUDIT.md), and
transcriptions are welcome.
