# Statistics and Sequences Programs

Programs for statistical calculations and numerical sequences.

## Program 4.12: Sum of Integer Sequence

**Purpose**: Calculate S = Σᵢ₌₁ⁿ i = 1 + 2 + 3 + ... + n

**Input**: x = PX (n entered)

**Program**:
```
П0 0 ИП0 + FL0 02 С/П
```

**Test**: n = 10 → S = 55

---

## Program 4.13: Sum of Factorials

**Purpose**: Calculate S(n!) = Σᵢ₌₁ⁿ i!

S = 1! + 1·2! + 1·2·3! + ... + n!

**Input**: n = PX

**Program**:
```
П7  0    П9  П6  1    П8   КИП6  ИП6  ИП8   ×
П8  ИП9  +   П9  ИП6  ИП7  −     Fx=0 06    ИП9
С/П БП   00
```

**Test**: n = 4 → S(n!) = 33 (1! + 2! + 3! + 4! = 1 + 2 + 6 + 24)

---

## Program 4.14: Product of Factorials

**Purpose**: Calculate P(n!) = 1!(1·2)!(1·2·3)!...n!

P(n!) = 1·(1·2)·(1·2·3)·...·(n−1)!n!

**Input**: n = PX

**Program**:
```
П7  0    П6  1    П8   П9   КИП6  ИП6  ИП8   ×
П8  ИП9  ×   П9   ИП6  ИП7  −     Fx=0 06    ИП9
С/П БП   00
```

**Test**: n = 4 → P(n!) = 288 (1! × 2! × 3! × 4! = 1 × 2 × 6 × 24)

---

## Program 4.15: Power Sequence Sum

**Purpose**: Calculate y = Σₖ₌₁ᵐ kⁿ

**Input**: m and n in register X

**Program**:
```
П7  С/П  П9  0   П4   П8   КИП4  ИП4  ИП9   XY
Fxʸ ИП8  +   П8  ИП7  ИП4  −     Fx=0 06    ИП8
С/П БП   00
```

**Test**: m = 5, n = 2 → y = 1² + 2² + 3² + 4² + 5² = 55

---

## Statistical Moments

**Purpose**: Calculate statistical moments M₁, M₂, M₃, M₄

**Definitions**:
- Mean: x̄ = m₁ = (1/N)Σxᵢ
- Variance: D = σ² = (1/N)Σ(xᵢ − x̄)² = M₂
- Standard deviation: σ = √D
- M₂ = m₂ − m₁²
- M₃ = m₃ − 3m₁m₂ + 2m₁³
- M₄ = m₄ − 4m₁m₃ + 6m₁²m₂ − 3m₁⁴

**Skewness**: A = M₃/M₂^(3/2)
**Kurtosis**: E = M₄/M₂² − 3

---

## Program: Mean and Variance

**Purpose**: Calculate mean and variance of N numbers

**Input**: N = P0, then x₁, x₂, ..., xₙ via C/П prompts

**Program Structure**:
```
; Initialize
П→x 0       ; N
П1          ; Store N
0           ; Initialize sums
П2          ; Sum of x
П3          ; Sum of x²

; Loop to enter data
С/П         ; Enter xᵢ
П4          ; Store xᵢ
П→x 2
+           ; Add to sum
П2
П→x 4
x²
П→x 3
+           ; Add to sum of squares
П3
П→x 1
1 −
П1
Fx≠0 XX     ; Loop if more data

; Calculate results
П→x 2       ; Sum
П→x 0       ; N
÷           ; Mean = Sum/N
П5          ; Store mean
П→x 3       ; Sum of x²
П→x 0
÷           ; Mean of x²
П→x 5
x²
−           ; Variance = E[x²] - (E[x])²
С/П
```

---

## Program: Linear Regression

**Purpose**: Calculate y = ax + b from data points

**Input**: (x₁,y₁), (x₂,y₂), ..., (xₙ,yₙ)

**Output**: Slope a, intercept b

**Formulas**:
- a = (NΣxy − ΣxΣy) / (NΣx² − (Σx)²)
- b = (Σy − aΣx) / N

---

## Program: Correlation Coefficient

**Purpose**: Calculate Pearson correlation coefficient r

r = (NΣxy − ΣxΣy) / √[(NΣx² − (Σx)²)(NΣy² − (Σy)²)]

**Interpretation**:
- r = 1: Perfect positive correlation
- r = −1: Perfect negative correlation
- r = 0: No linear correlation

---

## Normal Distribution

**Purpose**: Approximate normal distribution CDF

Φ(x) = (1/√2π) ∫₋∞ˣ e^(−t²/2) dt

**Approximation using series or table lookup**

---

## Monte Carlo Simulation

**Purpose**: Random number generation and simulation

**Note**: B3-34/MK-56 lacks built-in random number generator.
Use pseudo-random sequence: xₙ₊₁ = (axₙ + c) mod m

---

## Usage Notes

1. For large datasets, memory may be limiting factor
2. Use running sums to avoid overflow
3. Check for division by zero in variance calculations
4. Statistical results should be validated with known test cases
