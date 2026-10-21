# Audit of `programs/*.md` against Дьяконов (1985)

**Source checked:** V.P. Дьяконов, *Справочник по расчётам на микрокалькуляторах* (Наука, 1985), `references/book61.pdf`.
**Page citations:** "p.N" is the **printed** book page. In this scan, printed page N is **book61.pdf page N+1** (1-based). The page numbers in `programs/README.md` are printed pages and are correct, with one exception: 4.12 starts on p.66, not p.67.
**Status (after the audit):** all 45 listings are run by `make test` on the
real assembler and emulator. 44 reproduce the book's results. 5.16 is a known
failure (`@xfail`): it stops only when a Newton correction is exactly zero,
and that depends on the real chip's sin digits. The 18 NOT-FOUND entries were
then replaced by 27 programs transcribed from the book; see
[Transcriptions that replace the NOT-FOUND entries](#transcriptions-that-replace-the-not-found-entries).

**Method:** each listing was read from page images rendered at 260–400 dpi, not from the OCR layer, which mangles key names and digits. Each `.mk56` listing was then run through a scratch simulator of the ISA doc semantics (§2–3) with the book's worked example. All listings reproduce the book's printed results except 5.16; the reason is explained below. The simulator is scratch work only. The repo emulator and assembler were not built or run.
**Output:** 45 listings (now `programs/*.asm`), covering 43 audited entries. The sinc example and 5.32 each have two listings.

## Status counts

| Status | Count |
|---|---|
| VERIFIED | 19 |
| CORRECTED | 24 |
| NOT-FOUND | 18 |
| NOT-MK56 | 0 |
| **Total entries in programs/*.md** | **61** |

None of the entries is NOT-MK56. Every program in the book that we transcribed is written for the Б3-34/МК-54/МК-56 in RPN. The book itself says the МК-56 is fully compatible with the Б3-34. The TI-58C/59 programs are only in the book's appendices, and none of our entries came from there. **The README claim that the МК-56 "uses algebraic logic similar to B3-38" and that programs need "translation to algebraic notation" is false and must be removed.** The same applies to the "translate for MK-56 / algebraic mode" usage notes in every chapter file.

## Systematic transcription error: ÷ was read as +

In this printing the **÷ sign usually prints as a small, bold "+"**. A real + is larger and thinner. Our transcriptions turned many of these ÷ signs into +. Where we could not tell from the glyph, the step was decided by tracing the algorithm and by simulating against the book's example. The steps fixed this way are 3.3/01, 3.4/04 and /08, 3.7/07, /12 and /19, 3.13/13, /17 and /27, 3.14/04, /42 and /46, 3.17/12 and /14, 4.6/08, 5.1/08, 5.32-quartic/70 and 5.32-quintic/37. Three steps are read as ÷ but are **not fully pinned down** by the example: 5.32-quartic/22, 5.32-quintic/60 and 7.9/17 and /26. For 7.9 the formula requires ÷. For the two 5.32 steps either reading gives the same roots for the book's example.

## Summary table

| Entry in programs/*.md | Status | Book page | Listing | Notes |
|---|---|---|---|---|
| 3.1 Integer part | VERIFIED | p.56 | 03-01-int-part.asm | Book has no worked example, so the test is computed |
| 3.2 Fractional part | VERIFIED | p.56 | 03-02-frac-part.asm | Book has no worked example, so the test is computed |
| 3.3 Truncation | CORRECTED | p.56 | 03-03-truncate.asm | Step 01 is ÷, not + |
| 3.4 Rounding with sign | CORRECTED | p.56 | 03-04-round.asm | Steps 04 and 08 are ÷, not + |
| 3.5 Absolute value | VERIFIED | p.56 | 03-05-abs.asm | Book gives only a fragment. The listing is a minimal instance with a computed test |
| 3.6 Radians → °′″ | CORRECTED | p.56–57 | 03-06-rad-to-dms.asm | Our listing was a copy of 3.7. The real listing has 36 steps and two nested subroutines |
| 3.7 °′″ → radians | CORRECTED | p.57 | 03-07-dms-to-rad.asm | Steps 07, 12 and 19 are ÷, not + |
| 3.8 2×2 determinant | VERIFIED | p.57 | 03-08-det2.asm | |
| 3.9 3×3 determinant | VERIFIED | p.57 | 03-09-det3.asm | |
| 3.10 4×4 determinant | CORRECTED | p.58 | 03-10-det4.asm | Listing garbled: rows were missing or merged. Test garbled |
| 3.11 4×3 matrix addition | CORRECTED | p.59 | 03-11-matrix-add.asm | Steps 47–55 were garbled |
| 3.12 Matrix multiplication | CORRECTED | p.59–60 | 03-12-matrix-mul.asm | We had 27 steps; the book has 69 (uses F⟳) |
| 3.13 2×2 inverse | CORRECTED | p.60–61 | 03-13-inverse2.asm | Steps 13, 17 and 27 are ÷, not + |
| 3.14 3×3 inverse | CORRECTED | p.61 | 03-14-inverse3.asm | Step 04 is ÷. Steps 30–49 were garbled or duplicated |
| 3.15 n!, n ≥ 1 | VERIFIED | p.61 | 03-15-factorial.asm | |
| 3.16 n!, any n | VERIFIED | p.61 | 03-16-factorial-any.asm | |
| 3.17 Stirling n! | CORRECTED | p.61–62 | 03-17-stirling.asm | `1 2 ÷ ИП9 ÷` (steps 10–14) was missing. Book prints 56! = 7,1100172·10⁷⁴, not 7.1099859·10⁷⁴ |
| 4.1 sh | VERIFIED | p.64 | 04-01-sinh.asm | |
| 4.2 ch | VERIFIED | p.64 | 04-02-cosh.asm | |
| 4.3 th | VERIFIED | p.64 | 04-03-tanh.asm | |
| 4.4 arsh | VERIFIED | p.64 | 04-04-arsh.asm | |
| 4.5 arch | VERIFIED | p.64 | 04-05-arch.asm | |
| 4.6 arth | CORRECTED | p.64 | 04-06-arth.asm | Step 08 is ÷, not + |
| 4.7 arcth | VERIFIED | p.65 | 04-07-arcth.asm | |
| 4.8 Continued fraction | CORRECTED | p.65 | 04-08-contfrac.asm | Listing is correct. The test result is 6,8765432, not 6.8785432 |
| 4.9 Rational function | VERIFIED | p.65 | 04-09-ratfunc.asm | |
| 4.10 Horner, real | CORRECTED | p.65–66 | 04-10-horner.asm | `+ ИП0 Fx=0` was missing. Test polynomial typo |
| 4.11 Horner, complex | CORRECTED | p.66 | 04-11-complex-poly.asm | Listing garbled (60 steps). Test should read a₉ = a₁₀ = 0, not a₀ |
| 4.12 Sum 1..n | VERIFIED | p.66–67 | 04-12-sum-int.asm | README page 67 should be 66 |
| 4.13 Sum of factorials | VERIFIED | p.67 | 04-13-sum-fact.asm | |
| 4.14 Product of factorials | VERIFIED | p.67 | 04-14-prod-fact.asm | |
| 4.15 Σkⁿ | VERIFIED | p.67–68 | 04-15-sum-powers.asm | Our test (m=5, n=2) is not from the book. The book's example is m=20, n=4 → 722665,91. Both are in the .mk56 |
| 4.18 Hermite coefficients | CORRECTED | p.69 | 04-18-hermite-coef.asm | Listing is correct. Our test (P₅ = 7.875x⁵ − 6.75x³ …) belongs to 4.17 (Legendre) and has a typo (8,75). The 4.18 example is H₈ |
| 4.19 Chebyshev coefficients | CORRECTED | p.69 | 04-19-chebyshev-coef.asm | Listing garbled (61 steps) |
| 4.20 Laguerre | CORRECTED | p.69–70 | 04-20-laguerre.asm | We had no listing. Our test L₅(2) = −0.46666667 is wrong: the true value is 0.7333. The book's examples are L₂, L₃, L₄ at x = 3 |
| Sinc y = sin(πnft)/πnft | CORRECTED | p.22–24 (ch.1, unnumbered) | 01-01-sinc-branch.asm, 01-02-sinc-loop.asm | The jump addresses of the two variants were swapped (04 ↔ 06). The loop variant was missing a × |
| 5.1 Linear system n ≤ 4 | CORRECTED | p.79 | 05-01-linsys.asm | Listing garbled. The book's listing uses all 98 steps. Step 08 is ÷ |
| Quadratic equation | NOT-FOUND | — | — | Invented. Book equivalents: 5.29, 5.30 (p.97) |
| Newton-Raphson (generic) | NOT-FOUND | — | — | Invented outline. Book equivalents: 5.16, 5.17 (p.89) |
| Trapezoidal integration | NOT-FOUND | — | — | Invented outline. Book: 5.46 (p.107) |
| Bisection | NOT-FOUND | — | — | Invented outline. Book: 5.22 (p.92) |
| Combinations C(n,k) | NOT-FOUND | — | — | Invented outline. Book: 3.19 (p.62) |
| Permutations P(n,k) | NOT-FOUND | — | — | Invented outline. Book: 3.19 (p.62) |
| Efficient combinations | NOT-FOUND | — | — | Invented outline with an "XX" placeholder |
| Double factorial | NOT-FOUND | — | — | Invented. It uses "Fx>0", which does not exist on the МК-56 |
| 5.15 Simple iteration | CORRECTED | p.89 | 05-15-iteration.asm | Listing is correct. The book's result is 1,1712298 (we had 1.171298) |
| 5.16 Newton, machine zero | CORRECTED | p.89 | 05-16-newton.asm | The leading `ПД` was missing. Hangs under binary doubles (see below) |
| 5.17 Newton, ε² | VERIFIED | p.89 | 05-17-newton-eps.asm | Template. Instantiated with the book's check function; ε² is our choice |
| 5.32 Fifth-degree equation | CORRECTED | p.98–99 | 05-32-quintic.asm, 05-32-quartic.asm | Listing garbled. The book has two programs numbered 5.32: a quartic (p.98) and a quintic (p.99). Our test belonged to the quartic |
| 7.8 Pot-core coil | CORRECTED | p.179 | 07-08-coil-pot-core.asm | We had about 40 of 57 steps. `, 7 4` (19,74) was garbled |
| 7.9 Closed-core coil | CORRECTED | p.179–180 | 07-09-coil-closed-core.asm | We had no listing. Transcribed from the book |
| Transistor h-parameters | NOT-FOUND | — | — | Description only. Book: 7.29, 7.30 (p.191–192) |
| Rectifier | NOT-FOUND | — | — | Description only. Book: 7.28 (p.190) |
| Small-signal amplifier stages | NOT-FOUND | — | — | Description only. Book: 7.31–7.33 (p.194–195) |
| RC/RL time constants | NOT-FOUND | — | — | Description only. Nearest in the book: 5.67, RC-circuit response (p.118) |
| Statistical moments | NOT-FOUND | — | — | Formulas only. Book: 5.80 (p.135) |
| Mean and variance | NOT-FOUND | — | — | Invented outline. Book: 5.80, 5.81 (p.135–136) |
| Linear regression | NOT-FOUND | — | — | Formulas only. Book: 5.89 (p.140) and the following programs |
| Correlation coefficient | NOT-FOUND | — | — | Formulas only. Book: 5.82 (p.136) |
| Normal distribution | NOT-FOUND | — | — | Description only. Book: 6.31–6.36, Φ(x) (p.167–169) |
| Monte Carlo | NOT-FOUND | — | — | Description only. Book: 5.85–5.88, random numbers (p.138–139) |

"NOT-FOUND" means that **our text** cannot be found in the book. In every case it is an invented outline in pseudo-algebraic notation (`x→П`, `√x`, `XX` placeholders) or a description with no listing. The "Book" column names the real program a rewrite should use instead. None of those programs was transcribed in this audit.

## Details: CORRECTED programs

Step numbers are 2-digit addresses in the corrected listing.

- **3.3**: step 01 is `÷` (x/ε), not `+`.
- **3.4**: steps 04 and 08 are `÷`. Step 04 computes sign(x) = x/|x|; step 08 computes |x|/ε. With `+` the program is meaningless.
- **3.6**: `programs/01-basic-operations.md` shows the 3.7 listing under 3.6. The correct listing is 36 steps, `Fπ ÷ 1 8 0 ПП 19 ИП8 6 0 ПП 19 … КИП9 ↔ ИП9 − П8 В/О`. It needs a return-stack depth of 2. Test: 2 rad → 114, 35, 29,616. The printed 29,616 is an 8-digit artefact; double precision gives 29,6195.
- **3.7**: steps 07, 12 and 19 are `÷` (/60, /60, /180).
- **3.10**: our listing had rows dropped and merged. The book's listing has 90 steps: four rotations of the column registers, each followed by `ПП 54`, and a 3×3 determinant subroutine at 54 that ends `С/П × ИП0 + П0 ИПa В/О`. Test protocol: С/П → A₁ = 8; enter a₁ = 6 → B₁ = 16; −b₁ = −3 → C₁ = 52; c₁ = 0 → D₁ = 72; −d₁ = −3 → Δ = −216. Our "A₁=6, B₁=8, …" mixes up inputs and outputs.
- **3.11**: the last block is `… 0 С/П ИП0 + П0 1 0 С/П ИПa + Пa 1 1 С/П ИПb + Пb БП 00`. We had `ИПa 1 1` in place of `ИП0 + П0 1 0 С/П ИПa + Пa`. The book prints no numbers, only a check: put each register's own number in it and add the same matrix, and every register doubles. That is the test.
- **3.12**: the book's listing has 69 steps, ours had 27. The subroutine at 16 prompts with 1, 2, 3, 4, accumulates c_i1 in R3 and c_i2 in Rd, and uses `F,` (= F⟳) four times. Output: c11 = R9, c12 = Rb, c21 = R6, c22 = Rc, c31 = R3, c32 = Rd. Example: 17, 11, 15, 16, 19, 5.
- **3.13**: steps 13, 17 and 27 are `÷`. The algorithm divides by the determinant, and only ÷ makes it work.
- **3.14**: step 04 is `÷`. Steps 30–49 are `ИП8 × − П4 ИП3 ИПd ИП9 × − П5 ИП8 ИП7 ÷ П1 ИП9 ИП7 ÷ П2 ИП7 F1/x`. Ours had a duplicated, garbled block and no `F1/x`.
- **3.17**: steps 10–14 are `1 2 ÷ ИП9 ÷`. Ours dropped them, so the 1/(12n) factor was missing. Book results are 10! = 3628711,6, 20! = 2,4328826·10¹⁸ and 56! = 7,1100172·10⁷⁴. Our 7.1099859·10⁷⁴ is the exact 56!, not what the program prints.
- **4.6**: step 08 is `÷`, giving (1+x)/(1−x).
- **4.8**: the listing matches. The test value is **6,8765432**; we had 6.8785432. Input order for [5; 8/4; 2/7; 3/5] is a₃ = 5, b₃ = 3, a₂ = 7, b₂ = 2, a₁ = 4, b₁ = 8, a₀ = 5.
- **4.10**: the template is `ПД … … П0 ИПn ↑ XY ИПД × КИП0 + ИП0 Fx=0 06 XY ИПС + С/П БП 00`. The footnote says "…" is n keyed as two digits. Ours lacked `+ ИП0 Fx=0`. The test polynomial is 0 + 1x + 2x² + 3x³ + 4x⁴; ours read "2x³ + 3x⁴ + 4x⁴". The program file instantiates n = 4.
- **4.11**: the book's listing has 60 steps with a complex-Horner subroutine at 42. Ours was garbled and two rows short. Input: a = Y, b = X. Output: c = X, d = Y; d is also left in Rd. The test condition is a₉ = a₁₀ = 0 (we had a₀ = a₁₀ = 0).
- **4.18**: the listing matches. Our test "P₅ = 7.875x⁵ − 6.75x³ + 1.875x" is the end of program 4.17 (Legendre), and the book prints 8,75 there, not 6.75. The 4.18 example is H₈ = x⁸ − 28x⁶ + 210x⁴ − 420x² + 105, read one coefficient per С/П and ending with 0.
- **4.19**: the book's listing has 61 steps. Steps 20–57 differ from ours throughout.
- **4.20**: the book's listing has 38 steps: n = Rd, x = X, a recurrence loop, and an exit by `Fx≥0`. Ours had no listing, and its test L₅(2) = −0.46666667 is wrong (L₅(2) = 88/120 = 0.7333…). The book's examples are L₂(3) = −0,5, L₃(3) = 1 and L₄(3) = 1,375.
- **Sinc**: the book has `Fx=0 04 1 С/П Fπ ИП8 ИП9 × × × Fsin FBx ÷ С/П` (press В/О for each new t) and `Fx=0 06 1 С/П БП 00 Fπ ИП8 ИП9 × × × Fsin FBx ÷ БП 03`. Ours had the addresses swapped and only two × in the loop variant. The example on p.23 is n = 2, f = 1000, t = 1,2·10⁻⁴ → 0,90790883.
- **5.1**: the book's listing has 98 steps and is reproduced in full in the program file. Ours was garbled from step 06 onward. Protocol: n → R0, then all a_ij and b_i row by row, each followed by С/П. Output: x₁ in X; x₁…x₄ in Rd, Rc, Rb, Ra. The book's example for n = 3 reproduces exactly (1,9091983, 3,1949644, 5,0448073).
- **5.15**: the listing matches. The result is **1,1712298** (ours read 1.171298). x₀ = 1,2 and f(x) = `ИПД Fsin ИП9 +` with R9 = 0,25 come from the 5.14 example on p.88.
- **5.16**: `ПД` at step 00 was missing. Check example: x₀ = 1,3 → 1,1712297.
- **5.32**: the book prints two programs numbered 5.32. The **quartic** is on p.98 and its example is x⁴ + 9x³ + 31x² + 59x + 60 (x₁,₂ = −1 ± j·1,9999999, x₃ = −3, x₄ = −4; Rd = −2, R7 = 4,9999998). The **quintic** is on p.99 and its example is x⁵ + 8x⁴ + 31x³ + 80x² + 94x + 20 (x₁,₂ = −1 ± j·3,0000178, x₃ = −3,7320507, x₄ = −0,2679458, x₅ = −2,000032). Our entry describes the quintic but has a garbled listing and uses the quartic's test. Both programs are now transcribed; both rely on ЕГГОГ semantics (see below).
- **7.8**: the book's listing has 57 steps; ours had about 40, with the A-term block garbled and 19,74 written as `1 9 … 7 4` without the comma. The input loop stores values with `КП0` (R0 counts down from 8). The examples reproduce exactly (103,26144 and 46,179922).
- **7.9**: we had no listing. The book's listing has 33 steps. Examples: 415,23228 and 185,69752.

## Details: NOT-FOUND entries

Quadratic equation, Newton-Raphson (generic), Trapezoidal integration and Bisection are in `05-numerical-methods.md`. Combinations, Permutations, Efficient combinations and Double factorial are in `06-factorial-combinatorics.md`. Transistor h-parameters, Rectifier, Small-signal amplifier stages and RC/RL time constants are in `07-scientific-engineering.md`. Statistical moments, Mean and variance, Linear regression, Correlation, Normal distribution and Monte Carlo are in `08-statistics-sequences.md`.

None of these is a book transcription. They are pseudo-code outlines in a non-МК-56 notation (`x→П`, `П→x`, `√x`, `x²`, `/~/`), have unresolved `XX` jump targets, use an operator that does not exist (`Fx>0`), or have no listing at all. They were deleted and replaced with the book programs listed in the table (next section). The old claim in `08-statistics-sequences.md` that the МК-56 lacks a random-number generator was dropped with the file: the claim is true, but the book provides generator programs (5.85–5.88), now in the library.

## Transcriptions that replace the NOT-FOUND entries

Method as above: listings read from page images at 300–600 dpi, every ÷/+ glyph decided by the formula, and every program run on the repo's assembler and emulator against the book's worked example. All 27 pass. The book has no double-factorial program (pp.61–62 hold only 3.15–3.19), so that entry has no replacement; "Efficient combinations" is covered by 3.19.

| Replaces | Book programs | Listings |
|---|---|---|
| Combinations, Permutations, Efficient combinations | 3.19 (p.62) | 03-19-combinations.asm |
| Bisection | 5.22 (p.92) | 05-22-bisection.asm |
| Quadratic equation | 5.29, 5.30 (p.97–98) | 05-29-quadratic.asm, 05-30-quadratic-precise.asm |
| Newton-Raphson (generic) | 5.16, 5.17 (already in the library) | — |
| Trapezoidal integration | 5.46, 5.47 Simpson (p.107) | 05-46-trapezoid.asm, 05-47-simpson.asm |
| RC/RL time constants | 5.67 (p.118) | 05-67-rc-circuit.asm |
| Statistical moments, Mean and variance | 5.80, 5.81 (p.135–136) | 05-80-moments.asm, 05-81-u3-u4.asm |
| Correlation coefficient | 5.82 (p.136) | 05-82-correlation.asm |
| Monte Carlo | 5.85–5.88 (p.138–139) | 05-85-random.asm … 05-88-random-normal.asm |
| Linear regression | 5.89 (p.140) | 05-89-regression.asm |
| Normal distribution | 6.31–6.36 (p.167–169) | 06-31-erf-series.asm … 06-36-erf-approx5.asm |
| Rectifier | 7.28 (p.190) | 07-28-rectifier.asm |
| Transistor h-parameters | 7.29, 7.30 (p.191–193) | 07-29-…, 07-30-… |
| Small-signal amplifier stages | 7.31–7.33 (p.194–195) | 07-31-…, 07-32-…, 07-33-… |

6.31–6.36 compute the probability integral, not the density; the density ψ(x) is program 6.37 (p.169–170), not transcribed.

**÷ printed as a small bold "+"** (each decided by the formula and the example): 3.19/18, /21; 5.22/02, /08; 5.30/27; 5.46/13; 5.82/43, /49, /59; 6.32/05; 7.28/04, /89, /93; 7.29/13, /20; 7.32/56; 7.33/39. 5.89/49 prints as "−" with a stray dot and is −.

**Misprints in the book** (the listing is transcribed as printed; the test follows the program):
- **5.29, p.98:** x₂ = −6,66666666·10⁻⁴ for 3x² + 20000x + 12 cannot come from 8-digit arithmetic, where p + √D is a multiple of 10⁻⁴. That check is left out (5.30 exists to fix exactly this case).
- **5.30:** the text gives x₂ = −a₀/(x₁a₂); the program correctly computes +a₀/(a₂x₁).
- **5.46, table 5.4:** "0,906642285" has a doubled 6; read as 0,90642285.
- **6.31:** the printed Φ(4) = 0,99993495 is the series' rounding error (exact 0,99993666) and is not tested.
- **6.34:** the text gives Φ(−x) = 1 − Φ(x); erf is odd, so Φ(−x) = −Φ(x).
- **7.32:** the printed Rвых formula has (a·rк + rэ); the listing computes (a·rк − rэ), and only that reproduces 37217,544.
- **7.33:** K_I is printed as 48,421071; the formula and the listing give 48,721071.
- **7.31–7.33:** both R4 and R5 are labelled "Rн". R4 is the source resistance Rи, R5 the load.

**Precision observations** (no emulator change; recorded for the chip-level work in the README's Future work):
- At m = 64, 5.46 and 5.47 differ from the book by 6–7·10⁻⁷ relative. A Python model with 8-digit truncation reproduces the emulator exactly; 8-digit *rounding* lands closer to the book (trapezoid 0,90738956 vs printed 0,9073897; emulator 0,90738906).
- 5.86's third output: emulator 0,493815, book 0,493816; the underlying sum 13,4938156 truncates to the former and rounds to the latter.
- 5.82 r and 5.88 differ in the 8th digit; 5.80's excess E cancels terms near 10⁴ and agrees to about 3 digits (tolerance 3e-3).
- The manual itself shows truncation for F1/x (1/560 gives 1,7857142 -03 in the parallel-resistor example, [ch.5](../docs/manual/05-automatic-mode.md)), so if the book's machine rounded anywhere it was in other operations. Only the real microcode can settle this.

## Findings that bear on emulator semantics (ISA doc §2–3)

The book does not contradict anything in the ISA doc. It confirms several [INF] items and adds requirements the doc does not state.

1. **Confirmed: conditionals jump when the condition fails.** p.24 says it explicitly: with t = 0, "the condition t = x = 0 holds, the jump address 04 is ignored and 1 is displayed".
2. **Confirmed: F⟳ rotation direction (X→T, T→Z, Z→Y, Y→X).** 3.12 and 5.1 reproduce the book's results with this direction and fail with the opposite one. These are the strongest available tests for F⟳ and for its code being programmable. The book prints the key as "F,".
3. **Confirmed (§8 [INF]): a digit typed after x→П lifts the stack.** The stack table on p.23 shows the state after keying n П8, f П9, t as Z = n, Y = f, X = t.
4. **New: F π also sets X1 ← old X.** In the same p.23 table X1 changes from 0 to t after Fπ. That table also confirms that Fπ lifts after digit entry, that × copies the old X into X1, and that FBx does not change X1. The ISA doc lists only the lift for Fπ.
5. **Missing from the doc: indirect access with out-of-range register values must not fail.** 3.1–3.4 and 3.6 use the Б3-34 idiom `ПM КИПM ИПM` (M ≥ 7) to truncate to an integer. There the register holds values such as 123,4567, 1234 or 12345, so КИП reads "register 123". 4.15 increments R4 up to 20 through `КИП4`. The book only needs the side effect: the register is truncated or modified and stored back. The value loaded into X is discarded. The emulator must accept any register number, store the modified value, and load something (any value) without raising ЕГГОГ.
6. **Missing from the doc: an error inside a program must keep the stack and allow resuming.** The 5.32 quartic deliberately divides by 0 at step 44 to signal complex roots. It expects С/П to resume at step 45 (`Cx F⟳ ↔ БП 54`) with Y = m and Z = d still in place. The 5.32 quintic expects X (= −m²) and Y (= d) to survive an error in `F√`, so that the user can key ↔. The emulator should therefore stop on ЕГГОГ with PC already past the failing step, leave X, Y, Z and T unchanged, and let С/П continue.
7. **Missing from the doc: С/П in a program ends digit entry.** In 3.11 the program keys a prompt digit (`7 С/П`), then the user keys a matrix element. If the program's `7` were still open for entry, the user's digits would be appended to it.
8. **Precision: the book's results come from 8-digit decimal arithmetic, so binary doubles will not match exactly.** Rerunning the listings with 8-digit truncation reproduces printed digits exactly: 3.6 gives 29,616 (doubles give 29,6195) and 4.15 gives 722665,92 vs the printed 722665,91 (doubles give 722666,00). The test tolerances are set so that both models pass.
   - **The serious case is 5.16:** it stops when the Newton correction is exactly 0. Under doubles the iteration settles into a two-value cycle of ±1,8·10⁻¹⁶ and **never terminates**. A naive 8-digit-rounding model also cycles, while the real machine stopped after about 30 s.
   - The test runner needs a step limit, and 05-16-newton.asm is expected to fail until the emulator does МК-56-style decimal arithmetic. 5.15 has the same kind of stop but terminates under doubles.
9. **xʸ:** 3.17 and 4.15 confirm base = X and exponent = Y. All listings pass both with xʸ dropping the stack and with xʸ keeping Y, so the book does not settle that open question.
10. **Return stack:** 3.6 nests two levels of ПП, 3.10 and 4.11 one level. Nothing approaches the 5-level limit.

## Format notes for the program files

- Each program is one MK56-ASM file. Its header holds the description, the test directives and the book's listing **as printed** (`; As printed:` followed by `;   NN: keys…` lines). `make test` checks that this listing assembles to exactly the same steps as the code below it.
- In the printed listing, every line starts with an `NN:` address assertion. Lines are broken so that a jump and its address byte are always on the same line, which is why some lines do not start at a multiple of 10.
- Directive values use a decimal point and `e` exponents (`@expect X=2.432902e18`). Listing tokens use the canonical spellings, with `,` for the decimal point.
- Where the book gives a template ("…" to be filled in by the user: 3.5, 4.10, 5.15–5.17), the program file instantiates it with the book's own example data and says so in the header.
