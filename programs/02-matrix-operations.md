# Matrix Operations Programs

Programs for determinants and matrix calculations.

## Program 3.8: 2×2 Determinant

**Purpose**: Calculate determinant of 2×2 matrix

```
Δ = |a₁  b₁|
    |a₂  b₂| = a₁b₂ − a₂b₁
```

**Input**:
- a₁ = P8, b₁ = P9
- a₂ = P5, b₂ = P6

**Program**:
```
ИП8 ИП6 × ИП5 ИП9 × − С/П
```

**Test**:
```
|5  4|
|1.5 3| = 9
```

---

## Program 3.9: 3×3 Determinant

**Purpose**: Calculate determinant of 3×3 matrix

```
|a₁  b₁  c₁|
|a₂  b₂  c₂| = c₁(a₂b₃−a₃b₂) + c₂(a₃b₁−a₁b₃) + c₃(a₁b₂−a₂b₁)
|a₃  b₃  c₃|
```

**Input**:
- a₁=P7, b₁=P8, c₁=P9
- a₂=P4, b₂=P5, c₂=P6
- a₃=P1, b₃=P2, c₃=P3

**Program**:
```
ИП4 ИП2 × ИП1 ИП5 × −     ИП9 × ИП1
ИП8 × ИП7 ИП2 × −         ИП6 × +  ИП7
ИП5 × ИП4 ИП8 × −         ИП3 × +  С/П
```

**Test**:
```
|2  5  −3|
|1  4  −1| = 10
|1  3   2|
```

Calculation time: ~10 seconds

---

## Program 3.10: 4×4 Determinant

**Purpose**: Calculate determinant of 4×4 matrix by expansion

**Input**: Matrix elements in registers PA-PД (rows), columns in P0-P9

**Program**:
```
Сx  П0   ПП   54   ИП7   ПА   XY   П7   ИПВ  ИП4
HB  XY   П4   ИПС  ИП1   ПС   XY   П1   ПП   54
×   −    ИП9  ×    +     ИП7  ИП7  ИПВ  ИП4  
ИП6 ×    +    ИП7  ИП5   ×    −    ИП4  ИП8  ×
−        ИП9  ×    +     П3   ИП1  ИП8  ×    −
ИП3 ×    +    С/П  ×     ИП0  +    П0   В/0
```

**Test**:
```
|6  3  0  3|
|4  4  2  1|
|0  4  4  2| = −216
|7  7  8  5|
```

Input: A₁=6, B₁=8, C₁=52, D₁=72
Result: Δ = −216

---

## Program 3.11: Matrix Addition (4×3)

**Purpose**: Add two 4×3 matrices

**Input**: First matrix in P0-P11, second matrix entered via C/П

**Program**:
```
7   С/П  ИП7  +   П7  8    С/П  ИП8  +   П8
9   С/П  ИП9  +   П9  4    С/П  ИП4  +   П4
5   С/П  ИП5  +   П5  6    С/П  ИП6  +   П6
1   С/П  ИП1  +   П1  2    С/П  ИП2  +   П2
3   С/П  ИП3  +   П3  0    С/П  ИПА  1   1
С/П ИПВ  +    ПВ  БП  00
```

---

## Program 3.12: Matrix Multiplication (3×4 × 4×2)

**Purpose**: Multiply 3×4 matrix A by 4×2 matrix B

Result: 3×2 matrix C where Cᵢⱼ = Σ aᵢₖbₖⱼ

**Input**:
- Matrix A elements in specified registers
- Matrix B elements entered via prompts

**Program**:
```
ПП  16   ИП3  П9   ИПД  ПВ   ПП   16   ИП3  П6
ИПД ПС   ПП   16   0    С/П  1    С/П  ИП0  ×
ИПД +    ПД   +    ПВ   БП   00
```

**Test**:
```
|2 0 3 1|   |1 3|
|5 1 2 0| × |2 1| = |17  15  19  11  16  5|
|0 0 4 1|   |4 0|   
            |3 5|
```

---

## Program 3.13: 2×2 Matrix Inversion

**Purpose**: Calculate inverse of 2×2 matrix

**Input**:
- a₁₁=P7, a₂₁=P8
- a₁₂=P4, a₂₂=P5

**Inverse matrix replaces original in same registers**

**Program**:
```
ИП4 ИП8 × П2 ИП7 П9  ИП5 × ИП2 −
П2  ИП5 XY + П7 ИП9 ИП2 ÷ П5  ИП4
ИП2 /−/ ÷ П4 ИП8 ИП2 /−/ + П8  С/П
БП  00
```

**Test**:
```
A = |7  8|    A⁻¹ = | 1.6666666  −2.6666666|
    |4  5|          |−1.3333333   2.3333333|
```

---

## Program 3.14: 3×3 Matrix Inversion

**Purpose**: Calculate inverse of 3×3 matrix

**Input**:
- a₁₁=P7, a₁₂=P8, a₁₃=P9
- a₂₁=P4, a₂₂=P5, a₂₃=P6
- a₃₁=P1, a₃₂=P2, a₃₃=P3

**Program**:
```
3   П0   ИП4  ИП7  +    ПД   ИПД  /−/  ПС   ИП5
ИПД ИП8  ×    −    ПА   ИП6  ИПД  ИП9  ×    −
ПВ  ИП1  ИП7  ÷    ПД   ИПД  /−/  П6   ИП2  ИПД
ПД  ИП8  ×    −    П4   ИП3  ИПД  ИП9  ×    −
ИП8 ×    −    П4   ИП3  ИПД  ИП9  ×    −    П5
П3  ИПА  П7   ИПВ  П8   ИПС  П9   FL0  02   С/П
```

**Test**:
```
A = |4 8 0|    A⁻¹ = | 0.08333333  −0.08333333   0.66666666|
    |8 8 8|          | 0.08333333   0.04166667  −0.33333333|
    |2 0 1|          |−0.16666666   0.16666666   0.33333333|
```
