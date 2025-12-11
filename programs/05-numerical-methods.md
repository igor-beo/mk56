# Numerical Methods Programs

Programs for solving equations, linear systems, and integration.

## Program 5.1: System of Linear Equations (n ≤ 4)

**Purpose**: Solve system of n linear equations using optimal elimination

```
a₁₁x₁ + a₁₂x₂ + ... + a₁ₙxₙ = b₁
a₂₁x₁ + a₂₂x₂ + ... + a₂ₙxₙ = b₂
...
aₙ₁x₁ + aₙ₂x₂ + ... + aₙₙxₙ = bₙ
```

**Input**: n = P0, coefficients aᵢⱼ = PX, bᵢ = entered via C/П

**Program**:
```
П4  1    4    П2   ИП0  П1   ИП0  П1   FL1  23   КИП3
С/П БП   19   Сx   КП2  FL1  24   КП2  ИП0  ИП2  
+   П1   П2   ИП3  −    Fx≠0 42   С/П  ПП   84
+   КП2  −    ИП4  ÷    КП1  FL3  49   ИП1  ИП0
+   КП3  ×    КИП3 КП2  FL2  78   БП   12
FL0 86   F,   П0   В/0
```

**Test** (n = 3):
```
| 4     0.24   −0.08| |x₁|   | 8 |
| 0.09  3      −0.15| |x₂| = | 9 |
| 0.04  −0.08  4    | |x₃|   |20 |
```

Solution: x₁ = 1.9091983, x₂ = 3.1949644, x₃ = 5.0448073
Time: ~2 minutes

---

## Program for Quadratic Equation

**Purpose**: Solve ax² + bx + c = 0

**Input**: a, b, c in stack

**Program**:
```
x→П 2    ; Store c
x→П 1    ; Store b  
x→П 0    ; Store a
П→x 1    ; Recall b
x²       ; b²
4        ; Enter 4
П→x 0    ; Recall a
×        ; 4a
П→x 2    ; Recall c
×        ; 4ac
−        ; b² - 4ac
√x       ; √(b² - 4ac)
П→x 1    ; Recall b
/~/      ; -b
+        ; -b + √(b² - 4ac)
2        ; Enter 2
П→x 0    ; Recall a
×        ; 2a
÷        ; (-b + √(b² - 4ac)) / 2a = x₁
С/П      ; Stop, display x₁
```

For x₂, replace + with − before division.

---

## Newton-Raphson Method

**Purpose**: Find root of f(x) = 0 using iteration xₙ₊₁ = xₙ − f(xₙ)/f'(xₙ)

**General Program Structure**:
```
П0       ; Store initial guess x₀
<calculate f(x)>
П1       ; Store f(x)
П→x 0    ; Recall x
<calculate f'(x)>
П2       ; Store f'(x)
П→x 1    ; Recall f(x)
П→x 2    ; Recall f'(x)
÷        ; f(x)/f'(x)
П→x 0    ; Recall x
XY       ; Exchange
−        ; x - f(x)/f'(x)
П0       ; Store new x
С/П      ; Display, press C/П to continue
БП 00    ; Loop
```

---

## Trapezoidal Integration

**Purpose**: Numerical integration using trapezoidal rule

∫[a,b] f(x)dx ≈ h[f(a)/2 + f(x₁) + f(x₂) + ... + f(b)/2]

where h = (b-a)/n

**Input**: a = P1, b = P2, n = P0

**Program Structure**:
```
П→x 2    ; b
П→x 1    ; a
−        ; b - a
П→x 0    ; n
÷        ; h = (b-a)/n
П3       ; Store h
П→x 1    ; a
<calculate f(a)>
2 ÷      ; f(a)/2
П4       ; Initialize sum
; Loop for interior points
П→x 1    ; x
П→x 3    ; h
+        ; x + h
П1       ; Store new x
<calculate f(x)>
П→x 4    ; Recall sum
+        ; Add to sum
П4       ; Store sum
; Check if done, loop back
П→x 2    ; b
<calculate f(b)>
2 ÷      ; f(b)/2
П→x 4    ; Recall sum
+        ; Final sum
П→x 3    ; h
×        ; Result
С/П
```

---

## Bisection Method

**Purpose**: Find root in interval [a,b] where f(a)·f(b) < 0

**Program Structure**:
```
; a = P1, b = P2
; Calculate midpoint
П→x 1
П→x 2
+
2 ÷
П3       ; c = (a+b)/2
; Calculate f(c)
<calculate f(x) at x=c>
П4       ; Store f(c)
; Calculate f(a)
П→x 1
<calculate f(x)>
П→x 4
×        ; f(a)·f(c)
Fx<0 XX  ; If < 0, root in [a,c]
; Root in [c,b]
П→x 3
П1       ; a = c
БП 00
; Root in [a,c]
XX: П→x 3
П2       ; b = c
БП 00
```

---

## Usage Notes

1. For iterative methods, check convergence criteria
2. Store initial values before starting
3. Tolerance typically 10⁻⁶ to 10⁻⁸
4. For MK-56, adapt register operations to algebraic mode
