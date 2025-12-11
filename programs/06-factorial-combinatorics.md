# Factorial and Combinatorics Programs

Programs for factorial, permutations, and combinations.

## Program 3.15: Factorial (n ≥ 1)

**Purpose**: Calculate n! = 1·2·3·...·n

Excludes known value 0! = 1 (n = PX with n ≥ 1)

**Program**:
```
П0 1 ИП0 × FL0 02 С/П
```

**Test**: 10! = 3628800 (calculation time: ~10 seconds)

---

## Program 3.16: Factorial (any n ≥ 0)

**Purpose**: Calculate n! for any n including 0

**Input**: n = PX

**Program**:
```
П0 Fx≠0 11 1 ИП0 × FL0 04 С/П БП
00 1 БП 08
```

**Test Values**:
- 0! = 1
- 1! = 1  
- 3! = 6
- 10! = 3628800
- 20! = 2.432902·10¹⁸

---

## Program 3.17: Factorial (Stirling Approximation)

**Purpose**: Calculate n! for large n (n > 10) using Stirling's formula

n! ≈ nⁿ√(2πn) exp[−n + 1/(12n)(1 − 1/(30n))]

**Input**: n = PX (maximum n = 56)

**Program**:
```
П9 ↑ Fxʸ 1 ИП9 3 0 ×
F1/x − ИП9 − Feˣ × 2
Fπ × ИП9 × F√ × С/П БП 00
```

**Test**: 56! ≈ 7.1099859·10⁷⁴

**Accuracy**: First 5 digits are correct for n > 10

---

## Combinations C(n,k)

**Purpose**: Calculate C(n,k) = n!/(k!(n−k)!)

**Input**: n = P0, k = P1

**Program Structure**:
```
; Calculate n!
П→x 0
<factorial subroutine>
П2       ; Store n!

; Calculate k!
П→x 1
<factorial subroutine>
П3       ; Store k!

; Calculate (n-k)!
П→x 0
П→x 1
−
<factorial subroutine>
П4       ; Store (n-k)!

; Calculate C(n,k)
П→x 2    ; n!
П→x 3    ; k!
÷
П→x 4    ; (n-k)!
÷
С/П
```

**Test**: C(9,3) = 9!/(3!·6!) = 84

---

## Permutations P(n,k)

**Purpose**: Calculate P(n,k) = n!/(n−k)!

**Input**: n = P0, k = P1

**Program Structure**:
```
; Calculate n!
П→x 0
<factorial subroutine>
П2       ; Store n!

; Calculate (n-k)!
П→x 0
П→x 1
−
<factorial subroutine>
П3       ; Store (n-k)!

; Calculate P(n,k)
П→x 2    ; n!
П→x 3    ; (n-k)!
÷
С/П
```

**Test**: P(5,3) = 5!/2! = 60

---

## Efficient Combinations (without full factorials)

**Purpose**: Calculate C(n,k) more efficiently

C(n,k) = [n·(n−1)·...·(n−k+1)] / [k·(k−1)·...·1]

**Program**:
```
; n = P0, k = P1
П→x 0
П2       ; Initialize numerator product with n
П→x 1
П3       ; Counter = k

; Loop: multiply numerator
П→x 0
1 −
П0       ; n = n - 1
П→x 2
П→x 0
×
П2       ; product = product × n

; Divide by counter
П→x 2
П→x 3
÷
П2

; Decrement counter
П→x 3
1 −
П3
Fx≠0 XX  ; If counter ≠ 0, loop

П→x 2
С/П
```

---

## Double Factorial

**Purpose**: Calculate n!! = n·(n−2)·(n−4)·...

For odd n: n!! = n·(n−2)·...·3·1
For even n: n!! = n·(n−2)·...·4·2

**Program**:
```
П0       ; Store n
1        ; Initialize result
П1

; Loop
П→x 0
П→x 1
×
П1       ; result = result × n
П→x 0
2 −
П0       ; n = n - 2
Fx>0 XX  ; If n > 0, loop

П→x 1
С/П
```

**Test**: 
- 7!! = 7·5·3·1 = 105
- 8!! = 8·6·4·2 = 384

---

## Usage Notes

1. Factorial grows very fast - 13! already exceeds 10⁹
2. For large n, use Stirling approximation
3. For combinations, efficient method avoids overflow
4. All programs use B3-34 notation - adapt for MK-56
