# Электроника МК-56: machine reference

The instruction set and behaviour as taken from the original manual, with a
page citation for each fact. The emulator is built from this document.

**Source:** `references/MK-56 inst.pdf`. This is a scan of the factory manual "Микрокалькулятор Электроника МК56 — Техническое описание и инструкция по эксплуатации". It has 51 PDF pages and no text layer.
**Page citations:** "p.N" means the **printed manual page**. From PDF page 3 onward, PDF page *k* holds manual pages 2k−2 and 2k−1. So p.51 (Table 4) is on PDF page 26, and the functional test (p.96–100) is on PDF pages 49–51.
**Secondary source:** `references/book61.pdf` is V.P. Дьяконов, *Справочник по расчётам на микрокалькуляторах* (Наука). It has 226 pages and an ABBYY OCR text layer. It covers the Б3-34, МК-54 and МК-56 and says that the МК-56 is "fully compatible with the Б3-34 in programming language and instruction set". It is cited only where the manual is silent, as "book61 PDF p.N".

Each statement is in one of three groups:
- **[M]**: stated in the manual, or shown directly in a manual table or example.
- **[M-derived]**: follows from tracing a printed manual example. The trace reproduces the printed result.
- **[INF]**: *inferred — B3-34 family convention* (or book61). It is **not** in the manual. These items are collected in §8.

### Reading the scan (needed to read the tables correctly)
- The **÷ key prints almost like "+"**. You can only tell them apart by code (`13` is ÷, `10` is +) or by the arithmetic. Example: Table 13 addr 08 "+" = `13` = ÷. Functional test #30 prints "+" with code `13`.
- **The digit 1 is printed as "I"** throughout the manual (I4 = 14, I0ˣ = 10ˣ, etc.).
- **Codes are shown in 7-segment hex glyphs** (p.51–55, functional test): `-` = A, `L` = B, `С`/`Г-like C` = C, `Г` = D, `Е` = E, blank = F. For example `0-` = 0A, `5Г` = 5D, `-L` = AB, `ЕГ` = ED, `0 ` (blank) = 0F.
- **Register letters:** a, в (= b), c, d. The keyboard prints "в" for b (p.12, p.15).

---

## 1. Machine parameters

