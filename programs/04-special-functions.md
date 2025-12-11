# Special Functions Programs

Programs for hyperbolic, trigonometric, and other special functions.

## Program 4.1: Hyperbolic Sine

**Purpose**: Calculate sh(x) = (eˣ − 1/eˣ)/2

**Input**: x = PX

**Program**:
```
Feˣ ↑ F1/x − 2 ÷ С/П
```

**Test**: sh(1) = 1.1752012

---

## Program 4.2: Hyperbolic Cosine

**Purpose**: Calculate ch(x) = (eˣ + 1/eˣ)/2

**Input**: x = PX

**Program**:
```
Feˣ ↑ F1/x + 2 ÷ С/П
```

**Test**: ch(1) = 1.5430806

---

## Program 4.3: Hyperbolic Tangent

**Purpose**: Calculate th(x) = sh(x)/√(1 + sh²x)

**Input**: x = PX

**Program**:
```
Feˣ ↑ F1/x − 2 ÷ ↑ Fx² 1 +
F√ ÷ С/П
```

**Test**: th(1) = 0.76159417

For cth(x) = 1/th(x): add F1/x before С/П

---

## Program 4.4: Inverse Hyperbolic Sine

**Purpose**: Calculate arsh(x) = ln(x + √(1 + x²))

**Input**: x = PX (valid for −∞ < x < +∞)

**Program**:
```
↑ Fx² 1 + F√ + F ln С/П
```

**Test**: arsh(1) = 0.88137355

---

## Program 4.5: Inverse Hyperbolic Cosine

**Purpose**: Calculate arch(x) = ln(x + √(x² − 1))

**Input**: x = PX (valid for x > 1)

**Program**:
```
↑ Fx² 1 /−/ + F√ + F ln С/П
```

**Test**: arch(2) = 1.3169579

---

## Program 4.6: Inverse Hyperbolic Tangent

**Purpose**: Calculate arth(x) = ln√((x + 1)/(1 − x))

**Input**: x = PX (valid for −1 < x < +1)

**Program**:
```
↑ 1 XY + FBx 1 XY − + F√
F ln С/П
```

**Test**: arth(0.7615942) = 1.0000001

---

## Program 4.7: Inverse Hyperbolic Cotangent

**Purpose**: Calculate arcth(x) = ln√(1 + 2/(x − 1))

**Input**: x = PX (valid for x > 1)

**Program**:
```
↑ 1 − 2 XY ÷ 1 + F√ F ln
С/П
```

**Test**: arcth(1.3130352) = 1.0000001

---

## Program 4.8: Continued Fractions

**Purpose**: Evaluate continued fraction

f = a₀ + b₁/(a₁ + b₂/(a₂ + b₃/(a₃ + ...)))

**Input**: aₘ, bₘ, aₘ₋₁, bₘ₋₁, ..., a₁, b₁, a₀ sequentially

**Program**:
```
↑ С/П XY ÷ ↑ С/П + БП 00
```

**Test**: f = [5; 8/4, 2/7, 3/5] = 6.8785432

---

## Program 4.9: Fractional-Rational Function

**Purpose**: Evaluate f(x) = (15 − 21x² + x⁴)/(15 − 6x²)

Written as continued fraction: f(x) = [1; −x²/1, −x²/3, −x²/5]

**Input**: x = PX

**Program**:
```
П9 ИП9 /−/ × П8 5 ÷ 3 + ИП8
XY ÷ 1 + ИП8 XY ÷ 1 + С/П
БП 00
```

**Test**: 
- f(0) = 1
- f(1) = −0.5555554
- f(2) = 5.8888889

---

## Sinc Function

**Purpose**: Calculate y = sin(πnft)/(πnft)

**Input**: n = P8, f = P9, t = PX

**Program** (with t = 0 handling):
```
Fx=0 06 1 С/П Fπ ИП8 ИП9 × × ×
Fsin FBx ÷ С/П
```

Alternative with loop:
```
Fx=0 04 1 С/П БП 00 Fπ ИП8 ИП9 ×
× Fsin FBx ÷ БП 03
```

**Test**: n = 2, f = 1000, t = 1.2·10⁻⁴ → y = 9.0790883·10⁻¹

---

## Usage Notes

1. All programs use radians for angles
2. Check domain restrictions before use
3. For MK-56, translate RPN notation to algebraic
4. Hyperbolic functions may need range limiting for large x
