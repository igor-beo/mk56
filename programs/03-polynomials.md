# Polynomial Evaluation Programs

Programs for polynomial calculations using Horner's scheme.

## Program 4.10: Real Polynomial (Horner's Method)

**Purpose**: Evaluate polynomial of degree n ≤ 11

P(x) = a₀ + a₁x + a₂x² + ... + aₙxⁿ = (...(aₙx + aₙ₋₁)x + ... + a₁)x + a₀

**Input**:
- a₁ ÷ aₙ = P1 ÷ Pn
- a₀ = PС
- x = PX

**Program**:
```
ПД  ..  ...  П0  ИПn  ↑    XY  ИПД  ×   КИП0
06  XY  ИПС  +   С/П  БП   00
```

**Test**: P(x) = 0 + 1x + 2x³ + 3x⁴ + 4x⁴ (n = 4)
- P(1) = 10
- P(2) = 98

---

## Program 4.11: Complex Polynomial

**Purpose**: Evaluate polynomial of complex variable Z = a + jb

P(Z) = c + jd where c → PX, d → PY

**Input**:
- Coefficients a₀ = P0, a₁ = P1, ..., a₉ = P9, a₁₀ = PA
- a = PY, b = PX

**Result**: P(Z) = c + jd

**Program**:
```
ПС  XY    ПВ   ИПА  ×    ИП9  +      ПП   42    ИП7  ПП
42  ИП5   ПП   42   ИП8  ПП   42     ИП6  ПП    42   ИП4
ПП  42    ИП2  ПП   42   ИП0  +      XY   ИПВ   ×    +
ПД  XY    ИПС  ×    −    XY   ИП3   ПП    42    ИП1
ПП  42    ИПД  +    С/П  ×    ИПВ   ПП    54    ИПС
ИПС ×     −    XY   ИПС  ИПВ  ×     2     ×     XY
В/0
```

**Test**: P(Z) = 1 + Z + 2Z² + ... + 8Z⁸ (a₀ = a₁₀ = 0)
- For Z = 1 + j·1: P(Z) = 144 − j·113

Calculation time: ~70 seconds

---

## Program 4.18: Hermite Polynomial Coefficients

**Purpose**: Calculate coefficients of Hermite polynomial Hₙ(x)

**Input**: n = PX

**Program**:
```
П2  1   П3  П8  +  П4  2   П5  ИП8  С/П
ИП4 1   −   П9  1  −   П4  ИП9  ×   ИП8
×   ИП5 /−/ ÷  П8 ИП5 2   +   П5   БП
08
```

**Test**: n = 5 → P₅(x) = 7.875x⁵ − 6.75x³ + 1.875x

---

## Program 4.19: Chebyshev Polynomial Coefficients

**Purpose**: Calculate coefficients of Chebyshev polynomial Tₙ(x)

Formula: Tₙ(x) = (n/2) Σ (-1)ᵐ [(n−m−1)!/m!(n−2m)!] (2x)ⁿ⁻²ᵐ

**Input**: n = PX

**Program**:
```
П2  2   П4   П8   −    П3   ИП4  2    ×    П4
ИП3 1   П5   −    П3   Fx=0 06   ИП4  С/П  /−/
÷   П4  ИП8  1    П5   +    ИП8  −    ИП6  ×
×   П5  ИП5  1    −    П6   Fx=0 40   ИП4  БП
22
```

**Test**: n = 8 → T₈(x) = 128x⁸ − 256x⁶ + 160x⁴ − 32x² + 1

---

## Program 4.20: Laguerre Polynomial

**Purpose**: Evaluate Laguerre polynomial Lₙ(x) using recurrence

Lₙ(x) = (eˣ/n!) · dⁿ(xⁿe⁻ˣ)/dxⁿ

Recurrence: L₀(x) = 1, L₁(x) = 1 − x
Lᵢ₊₁(x) = [(2i + 1 − x)Lᵢ(x) − iLᵢ₋₁(x)] / (i + 1)

**Input**: n = P0, x = PX

**Program**: (using recurrence formula)

**Test**: L₅(2) = −0.46666667

---

## Usage Notes

1. Horner's method is numerically stable
2. For high-degree polynomials, watch for overflow
3. Complex polynomials require more registers
4. Coefficients should be pre-stored before execution