| Item | Value | Cite |
|---|---|---|
| Number system | Decimal input and output | p.5 §2.1.1 [M] |
| Mantissa digits | 8 | p.5 §2.1.2 [M] |
| Exponent digits | 2 (±99) | p.5 §2.1.3 [M] |
| Range | 1·10⁻⁹⁹ ≤ \|x\| ≤ 9.9999999·10⁹⁹ | p.5 §2.1.4, p.24 [M] |
| Display | 12-position vacuum-fluorescent display. Positions: 1 = mantissa sign, 2–9 = 8 mantissa digits, 10 = exponent sign, 11–12 = exponent digits | p.5 §2.1.6, p.21, functional test column layout p.96 [M] |
| Natural vs exponent display | Natural (fixed-point) display only for 1 ≤ \|x\| < 10⁸. Otherwise mantissa plus exponent, so results < 1 are shown as e.g. `5,55025 -01` | p.5 §2.1.5, p.21 §5.2.1, p.26–28 examples [M] |
| Program memory | **98 steps, addresses 00–97**. One step = one 2-digit code | p.7 §2.1.12, p.50 §6.1.4–6.1.5, p.56 §6.1.6–6.1.7 [M] |
| Addressable registers | **14**: R0–R9, Ra, Rb (printed "в"), Rc, Rd. In indirect codes they are numbered 0–13 (a = 10, b = 11, c = 12, d = 13) | p.6, p.11, p.48 §5.9.1, p.76 Table 12 [M] |
| Stack | 4 registers X, Y, Z, T ("магазинная память"). All zero at power-on | p.11, p.34–35 §5.7.1–5.7.2 [M] |
| Previous-result register | X1 (same as "Bx"); recalled with F Bx | p.38 §5.7.6, p.43–44 §5.8 [M] |
| Return stack | **5 levels** ("глубина … равна 5", "пятиразрядный стек возврата"), last-in first-out | p.8 item 3, p.56 §6.1.10, p.59 §6.2.1.4 [M] |
| Angle units | 3-position switch **Г/Р/ГРД** (degrees / radians / grads). It affects sin, cos, tg and their inverses. Other functions ignore it | p.6, p.19 §2.3.2, p.25 §5.5.2, p.26 §5.5.3 [M] |
| Keys / operations | 30 keys, 51 operations. Two prefixes: **F** (legends above the keys) and **К** (legends below the keys, plus indirect ops) | p.11 §2.2.5, p.12 Fig.2, p.16 [M] |
| Constant π | 3,1415926 (8 digits) | p.14, p.27 [M] |
| Power-on | Auto mode. All registers, program memory and stack are zeroed. The display shows "0," (functional test #0). p.20 §4.1 prints `"С"` in the top digit, which is probably a misprint of 0 | p.20–21 §5.1.1, p.35 §5.7.2, p.50 §5.9.6, p.63 "ВНИМАНИЕ", p.96 test 0 [M] |
| Timing (spec) | +, −, ×, ÷, 1/x, √, x² ≤ 0.5 s. xʸ ≤ 3.5 s. ln, lg, eˣ, 10ˣ, trig ≤ 2 s on average. Functional test #87 ≤ 40 s | p.6 §2.1.10, p.100 [M] |

### Keyboard (p.12 Fig. 2)

| Main key | F-legend (above) | К-legend (below) |
|---|---|---|
| ШГ (top; arrow direction is illegible in the scan) | x<0 | — |
| ПП | L3 | — |
| F | — | — |
| ШГ (second) | x=0 | — |
| БП | L2 | — |
| К | — | — |
| В/О | x≥0 | — |
| x→П | L1 | — |
| С/П | x≠0 | — |
| П→x | L0 | — |
| 7 / 8 / 9 | sin / cos / tg | — |
| 4 / 5 / 6 | sin⁻¹ / cos⁻¹ / tg⁻¹ | — |
| 1 / 2 / 3 | eˣ / lg / ln | — |
| 0 | 10ˣ | НОП |
| . | ⟳ (stack rotate) | a |
| /-/ | АВТ | в |
| − | √ | — |
| ÷ | 1/x | — |
| + | π | — |
| × | x² | — |
| В↑ | Bx | — |
| ↔ | xʸ | — |
| ВП | ПРГ | c |
| Cx | CF | d |

Register-name keys: after x→П, П→x, К x→П, К П→x, К БП, К ПП and the К conditional prefixes, the keys `.`, `/-/`, `ВП` and `Cx` mean a, b, c and d (p.12, p.15).

---

## 2. Opcode table (Table 4, p.51–55, plus functional test p.96–100)

The codes are printed in Table 4 unless the row says otherwise. Stack notation: **lift** = T←Z, Z←Y, Y←X (X is then overwritten). **drop** = Y←Z, Z←T, T unchanged (T is duplicated). **X1←X** = the old X is saved to the previous-result register.

### 2.1 Digit entry and editing (0x)

| Code | Keys | Semantics | Stack / X1 | Cite |
|---|---|---|---|---|
| 00–09 | 0 … 9 | Enter a digit into X | First digit after an op result lifts the stack (p.28–29 §5.6.5, p.40–42). No lift after В↑ (p.39–40, p.42) or after Cx (p.37). X1 is unchanged [M-derived: functional test trace] | p.51; p.13 Table 2 |
| 0A | . | Decimal point | Part of entry | p.51 |
| 0B | /-/ | Change the sign of the mantissa, or of the exponent while the exponent is being entered | — | p.13, p.22–23 §5.3.5, §5.3.7 [M] |
| 0C | ВП | Start exponent entry. If the mantissa is 0 it becomes 1 | — | p.13, p.23 §5.3.8; test #102 [M] |
| 0D | Cx | X ← 0. Y, Z and T are unchanged. The next digit does not lift | X1 unchanged (p.45 §5.8.3: clearing X1 needs "Cx then any operation") | p.37 [M] |
| 0E | В↑ | Normalise X, then lift (Y←X, Z←Y, T←Z; T is lost). X keeps its value. The next digit overwrites X | X1: not stated | p.13, p.23 §5.3.9, p.35 §5.7.4 [M] |
| 0F | F Bx | Recall X1 into X **with stack lift** (T lost, Z←Y, Y←X, X←X1). X1 unchanged | lift | **Not in Table 4.** Code 0F is shown by functional test #82 (display `0 ` = 0F) [M]. Stack diagram p.44 §5.8.1, data p.46–47 [M] |

### 2.2 Arithmetic and stack (1x)

| Code | Keys | Semantics | Stack / X1 | Cite |
|---|---|---|---|---|
| 10 | + | X ← Y + X | drop. X1 ← X | p.51; diagram p.39 §5.7.8; p.43 [M] |
| 11 | − | X ← Y − X | drop. X1←X | p.51; p.28 ("12 В↑ 3 −" gives 9) [M] |
| 12 | × | X ← Y · X | drop. X1←X | p.51 [M] |
| 13 | ÷ | X ← Y / X. Error if X = 0 | drop. X1←X | p.51; p.28 ("12 В↑ 3 ÷" gives 4) [M] |
| 14 | ↔ | Swap X and Y. Z and T unchanged | X1: not stated in the manual | p.13, p.36, p.37, p.43 [M] |
| 15 | F 10ˣ | X ← 10^X | unary. X1←X | p.51, p.26 [M] |
| 16 | F eˣ | X ← e^X | unary. X1←X | p.51, p.26 |
| 17 | F lg | X ← log₁₀ X (error if X ≤ 0) | unary | p.51, p.24, p.26 |
| 18 | F ln | X ← ln X (error if X ≤ 0) | unary | p.51, p.24, p.26 |
| 19 | F sin⁻¹ | X ← arcsin X in the selected angle unit (error if \|X\| > 1) | unary | p.51, p.24, p.26 |
| 1A | F cos⁻¹ | X ← arccos X (error if \|X\| > 1) | unary | p.51 (`1-`) |
| 1B | F tg⁻¹ | X ← arctg X | unary | p.51 (`1L`) |
| 1C | F sin | X ← sin X | unary | p.51 (`1С`) |
| 1D | F cos | X ← cos X | unary | p.51 (`1Г`) |
| 1E | F tg | X ← tg X | unary | p.51 |

All unary operations: "the result goes into X, the contents of the other registers do not change" (p.25 §5.5.1). The old X goes into X1 (p.38 §5.7.6, diagram on p.39) [M].

### 2.3 F functions (2x)

| Code | Keys | Semantics | Stack / X1 | Cite |
|---|---|---|---|---|
| 20 | F π | X ← 3,1415926 **with lift** after an op result (p.30: "6000 F π ÷" gives 1909.8593). Behaviour right after В↑: see §8 | lift | p.51, p.27, p.30 [M] |
| 21 | F √ | X ← √X (error if X < 0) | unary | p.51, p.24, p.27 |
| 22 | F x² | X ← X² | unary | p.51, p.26 |
| 23 | F 1/x | X ← 1/X (error if X = 0) | unary | p.51, p.27 |
| 24 | F xʸ | **X ← X^Y. Base = X, exponent = Y.** Key order: enter y, В↑, enter x, F xʸ (p.28 §5.6.4: 21,7^15,6 gives 7,0594552 20; 4^−0,2 gives 7,5785828 −01). Functional test #5: X = 1,1447298, Y = 0, result `1,`. Domain x > 0 (Table 1, p.7). The manual classes it as a two-operand op ("информация в регистре Y … стирается", p.27 §5.6.1) | drop. X1←X (per p.27, p.39) | p.51 (printed as "F ↔"; the key is ↔ with legend xʸ) [M] |
| 25 | F ⟳ | **Code not in the manual** (Table 4 has no row; see §8). Semantics [M]: rotate X→T, T→Z, Z→Y, Y→X. **The old X is also copied to X1** | X1←X | Diagrams p.35 §5.7.5 and p.44 §5.8.2; data p.36–37, p.40, p.47 [M]. Code = [INF] |
| — | F CF | Cancels a pending F prefix. Not programmable (code cell blank) | — | p.14, p.50 §5.10, p.51 [M] |
| — | F ПРГ / F АВТ | Switch to programming / auto mode. Not programmable | — | p.15 Table 3, p.20, p.50 [M] |

### 2.4 Registers (4x, 6x)

| Code | Keys | Semantics | Stack | Cite |
|---|---|---|---|---|
| 40–49, 4A–4D | x→П 0…9, a, в, c, d | Rn ← X. X keeps its value ("число … сохраняется в регистре X") | no stack change. X1 unchanged [M-derived: test trace] | p.48 §5.9.2, p.52 [M] |
| 60–69, 6A–6D | П→x 0…9, a…d | X ← Rn. Rn unchanged | **lift** [M-derived: Table 13 and the functional-test trace need it] | p.49 §5.9.4, p.52 [M] |

### 2.5 Control (5x)

| Code | Keys | Semantics | Cite |
|---|---|---|---|
| 50 | С/П | In a program: stop and show X. Pressed in auto mode: start running from the current address, or stop a running program | p.16 Table 3, p.63 §6.2.4 [M] |
| 51 | БП NN | Two-step command: next byte = target address. Unconditional jump | p.15, p.64 §6.3.1, Table 6 (`51 42`) [M] |
| 52 | В/О | In a program: return from subroutine (pop the return stack). Auto mode: set PC = 00 | p.15, p.66–67 §6.3.4 [M] |
| 53 | ПП NN | Two-step command: push the address of the step after NN, then jump to NN. Auto mode: **single step** | p.15, p.66 §6.3.3, Table 8; p.63 §6.2.3.2 [M] |
| 54 | К НОП | No operation (used for editing) | p.17, p.52, p.62 §6.2.2.3 [M] |
| 57 | F x≠0 NN | Conditional (see rule below) | p.52 [M] |
| 59 | F x≥0 NN | Conditional | p.52 |
| 5C | F x<0 NN | Conditional | p.52 (`5С`) |
| 5E | F x=0 NN | Conditional | p.52 |
| 5D | F L0 NN | Loop on R0 | p.52 (`5Г`) |
| 5B | F L1 NN | Loop on R1 | p.52 (`5L`) |
| 58 | F L2 NN | Loop on R2 | p.52 |
| 5A | F L3 NN | Loop on R3 | p.52 (`5-`) |

**Conditional jump rule [M] (p.65 §6.3.2, Table 7, p.66):** The condition is tested on X. **If it does NOT hold, jump to NN.** If it holds, continue at the step after NN; the address byte is skipped. The stack is not changed.

**Loop rule [M] (p.82 §6.3.10, Fig. 6 p.83):** F Ln subtracts 1 from Rn and tests the result. **Result ≠ 0: store it and jump to NN. Result = 0: fall through to the step after NN.** In that case Rn **keeps the value 1**: the manual says that after the last pass П→x 0 shows `00000001,` (p.82). Functional test #93 also shows R3 = `00000001,` after an L3 loop.
**Decrement of 0** (functional test #19–#21 trace, #92): F L2 with R2 = 0 leaves R2 = **`-99999999,`**. That result is ≠ 0, so the loop jumps [M-derived].

### 2.6 К-prefixed (indirect) codes

| Code range | Keys | Semantics | Cite |
|---|---|---|---|
| 70–7D | К x≠0 R | Indirect conditional jump | p.54–55 [M] |
| 80–8D | К БП R | Indirect unconditional jump | p.52–53 [M] |
| 90–9D | К x≥0 R | Indirect conditional | p.54 [M] |
| A0–AD | К ПП R | Indirect subroutine call (pushes the address of the next step) | p.53 (`-0` … `-Г`), p.73 §6.3.7 [M] |
| B0–BD | К x→П R | Indirect store: R[mod(R)] ← X | p.55 (`L0` … `LГ`), p.76 §6.3.8 [M] |
| C0–CD | К x<0 R | Indirect conditional | p.53–54 (`С0` … `СГ`) [M] |
| D0–DD | К П→x R | Indirect recall: X ← R[mod(R)] (lift [INF], as for П→x) | p.55 (`Г0` … `ГГ`), p.77 §6.3.9 [M] |
| E0–ED | К x=0 R | Indirect conditional | p.53 [M] |

**Address modification [M] (p.67 §6.3.5):** the register named in the command is modified first:
- **R0–R3: minus 1**
- **R4–R6: plus 1**
- **R7, R8, R9, Ra, Rb, Rc, Rd: unchanged**

The **modified** value is then used as the target address or register number ("переход к выполнению команды, записанной по новому (модифицированному) адресу").

- **Modification happens before use (pre-decrement / pre-increment). [M]**
  - p.77: R0 = 14, then `К x→П 0` stores into **Rd (13)** and R0 becomes `00000013,`.
  - p.78: R4 = 4, then `К П→x 4` loads **R5** and R4 becomes `00000005,`.
  - p.69–70: R3 = 5, then `К БП 3` jumps to **04**.
- **Register number mapping:** 0–9 → R0–R9, 10 → a, 11 → b, 12 → c, 13 → d (Table 12, p.76) [M].
- **Indirect conditionals (p.70 §6.3.6):** if the condition **fails**, modify the register and jump to the modified address. If it **holds**, go on to the next step and **do not modify** the register [M]. Functional test (addr 47–50) confirms both cases.
- **Storage format after modification:** the register then holds an unnormalised integer that displays with leading zeros, e.g. `00000004,` `00000012,` (p.70, p.77, p.78, p.82; test #93–94). **Even an "unchanged" R7–Rd register is rewritten this way:** Ra = 12 shows as `00000012,` after `К БП a` (p.70) [M].
- **Integer part only?** The manual does not say. It only shows integer examples. See §8 [INF/book61].

### 2.7 Codes the manual does not cover
- **25** (F⟳) is missing from Table 4. book61 Table 1.3 omits it too.
- **26–3F, 55, 56, 5F, 6E–6F, 4E–4F, 7E–7F, 8E–8F, 9E–9F, AE–AF, BE–BF, CE–CF, DE–DF, EE–EF, F0–FF:** not documented. Treat their behaviour as unknown.

---

## 3. Stack, entry and X1: rules confirmed by the manual

| Rule | Evidence |
|---|---|
| Binary op (+ − × ÷ xʸ): X ← Y∘X, Y←Z, Z←T, **T keeps its value**, X1 ← old X | Diagram p.39. Data p.42–43: 3 7 3 12 + gives T3 Z3 Y7 X15, × gives T3 Z3 Y3 X105. p.39 "+" shows 12 going to X1 [M] |
| Unary op: X ← f(X). Y, Z, T unchanged. X1 ← old X | p.25 §5.5.1, p.38 §5.7.6 (√375: X1 = 375), p.46 (sin: X1 = 2) [M] |
| В↑: lift and keep X | p.35 diagram. Data p.36: 4 В↑ 3 В↑ 2 В↑ 1 gives T4 Z3 Y2 X1. Another В↑ gives T3 Z2 Y1 X1 [M] |
| Digit after В↑ overwrites X (no lift) | p.39 (Cx В↑ В↑ В↑ 34 gives X = 34 with Y = 0), p.40, p.42 [M] |
| Digit after Cx overwrites X (no lift) | p.37: T1 Z1 Y2 X0, then 375 gives T1 Z1 Y2 X375 [M] |
| Digit after an op result lifts | p.28–29 §5.6.5. p.41 "15, 7 ×". p.45: T3 Z3 Y3 X35, then 14 gives T3 Z3 Y35 X14 [M] |
| Digit after F⟳ lifts | p.40: T64 Z4 Y4 X4, then 23 gives T4 Z4 Y4 X23 [M] |
| A digit after F⟳, and after П→x followed by an F x=0 jump, lifts | p.47 ("4" after F⟳), Table 13 addr 07 [M-derived] |
| F⟳: X→T, T→Z, Z→Y, Y→X, old X → X1 | p.35, p.44. Data p.36–37 (see note below) and p.47 [M] |
| F Bx: lift, X ← X1, X1 unchanged | p.44. p.46: T3 Z3 Y35 X0,48859, then F Bx gives T3 Z35 Y0,48859 X0,034899 [M] |
| ↔ only swaps X and Y | p.36–37, p.43 [M] |
| Cx + any op is how to clear X1 (so Cx itself does not write X1) | p.45 §5.8.3 [M] |
| Clear the stack with `Cx В↑ В↑ В↑` | p.38 §5.7.7 [M] |
| x→П, digit entry, БП, ПП, К ПП, В/О and conditionals do **not** write X1 | [M-derived] Functional test: F Bx at addr 62 must return −9,6903… (the X1 set by F x² at addr 51) to give e^x = 6,187848−05 (test #87). Digits 6 2, x→П в, К ПП в came in between |

Note on F⟳ (p.36): the printed sequence starts from T3 Z2 Y1 X1 (after the extra В↑) and gives T1 Z3 Y2 X1. A second F⟳ gives T1 Z1 Y3 X2 (p.37). Both match X→T, T→Z, Z→Y, Y→X.

### Number entry [M]
- **Mantissa entry:** digits go into X (p.22 §5.3.4). **Entry stops after 8 mantissa digits**: further digit keys have no effect (p.23 note).
- **/-/** after the mantissa changes its sign. On a finished number it toggles the sign (p.22 §5.3.5).
- **Exponent entry:** press **ВП**, then the exponent digits. Each new digit goes into the low exponent digit and the older digits shift left, so the high digit is lost (p.23 §5.3.8). **/-/ after ВП negates the exponent** (p.23: `148,12 /-/ ВП 15 /-/` gives `-148,12 -15`). ВП with mantissa 0 sets the mantissa to 1 (p.23; test #102: after Cx, ВП shows `1,` and `00`).
- **В↑ normalises the displayed number:** `-148,12·10⁴` then В↑ shows `-1481200,` (p.23 §5.3.9).

---

## 4. Auto mode vs programming mode [M]

| Action | Auto mode (АВТ) | Programming mode (ПРГ) |
|---|---|---|
| Enter mode | Power-on, or **F АВТ** (p.20 §5.1.1) | **F ПРГ** (p.50 §6.1.1) |
| Any programmable key | Executes the operation | Stores its code at PC, then PC+1 (p.50 §6.1.2, p.56 §6.1.8) |
| В/О | PC ← 00 (p.15, p.60, p.63 §6.2.4.1) | Stores code 52 |
| БП NN | Sets PC ← NN. The jump and the address are one step (p.61, p.63 §6.2.3.1–2) | Stores 51 NN |
| ПП | **Executes one program step** at PC (step mode). A jump together with its address counts as one step (p.15, p.63 §6.2.3.2, p.69) | Stores 53 |
| С/П | Runs from PC. Pressed while running: stops the program, e.g. to break an endless loop (p.16, p.63 §6.2.4.2–3) | Stores 50 |
| ШГ → / ШГ ← | — (described only for program mode) | PC +1 / −1 (p.17–18, p.61 §6.2.2.2) |
| К НОП | — | Stores 54 over a step you want to delete (p.62) |
| Display | X (p.22) | **Codes at PC−1, PC−2, PC−3, then the 2-digit PC**. Example: `02 01 0E 06` means 0E @03, 01 @04, 02 @05, PC = 06 (p.57 §6.1.12). Positions with no earlier step are blank (test #19–21) |
| Address byte after БП / ПП / F cond / F Ln | — | Two digit keys form **one** byte. `БП 4 2` gives `51 42` (p.64 Table 6). Test #22: "1 3" stores one step `13` |

While a program runs, the display is lit ("подсвет индикатора", p.63 §6.2.4.2).
The return stack is used only by ПП / К ПП / В/О during a run (p.66–67).

---

## 5. Display and errors [M]

- **Errors (p.24 §5.4.1–5.4.2)** show **«ЕГГОГ»**. On the 7-segment display this reads `E Г Г 0 Г` in positions 2–6 (test #100). Causes:
  - ÷ 0
  - xʸ with x = 0 (the y-condition is printed "y≷0", so it is unclear)
  - √ of x < 0
  - 1/x with x = 0
  - lg or ln of x ≤ 0
  - arcsin or arccos of \|x\| > 1
  - **overflow** \|result\| > 9,9999999·10⁹⁹
  - **underflow** \|result\| < 1·10⁻⁹⁹. The manual says this also shows ЕГГОГ and **X is set to 0**
- After ЕГГОГ you can type numbers and keep computing (p.24 example: `4 /-/ F √` shows ЕГГОГ, then `25` shows `25`). Test #100–101: ЕГГОГ, then Cx shows `0,`.
- **Function domains (Table 1, p.7):**
  - sin, cos, tg: 1·10⁻⁴⁹ < \|x\| < 10¹⁰
  - arcsin, arccos: \|x\| ≤ 1
  - arctg: any value
  - xʸ: 0 < x
  - eˣ: \|x\| < 100·ln10
  - x²: \|x\| < 10⁵⁰
  - 10ˣ: \|x\| < 99,999999
  - 1/x: x ≠ 0
  - √x, ln x, lg x: 0 < x
- **Accuracy (Table 1, p.7):** max relative error 3·10⁻⁷ for trig and logs, 1·10⁻⁶ for xʸ, 5·10⁻⁶ for eˣ, 4·10⁻⁷ for 10ˣ, 1·10⁻⁷ for x² and 1/x. √ is printed as 1·10⁻⁴, which is probably a misprint.
- **Display formatting:**
  - Comma decimal separator. Integers show a trailing comma (`32,`, `0,`).
  - Trailing zeros of the mantissa are suppressed: arcsin 0,975 shows `1,346721` (= 1.3467210); test #87 shows `6,187848 -05`.
  - Numbers outside [1, 10⁸) use mantissa + exponent: `-2, -01` for −0.2 after В↑ (p.28).
  - Indirectly modified registers show leading zeros (`00000013,`). Decrementing 0 shows `-99999999,` (test #92).
- **Entry display:** p.26 shows `412,` while typing. Test #16 prints `I4` with no comma while typing; that may be a printing slip.

---

## 6. Worked examples to use as emulator tests

**About exact digits:** the printed values come from the real 8-digit decimal microcode.
- `0,4 В↑ F π ×25 ×2,25` gives **70,685831** (p.34). This is only reproduced with π = 3,1415926 and 8-digit truncated arithmetic. Doubles give 70.685835.
- 1/560 gives **1,7857142 −03** (p.29) and 1/589 gives **1,6977928 −03** (p.27). Both are truncated, not rounded.
- Transcendental results often differ from IEEE values in the last 1–4 digits:
  - sin 32 rad: printed 5,5142714 −01, true value 5,5142668.
  - functional tests #6–#13.

Compare with a tolerance, or tag these values as "hardware digits".

### 6.1 Auto-mode keystroke examples (expected display after each line)

| Cite | Switch | Keys | Display |
|---|---|---|---|
| p.22 | | 1 4 8 . 1 2 | `148,12` |
| p.22 | | /-/ | `-148,12` |
| p.22 | | /-/ | `148,12` |
| p.22 | | Cx | `0,` |
| p.23 | | 148.12 /-/ ВП 15 /-/ | `-148,12 -15` (after ВП: `-148,12 00`) |
| p.23 | | −148,12·10⁴ then В↑ | `-1481200,` |
| p.24 | | 4 /-/ F √ | `ЕГГОГ` |
| p.24 | | 2 5 | `25` |
| p.25 | Р | 32 F sin | `5,5142714 -01` |
| p.25 | Г | 18 F cos | `9,5105655 -01` |
| p.25–26 | Г | 48.5 F tg | `1,1302944` |
| p.26 | Р | 0.975 F sin⁻¹ | `1,346721` |
| p.26 | Р | 0.2 F cos⁻¹ | `1,3694383` |
| p.26 | Г | 41 F tg⁻¹ | `88,602819` |
| p.26 | ГРД | 32 F sin | `4,8175367 -01` |
| p.26 | any | 412 F ln | `6,0210233` |
| p.26 | | 412 F lg | `2,6148971` |
| p.26 | | 12 F eˣ | `162754,78` |
| p.26 | | 0.48 /-/ F eˣ | `6,1878339 -01` |
| p.26 | | 4.75 F 10ˣ | `56234,135` |
| p.26 | | 1.48 /-/ F 10ˣ | `3,3113111 -02` |
| p.26 | | 0.745 F x² | `5,55025 -01` |
| p.27 | | 589 F 1/x | `1,6977928 -03` |
| p.27 | | 563 F √ | `23,727621` |
| p.27 | | F π | `3,1415926` |
| p.28 | | 12 В↑ 3 + | `15,` |
| p.28 | | 12 В↑ 3 − / × / ÷ | `9,` / `36,` / `4,` |
| p.28 | | 15.6 В↑ 21.7 F xʸ | `7,0594552 20` |
| p.28 | | 0.2 /-/ В↑ 4 F xʸ | after В↑: `-2, -01`. Final: `7,5785828 -01` |
| p.29 | | 220 F 1/x / 4000 F 1/x / + / 560 F 1/x / + / 1200 F 1/x + / F 1/x | `4,5454545 -03` / `2,5 -04` / `4,7954545 -03` / `1,7857142 -03` / `6,5811687 -03` / `7,414502 -03` / `134,87082` |
| p.30 | | 12000 В↑ / 2 ÷ / F π ÷ / 50 ÷ | `12000,` / `6000,` / `1909,8593` / `38,197186` |
| p.32 | Р | 15.7 В↑ / 4.5 − / 15.7 ÷ / F cos⁻¹ / 2 × / В↑ / F sin / − / В↑ / 15.7 F x² / × / 2 ÷ | `15,7` / `11,2` / `7,1337579 -01` / `7,764927 -01` / `1,5529854` / `1,5529854` / `9,998414 -01` / `5,53144 -01` / `5,53144 -01` / `246,49` / `136,34446` / `68,17223` |
| p.34 | | 0.4 В↑ F π × 25 × 2.25 × | `70,685831` |
| p.34 | | 50 × 20 × 1250 ÷ | `56,548665` |
| p.34 | | 1.5 F x² ÷ 4 × | `100,53096` |
| p.34 | | 0.33 ВП 4 /-/ × | `3,3175216 -03` |
| p.34 | | 0.28 F x² + F √ | `2,8586276 -01` |
| p.34 | | 0.28 + 1.5 F x² × 1250 × | `1591,489` |
| p.34 | | F 1/x 25 × 2.25 × 50 × | `1,767213` |
| p.34 | | 20 ВП 2 × 0.4 × F π × | `4441,4906` |
| p.36–37 | | 4 В↑ 3 В↑ 2 В↑ 1 → В↑ → F⟳ → F⟳ → ↔ → Cx → 375 | T4 Z3 Y2 X1 → T3 Z2 Y1 X1 → T1 Z3 Y2 X1 → T1 Z1 Y3 X2 → T1 Z1 Y2 X3 → T1 Z1 Y2 X0 → T1 Z1 Y2 X375 |
| p.38 | | (T1 Z1 Y2 X375) F √ | T1 Z1 Y2 X19,364916. X1 = 375 |
| p.38 | | Cx В↑ В↑ В↑ | all `0,` |
| p.39 | | Cx В↑ В↑ В↑ 34 В↑ 12 + | `46,`. X1 = 12 |
| p.40–41 | | 4 В↑ В↑ В↑ 16 × F⟳ 23 × | X64 (T4 Z4 Y4) → F⟳: T64 Z4 Y4 X4 → 23: T4 Z4 Y4 X23 → `92,` |
| p.41 | | 12 В↑ 3 + 7 × 3 ÷ | `15,` `105,` `35,` |
| p.42–43 | | (Y35 X3) В↑ 7 В↑ 3 В↑ 12 + × ↔ ÷ | T0 Z35 Y3 X3 → … → T3 Z7 Y3 X12 → + T3 Z3 Y7 X15 → × T3 Z3 Y3 X105 → ↔ Y105 X3 → ÷ X35 (T3 Z3 Y3). X1 = 3 |
| p.45–48 | Г | (T3 Z3 Y3 X35, X1 3) 14 В↑ 2 F sin × F Bx F⟳ 4 − F Bx ÷ | 14: T3 Z3 Y35 X14 → В↑: T3 Z35 Y14 X14 → 2 → sin: X `3,4899495 -02`, X1 2 → ×: T3 Z3 Y35 X `4,8859293 -01`, X1 0,0348995 → F Bx: T3 Z35 Y0,48859 X0,034899 → F⟳: T0,034899 Z3 Y35 X0,48859293 → 4: T3 Z35 Y0,48859 X4 → −: T3 Z3 Y35 X `-3,5114071`, X1 4 → F Bx: T3 Z35 Y−3,5114071 X4 → ÷: T3 Z3 Y35 X `-8,7785177 -01` |
| p.48–49 | | 6.02 ВП 23 x→П 1 / F x² / П→x 1 | `6,02 23` / `3,62404 47` / `6,02 23` |
| p.50 | | Cx x→П 1 | `0,` (R1 = 0) |
| p.69–70 | | 5 x→П 3, 7 x→П 4, 12 x→П a, then П→x 3/4/a | `5,` `7,` `12,` |
| p.77 | | 14 x→П 0 К x→П 0 П→x 0 П→x d 5 К x→П 0 П→x 0 П→x c | `14,` `14,` `00000013,` `14,` `5,` `5,` `00000012,` `5,` |
| p.78 | | 4 x→П 4, 10 x→П 5, 20 x→П 6, 30 x→П 7, К П→x 4, П→x 4, К П→x 4, П→x 4 | `4,` `10,` `20,` `30,` `10,` `00000005,` `20,` `00000006,` |

### 6.2 Program listings (address, keys, hex)

**Table 5 (p.58), circle area S = πd²/4, d in R2.** Usage p.64: `4 x→П 2 В/О С/П` gives `12,56637`. d=5 gives `19,634953`. d=1.8 gives `2,54469`.

| Addr | Keys | Hex |
|---|---|---|
| 00 | П→x 2 | 62 |
| 01 | F x² | 22 |
| 02 | В↑ | 0E |
| 03 | F π | 20 |
| 04 | × | 12 |
| 05 | 4 | 04 |
| 06 | ÷ | 13 |
| 07 | С/П | 50 |

Entry display (p.60–61): after `П→x 2` the display shows `62 01`. After F x²: `22 62 02`. After В↑: `0E 22 62 03`. Auto: `БП 0 2`, then F ПРГ shows `22 62 02`.

**Table 9 (p.68), indirect jumps; computes (4+2)·3.** Setup: `5 x→П 3, 7 x→П 4, 12 x→П a, В/О, С/П`. Result `18` [M-derived]. Afterwards R3 = `00000004,`, R4 = `00000008,`, Ra = `00000012,` (p.70).

| Addr | Keys | Hex |
|---|---|---|
| 00 | 4 | 04 |
| 01 | В↑ | 0E |
| 02 | К БП 3 | 83 |
| 03 | F √ | 21 |
| 04 | 2 | 02 |
| 05 | + | 10 |
| 06 | К БП 4 | 84 |
| 07 | + | 10 |
| 08 | 3 | 03 |
| 09 | × | 12 |
| 10 | К БП a | 8A |
| 11 | − | 11 |
| 12 | С/П | 50 |

**Table 10 (p.71), y = −9x² + e^{2x}; adds sin x if y ≥ 0, tg x if y < 0. x in R1, switch Р.** Usage p.72–73: `x x→П 1 В/О С/П`. Expected:

| x | Display |
|---|---|
| 1 | `-5,35365 -02` |
| 2 | `19,507444` |
| 3 | `322,56986` |
| 4 | `2836,2007` |

These are hardware digits. IEEE results: −0.05353618, 19.507447, 322.56991, 2836.2012.

| Addr | Keys | Hex |
|---|---|---|
| 00 | 1 | 01 |
| 01 | 9 | 09 |
| 02 | x→П в | 4B |
| 03 | 9 | 09 |
| 04 | П→x 1 | 61 |
| 05 | F x² | 22 |
| 06 | × | 12 |
| 07 | x→П 2 | 42 |
| 08 | П→x 1 | 61 |
| 09 | 2 | 02 |
| 10 | × | 12 |
| 11 | F eˣ | 16 |
| 12 | П→x 2 | 62 |
| 13 | − | 11 |
| 14 | К x<0 в | CB |
| 15 | П→x 1 | 61 |
| 16 | F tg | 1E |
| 17 | + | 10 |
| 18 | С/П | 50 |
| 19 | П→x 1 | 61 |
| 20 | F sin | 1C |
| 21 | + | 10 |
| 22 | С/П | 50 |

**Table 11 (p.74), quadratic ax²+bx+c = 0 with an indirect subroutine (К ПП 7, R7 = 19).** Inputs a→Ra, b→Rb, c→Rc. Usage p.75: `3 x→П a, 2 x→П в, 1 /-/ x→П c, В/О, С/П`. The display then shows x₂ = `-1,`. `П→x 1` shows x₁ = `3,3333333 -01`. A negative discriminant gives ЕГГОГ. The return addresses are 04, then 11 (p.75).

| Addr | Keys | Hex | Addr | Keys | Hex |
|---|---|---|---|---|---|
| 00 | 1 | 01 | 16 | ÷ | 13 |
| 01 | 9 | 09 | 17 | x→П 2 | 42 |
| 02 | x→П 7 | 47 | 18 | С/П | 50 |
| 03 | К ПП 7 | A7 | 19 | П→x a | 6A |
| 04 | + | 10 | 20 | П→x c | 6C |
| 05 | П→x a | 6A | 21 | × | 12 |
| 06 | ÷ | 13 | 22 | 4 | 04 |
| 07 | 2 | 02 | 23 | × | 12 |
| 08 | ÷ | 13 | 24 | П→x в | 6B |
| 09 | x→П 1 | 41 | 25 | F x² | 22 |
| 10 | К ПП 7 | A7 | 26 | ↔ | 14 |
| 11 | ↔ | 14 | 27 | − | 11 |
| 12 | − | 11 | 28 | F √ | 21 |
| 13 | П→x a | 6A | 29 | П→x в | 6B |
| 14 | ÷ | 13 | 30 | /-/ | 0B |
| 15 | 2 | 02 | 31 | В/О | 52 |

**Table 13 (p.81), Σ_{i=1..4}(2·tg(xᵢ/3)+4) using К П→x 3 as a counter. Switch Р.** Usage p.79, p.82: `Cx x→П 5, В/О, 5, С/П` gives `29,644467`.

| Addr | Keys | Hex |
|---|---|---|
| 00 | x→П 3 | 43 |
| 01 | К П→x 3 | D3 |
| 02 | П→x 3 | 63 |
| 03 | F x=0 | 5E |
| 04 | 07 | 07 |
| 05 | П→x 5 | 65 |
| 06 | С/П | 50 |
| 07 | 3 | 03 |
| 08 | ÷ | 13 |
| 09 | F tg | 1E |
| 10 | 2 | 02 |
| 11 | × | 12 |
| 12 | 4 | 04 |
| 13 | + | 10 |
| 14 | П→x 5 | 65 |
| 15 | + | 10 |
| 16 | x→П 5 | 45 |
| 17 | БП | 51 |
| 18 | 01 | 01 |

**Table 14 (p.84), the same sum using F L0. Switch Р.** Usage p.85: `Cx x→П 5, 4, В/О, С/П` gives `29,644467`. Afterwards R0 = `00000001,` (p.82).

| Addr | Keys | Hex |
|---|---|---|
| 00 | x→П 0 | 40 |
| 01 | П→x 0 | 60 |
| 02 | 3 | 03 |
| 03 | ÷ | 13 |
| 04 | F tg | 1E |
| 05 | 2 | 02 |
| 06 | × | 12 |
| 07 | 4 | 04 |
| 08 | + | 10 |
| 09 | П→x 5 | 65 |
| 10 | + | 10 |
| 11 | x→П 5 | 45 |
| 12 | F L0 | 5D |
| 13 | 01 | 01 |
| 14 | С/П | 50 |

**Table 16 (p.87–88), compound interest (§7.1).** Registers: R2 = n, R3 = i (%), R4 = H, R5 = K. Entry points (Table 15, p.87):

| To compute | Keys |
|---|---|
| n | `В/О С/П` |
| i | `БП 12 С/П` |
| H | `БП 29 С/П` |
| K | `БП 38 С/П` |

Example (p.86, p.89): n = 6, i = 7,5, H = 270, then `БП 3 8 С/П` gives **`416,6914`**.

| Addr | Keys | Hex | Addr | Keys | Hex |
|---|---|---|---|---|---|
| 00 | ПП | 53 | 29 | ПП | 53 |
| 01 | 46 | 46 | 30 | 46 | 46 |
| 02 | F ln | 18 | 31 | F xʸ | 24 |
| 03 | x→П 6 | 46 | 32 | F 1/x | 23 |
| 04 | П→x 5 | 65 | 33 | В↑ | 0E |
| 05 | П→x 4 | 64 | 34 | П→x 5 | 65 |
| 06 | ÷ | 13 | 35 | × | 12 |
| 07 | F ln | 18 | 36 | x→П 4 | 44 |
| 08 | П→x 6 | 66 | 37 | С/П | 50 |
| 09 | ÷ | 13 | 38 | ПП | 53 |
| 10 | x→П 2 | 42 | 39 | 46 | 46 |
| 11 | С/П | 50 | 40 | F xʸ | 24 |
| 12 | П→x 5 | 65 | 41 | В↑ | 0E |
| 13 | В↑ | 0E | 42 | П→x 4 | 64 |
| 14 | П→x 4 | 64 | 43 | × | 12 |
| 15 | ÷ | 13 | 44 | x→П 5 | 45 |
| 16 | В↑ | 0E | 45 | С/П | 50 |
| 17 | П→x 2 | 62 | 46 | П→x 3 | 63 |
| 18 | F 1/x | 23 | 47 | 1 | 01 |
| 19 | ↔ | 14 | 48 | 0 | 00 |
| 20 | F xʸ | 24 | 49 | 0 | 00 |
| 21 | 1 | 01 | 50 | ÷ | 13 |
| 22 | − | 11 | 51 | 1 | 01 |
| 23 | 1 | 01 | 52 | + | 10 |
| 24 | 0 | 00 | 53 | В↑ | 0E |
| 25 | 0 | 00 | 54 | П→x 2 | 62 |
| 26 | × | 12 | 55 | ↔ | 14 |
| 27 | x→П 3 | 43 | 56 | В/О | 52 |
| 28 | С/П | 50 | | | |

Addresses 17–20 confirm the xʸ operand order independently: the code computes (K/H)^(1/n) with X = K/H as the base and Y = 1/n as the exponent.

**Table 19 (p.91), S = Σ i or P = Π i for i = 1..n (§7.2).** Address 08 holds `+` (10) for a sum or `×` (12) for a product. Usage (Table 18): `F АВТ В/О`, enter n, `С/П`. **No numeric answer is printed.** The expected values follow from the program: n = 5 gives S = 15 or P = 120 [M-derived].

| Addr | Keys | Hex |
|---|---|---|
| 00 | x→П 2 | 42 |
| 01 | 1 | 01 |
| 02 | − | 11 |
| 03 | x→П 3 | 43 |
| 04 | F x≠0 | 57 |
| 05 | 13 | 13 |
| 06 | В↑ | 0E |
| 07 | П→x 2 | 62 |
| 08 | + or × | 10 / 12 |
| 09 | x→П 2 | 42 |
| 10 | П→x 3 | 63 |
| 11 | БП | 51 |
| 12 | 01 | 01 |
| 13 | П→x 2 | 62 |
| 14 | С/П | 50 |
| 15 | БП | 51 |
| 16 | 00 | 00 |

**Table 20 (p.92), running mean (§7.3).** Usage (Table 17): `В/О`, then `xᵢ С/П` for each value; the display shows the running mean. Check sums with `П→x 2` (Σx) and `П→x 3` (n). No numeric answer is printed. Inputs 2, 4, 9 give 2, 3, 5 [M-derived].

| Addr | Keys | Hex |
|---|---|---|
| 00 | x→П 2 | 42 |
| 01 | 1 | 01 |
| 02 | x→П 3 | 43 |
| 03 | П→x 2 | 62 |
| 04 | С/П | 50 |
| 05 | В↑ | 0E |
| 06 | П→x 2 | 62 |
| 07 | + | 10 |
| 08 | x→П 2 | 42 |
| 09 | П→x 3 | 63 |
| 10 | 1 | 01 |
| 11 | + | 10 |
| 12 | x→П 3 | 43 |
| 13 | В↑ | 0E |
| 14 | П→x 2 | 62 |
| 15 | ↔ | 14 |
| 16 | ÷ | 13 |
| 17 | С/П | 50 |
| 18 | БП | 51 |
| 19 | 05 | 05 |

**Table 22 (p.94), "ballistic" S = v²·sin α / g (as printed: sin α, not sin 2α).** Usage (Table 21, p.93): switch Г, `F АВТ В/О`, `α В↑ v С/П`. No numeric answer is printed. α = 30, v = 10 gives 100·0,5/9,81 = 5,0968399 [M-derived].

| Addr | Keys | Hex |
|---|---|---|
| 00 | F x² | 22 |
| 01 | ↔ | 14 |
| 02 | F sin | 1C |
| 03 | × | 12 |
| 04 | 9 | 09 |
| 05 | . | 0A |
| 06 | 8 | 08 |
| 07 | 1 | 01 |
| 08 | ÷ | 13 |
| 09 | С/П | 50 |
| 10 | БП | 51 |
| 11 | 00 | 00 |

**Fragments (p.64–66, Tables 6–8):**
- `11: БП 51`, `12: 42`
- `14: F x² 22`, `15: F x=0 5E`, `16: 38`, `17: + 10`, `38: 4 04`, `39: − 11`
- `17: ПП 53`, `18: 90`, `19: В↑ 0E`, `89: − 11`, `90: 2 02`, `91: В/О 52`

### 6.3 Appendix: functional test (p.96–100), verbatim

Run it from power-on, in order. Display columns 1–12: sign, 8 mantissa digits, exponent sign, 2 exponent digits. In program mode the display is `c(PC−1) c(PC−2) c(PC−3) PC`.

**Auto-mode block, tests 0–19:**

| # | Switch | Keys | Display |
|---|---|---|---|
| 0 | | (power on) | `0,` |
| 1 | | F π | `3,1415926` |
| 2 | | F ln | `1,1447298` |
| 3 | | F lg | `5,8702985 -02` |
| 4 | | F 10ˣ | `1,1447298` |
| 5 | | F xʸ | `1,` |
| 6 | Г | F sin | `1,7452405 -02` |
| 7 | | F cos | `9,9999996 -01` |
| 8 | | F tg | `1,7455063 -02` |
| 9 | | F tg⁻¹ | `9,9999992 -01` |
| 10 | Р | F cos⁻¹ | `4,4721361 -04` |
| 11 | | F sin⁻¹ | `4,4721363 -04` |
| 12 | ГРД | F sin | `7,0248161 -06` |
| 13 | | F cos⁻¹ | `99,999552` |
| 14 | | Cx | `0,` |
| 15 | | x→П 4 | `0,` |
| 16 | | 1 4 | `14` (printed without comma) |
| 17 | | x→П 0 | `14,` |
| 18 | | В/О | `14,` |
| 19 | | F ПРГ | blank codes, PC `00` |

**Program entry, tests 20–84.** Each row shows the code stored at the address and the display after the keystroke:

| # | Keys | Addr:Code | Display (c1 c2 c3 PC) |
|---|---|---|---|
| 20 | К x→П 0 | 00:B0 | `L0 · · 01` |
| 21 | F L0 | 01:5D | `5Г L0 · 02` |
| 22 | 1 3 | 02:13 | `13 5Г L0 03` |
| 23 | F L1 | 03:5B | `5L 13 5Г 04` |
| 24 | 0 9 | 04:09 | `09 5L 13 05` |
| 25 | 1 | 05:01 | `01 09 5L 06` |
| 26 | 7 | 06:07 | `07 01 09 07` |
| 27 | x→П 3 | 07:43 | `43 07 01 08` |
| 28 | К БП 3 | 08:83 | `83 43 07 09` |
| 29 | П→x d | 09:6D | `6Г 83 43 10` |
| 30 | ÷ | 10:13 | `13 6Г 83 11` |
| 31 | БП | 11:51 | `51 13 6Г 12` |
| 32 | 0 3 | 12:03 | `03 51 13 13` |
| 33 | П→x 0 | 13:60 | `60 03 51 14` |
| 34 | БП | 14:51 | `51 60 03 15` |
| 35 | 0 0 | 15:00 | `00 51 60 16` |
| 36 | × | 16:12 | `12 00 51 17` |
| 37 | П→x 7 | 17:67 | `67 12 00 18` |
| 38 | + | 18:10 | `10 67 12 19` |
| 39 | F L2 | 19:58 | `58 10 67 20` |
| 40 | 2 5 | 20:25 | `25 58 10 21` |
| 41 | F L3 | 21:5A | `5- 25 58 22` |
| 42 | 2 5 | 22:25 | `25 5- 25 23` |
| 43 | БП | 23:51 | `51 25 5- 24` |
| 44 | 2 7 | 24:27 | `27 51 25 25` |
| 45 | БП | 25:51 | `51 27 51 26` |
| 46 | 2 1 | 26:21 | `21 51 27 27` |
| 47 | К x→П 4 | 27:B4 | `L4 21 51 28` |
| 48 | F x<0 | 28:5C | `5С L4 21 29` |
| 49 | 3 1 | 29:31 | `31 5С L4 30` |
| 50 | К НОП | 30:54 | `54 31 5С 31` |
| 51 | F x=0 | 31:5E | `5E 54 31 32` |
| 52 | 3 5 | 32:35 | `35 5E 54 33` |
| 53 | БП | 33:51 | `51 35 5E 34` |
| 54 | 3 9 | 34:39 | `39 51 35 35` |
| 55 | ПП | 35:53 | `53 39 51 36` |
| 56 | 5 4 | 36:54 | `54 53 39 37` |
| 57 | F x≥0 | 37:59 | `59 54 53 38` |
| 58 | 3 3 | 38:33 | `33 59 54 39` |
| 59 | П→x 9 | 39:69 | `69 33 59 40` |
| 60 | − | 40:11 | `11 69 33 41` |
| 61 | F x≠0 | 41:57 | `57 11 69 42` |
| 62 | 6 0 | 42:60 | `60 57 11 43` |
| 63 | 4 | 43:04 | `04 60 57 44` |
| 64 | 7 | 44:07 | `07 04 60 45` |
| 65 | x→П 6 | 45:46 | `46 07 04 46` |
| 66 | ↔ | 46:14 | `14 46 07 47` |
| 67 | К x≥0 6 | 47:96 | `96 14 46 48` |
| 68 | К x=0 6 | 48:E6 | `E6 96 14 49` |
| 69 | К x≠0 6 | 49:76 | `76 E6 96 50` |
| 70 | К x<0 6 | 50:C6 | `С6 76 E6 51` |
| 71 | F x² | 51:22 | `22 С6 76 52` |
| 72 | БП | 52:51 | `51 22 С6 53` |
| 73 | 5 7 | 53:57 | `57 51 22 54` |
| 74 | F √ | 54:21 | `21 57 51 55` |
| 75 | F 1/x | 55:23 | `23 21 57 56` |
| 76 | В/О | 56:52 | `52 23 21 57` |
| 77 | 6 | 57:06 | `06 52 23 58` |
| 78 | 2 | 58:02 | `02 06 52 59` |
| 79 | x→П в | 59:4B | `4L 02 06 60` |
| 80 | К ПП в | 60:AB | `-L 4L 02 61` |
| 81 | С/П | 61:50 | `50 -L 4L 62` |
| 82 | F Bx | 62:**0F** | `0  50 -L 63` |
| 83 | F eˣ | 63:16 | `16 0  50 64` |
| 84 | В/О | 64:52 | `52 16 0  65` |

**Run and check, tests 85–102:**

| # | Keys | Display |
|---|---|---|
| 85 | F АВТ | `14,` |
| 86 | В/О | `14,` |
| 87 | С/П (≤ 40 s) | `6,187848 -05` |
| 88 | F⟳ | `62,` |
| 89 | F⟳ | `93,902651` |
| 90 | F⟳ | `47,` |
| 91 | П→x 1 | `10,428571` |
| 92 | П→x 2 | `-99999999,` |
| 93 | П→x 3 | `00000001,` |
| 94 | П→x 4 | `00000001,` |
| 95 | П→x 5 | `6,` |
| 96 | П→x 8 | `0,` |
| 97 | П→x a | `0,` |
| 98 | П→x d | `14,` |
| 99 | /-/ | `-14,` |
| 100 | F √ | `ЕГГОГ` (shows `EГГ0Г`) |
| 101 | Cx | `0,` |
| 102 | ВП | `1,` with exponent `00` |

**Trace of the run (test 87) [M-derived].** This is my execution trace using the semantics in §2–§3. It reproduces every printed value in tests 87–98. Start state: X = 14, Y = Z = T = 0, R0 = 14, R4 = 0, all other registers 0.

1. **Addr 00–01, 13–14 (loop).** 00 `К x→П 0` pre-decrements R0, then stores X in R[R0]. 01 `F L0` decrements R0 again and jumps to 13. 13 `П→x 0` lifts and recalls R0. 14 `БП 00` repeats. The stores are:

   | R0 after decrement | Register written | Value |
   |---|---|---|
   | 13 | Rd | 14 |
   | 11 | Rb | 12 |
   | 9 | R9 | 10 |
   | 7 | R7 | 8 |
   | 5 | R5 | 6 |
   | 3 | R3 | 4 |
   | 1 | R1 | 2 |

   On the last pass L0 finds 1−1 = 0 and falls through to 03. The stack is then X2 Y4 Z6 T8.
2. **03 `F L1`.** R1 2→1, jump to 09.
3. **09 `П→x d`** recalls 14, then **10 `÷`** gives 2/14 = 0,14285714. Stack Y4 Z6 T6, X1 = 14.
4. **11 `БП 03`, 03 `F L1`.** 1→0, so it falls through. R1 keeps 1.
5. **05–06 `1 7`** lifts and enters 17. **07** R3 = 17.
6. **08 `К БП 3`.** R3 becomes 16, jump to 16.
7. **16 `×`** gives 2,4285713. **17 `П→x 7`** recalls 8. **18 `+`** gives 10,428571. Stack Y4 Z6 T6.
8. **19 `F L2`.** R2 = 0 becomes −99999999, which is ≠ 0, so jump to 25.
9. **25 `БП 21`, 21 `F L3` loop.** R3 counts 16 → 1, then falls through. R3 = 1.
10. **23 `БП 27`.** 27 `К x→П 4`: R4 0→1, R1 = 10,428571.
11. **28 `F x<0`** is false, jump to 31. **31 `F x=0`** is false, jump to 35.
12. **35 `ПП 54`:** √ gives 3,2293…, 1/x gives 0,30966…, **56 `В/О`** returns to 37.
13. **37 `F x≥0`** is true, go to 39. **39 `П→x 9`** recalls 10. **40 `−`** gives −9,6903… with X1 = 10.
14. **41 `F x≠0`** is true. **43–44 `4 7`** lifts and enters 47. **45** R6 = 47. **46 `↔`** gives X −9,69 and Y 47.
15. **47 `К x≥0 6`** fails: R6 = 48, jump to 48. **48 `К x=0 6`** fails: R6 = 49, jump to 49.
16. **49 `К x≠0 6`** holds and **50 `К x<0 6`** holds, so execution goes on to 51.
17. **51 `F x²`** gives 93,90265. Now X1 = −9,6903. Stack Y47 Z4 T6.
18. **52 `БП 57`.** **57–58 `6 2`** lifts: X62 Y93,9 Z47 T4. **59** Rb = 62.
19. **60 `К ПП в`** pushes 61 and jumps to 62 (Rb is unchanged).
20. **62 `F Bx`** lifts and recalls X1: X −9,6903, Y62, Z93,9, T47.
21. **63 `F eˣ`** gives 6,187848·10⁻⁵. **64 `В/О`** returns to 61. **61 `С/П`** stops.
22. The three F⟳ presses then give 62, 93,902651 and 47.

Tests 1–13 and 87–89 check the microcode's own precision. Expect differences from IEEE in the last digit or two. For example, test 10 corresponds to arccos(0,9999999), not arccos(0,99999992).

---

## 7. Mode keys and non-programmable keys [M]
- F ПРГ and F АВТ switch modes.
- F CF cancels F.
- ШГ→ and ШГ← step the PC in programming mode.

None of these has a code (p.15, p.17–18, p.50–51). The manual mentions no ШГ action in auto mode.

---

## 8. Inferred, not stated in the manual

| Item | Inference | Basis |
|---|---|---|
| F⟳ opcode | **25** | B3-34 family convention. Missing from both manual Table 4 and book61 Table 1.3. Semantics are [M] (§2.3) |
| Integer part only in indirect modification | Indirect ops (К x→П, К П→x, and by extension К БП / К ПП / К cond) first truncate the register's fractional part. R0–R3 are then decremented by 1, R4–R6 incremented by 1, R7–Rd only truncated. Example: `421,756 x→П 9 К П→x 9 П→x 9` gives `00000421` | book61 PDF p.22–23 (§1.4, describes the Б3-34). The manual only shows integer examples and the leading-zero display (p.70, p.77–78) |
| Integer part used as address/register | Values ≥ 14 (registers) or ≥ 98 (addresses) are not described | B3-34 family. Behaviour unspecified |
| F π and П→x right after В↑ | book61 Fig. 1.4в shows "Fπ or ИПN" always lifting. Every manual example (p.34, p.58, Tables 16, 19, 20) gives the same result whether or not they lift after В↑, so it cannot be confirmed | book61 PDF p.19. Ambiguous in the manual |
| Digit entry after x→П, ↔, F Bx | Lifts (x→П ends entry) | B3-34 family. No manual example separates the two cases |
| ↔ and X1 | book61 Fig. 1.4г shows X1 unchanged. Some B3-34 references say ↔ copies X to X1. The manual is silent | Unresolved |
| В↑, /-/ and X1 | X1 unchanged | Manual silent |
| xʸ and Y | **Manual (p.27 §5.6.1):** a two-operand op that drops the stack. Community reports on Б3-34/МК-61 hardware say xʸ keeps Y. Every manual program here works under either model | Potential conflict. Needs ROM/hardware check |
| PC after 97 | Wraps to 00 ("выполняется все 98 шагов", p.59, implies running through all of memory) | B3-34 family |
| Return-stack overflow / underflow | Not described. The stack depth is 5 [M] | — |
| В/О in auto mode and the return stack | Manual: sets PC = 00 only. Whether it also clears the return stack is not stated | — |
| Error while a program runs | Execution stops and ЕГГОГ is shown ("вычисления останавливаются") | book61 PDF p.22. Manual p.24 only describes manual-mode errors |
| xʸ error domain | x ≤ 0 is an error (Table 1, p.7 says 0 < x). p.24 lists "x = 0" with an unclear y-condition | Partly [M] |
| Undocumented codes 26–3F etc. | Unknown | — |

---

## 9. Surprises and differences from the generic B3-34 picture

1. **Angle switch has 3 positions, Г/Р/ГРД.** The МК-56 has **grads**; the Б3-34 has only Р–Г (book61 p.15). The functional test needs ГРД (tests 12–13). An emulator needs a third angle mode.
2. **F Bx (0F) and F⟳ (25) are missing from the printed code table.** 0F appears only in the functional test (#82).
3. **Underflow is reported as ЕГГОГ with X set to 0** (p.24). Check this against the ROM before relying on it.
4. **Indirect access rewrites even R7–Rd into the leading-zero integer format** (Ra = `00000012,` after К БП a, p.70).
5. **F Ln exit leaves Rn = 1, not 0** (p.82; test #93). **F Ln on 0 gives −99999999** (test #92).
6. **The functional test also checks stack and X1 behaviour.** Tests 87–90 only pass if F Bx lifts the stack and digits / x→П / БП / К ПП leave X1 alone (see trace).
7. **Printed results follow 8-digit (truncating) decimal arithmetic with π = 3,1415926** (e.g. 70,685831 on p.34; 1,7857142 −03 on p.29). A binary-double emulator will not match the printed digits exactly.
8. The keyboard has **no К legends except НОП, a, в, c, d**. The other К operations are indirect prefixes only.

---

## 10. Additions from Дьяконов's handbook

The program audit ([programs/AUDIT.md](../programs/AUDIT.md)) ran 45 programs
from the handbook. Their worked examples settle these points:

| Behaviour | Evidence |
|---|---|
| F π also copies the old X to X1 | stack table, book p.23 |
| A digit after x→П lifts the stack | stack table, book p.23 |
| Conditionals jump when the condition fails | book p.24 |
| An indirect register number outside 0–13 is not an error. Programs use `Пn КИПn ИПn` to take the integer part of any number and discard what `КИПn` loads | programs 3.1–3.4, 3.6, 4.15 |
| After ЕГГОГ in a running program, X, Y, Z and T are intact and С/П continues with the next step | programs 5.32 (quartic, quintic), which report complex roots this way |
| С/П in a program ends number entry | program 3.11 |
