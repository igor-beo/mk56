# Scientific and Engineering Programs

Programs for physics, electrical engineering, and applied calculations.

## Program 5.15: Simple Iteration Method

**Purpose**: Find root using xₙ₊₁ = xₙ iteration until machine zero

**Input**: f(x), x₀ = PX

**Program**:
```
ПД ... ... ... ИПД XY ПД − Fx=0 01 ИПД С/П
```

**Test**: For x = 1.171298 converges in ~60 seconds

---

## Program 5.16: Newton's Method (Machine Zero Stop)

**Purpose**: Newton-Raphson with convergence to machine precision

xₙ₊₁ = xₙ − F(xₙ)/F'(xₙ)

**Input**: F(xₙ)/F'(x) in program, xₙ = PД, x₀ = PX

**Program**:
```
... ИПД XY − ПД FBx Fx=0 01 ИПД С/П
```

---

## Program 5.17: Newton's Method with Tolerance

**Purpose**: Newton-Raphson with ε² tolerance check

**Input**: F(xₙ)/F'(xₙ), xₙ = PД, ε² = PC, x₀ = PX

**Program**:
```
ПД ... ... ... ... ... ... ... ... ИПД XY
−   ПД  FBx  Fx²  ИПС  −   Fx<0  01  ИПД  С/П
```

---

## Program 5.32: Fifth Degree Polynomial Equation

**Purpose**: Solve x⁵ + a₄x⁴ + a₃x³ + a₂x² + a₁x + a₀ = 0

**Input**: a₀ ÷ a₄ = P0 ÷ P4, 2(1 + |aₘₐₓ|) = PA = PB

**Output**: x₁ → PX, x₂ → PY and x₃ → PД (after pressing БП 76 С/П)

**Program**:
```
Сx   ПС   XY   FBx  ↑     ИП4   +    П8    ×
ИП3  +    П7   ×    ИПС   Fx=0  63   F,    ИП2  +
П6   ×    ИП1  +    П5    ×     ИП0  +     Fx<0 34
−    ИП9  ПД   ИП5  П0    ИП7   П3   ИП8   П4   /−/   2
ИП9  −    Fx=0 03   ИПС   Fx=0  76   ИПВ   ПА   ПС
+    БП   35   F,   ↑     ИП7   −    БП    25   ИП0   ИП5  ÷
П5   ↑    ИП7  −    ×     Fx²              ИП5
=    F√   +    ÷    FBx   С/П
```

**Test**: x⁴ + 9x³ + 31x² + 59x + 60 = 0
- x₁,₂ = −1 ± j·1.9999999
- x₃ = −3
- x₄ = −4

Calculation time: ~7-10 minutes

---

## Program 7.8: Armored Core Coil Inductance

**Purpose**: Calculate ω for coil on armored core

ω = √(L₀(A + B)/19.74μ)

where A = (h₁ + h₂)(1/(d₁² − d₃²) + 1/(d₂² − d₁²))
      B = 1/(h₂ − h₁) ln((d₃ + d₄)/(d₁ + d₂))

**Input**: d₁, d₂, d₃, d₄, h₁, h₂, μ, L₀ entered via prompts

**Program**:
```
8    П0   0    С/П  КП0   ИП0  1    −    Fx=0  02
С/П  П8   ИП4  Fx²  ИП5   Fx²  −    F1/x  ИП3  ИП2  +
×    ПА   +    ИП8  ×     ИП1  ÷    1     9
÷    7    4    ÷    F√    БП   10
```

**Test**: d₁=1cm, d₂=2cm, d₃=4cm, d₄=5cm, h₁=3cm, h₂=4cm, μ=10, L₀=5·10⁵ nH
Result: ω = 103.26144

---

## Program 7.9: Closed Core Coil Calculation

**Purpose**: Calculate ω for coil with closed magnetic core

ω = √(L₀lₘ(1 + μd₁/alₘ)/4πμFc)

where Fc = cross-section area, lₘ = mean magnetic path

**Input**: Fc, lₘ, a, d₁, μ, L₀ entered sequentially

---

## Transistor Parameter Recalculation

**Purpose**: Convert between transistor h-parameters

**Input**: h₁₁, h₁₂, h₂₁, h₂₂ for one configuration
**Output**: Parameters for another configuration

---

## Rectifier Calculation

**Purpose**: Calculate rectifier circuit parameters

**Input**: Load voltage, current, ripple factor
**Output**: Component values, power ratings

---

## Small-Signal Amplifier Stages

**Purpose**: Calculate gain, input/output impedance

Programs for various transistor configurations:
- Common emitter
- Common base
- Common collector

---

## RC/RL Circuit Time Constants

**Purpose**: Calculate circuit time constants and transient response

τ = RC (for RC circuits)
τ = L/R (for RL circuits)

---

## Usage Notes

1. Engineering programs may require unit conversions
2. Check component values are within reasonable ranges
3. Results should be verified with manual calculations
4. Some programs require multiple runs for complete analysis
