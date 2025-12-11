; ============================================
; Program: Inverse Hyperbolic Sine
; Purpose: Calculate arsh(x) = ln(x + sqrt(1 + x²))
; Input:   x in X register
; Output:  arsh(x) in X register
; Registers Used: none (stack only)
; Source: Program 4.4 from Dyakonov
; ============================================
; Original: ↑ Fx² 1 + F√ + F ln С/П
; Test: arsh(1) = 0.88137355
; ============================================

.ORG 0

arsinh:
        ENTER           ; duplicate x: Y=x, X=x
        SQ              ; X = x²
        1               ; push 1
        ADD             ; X = 1 + x²
        SQRT            ; X = sqrt(1 + x²)
        ADD             ; X = x + sqrt(1 + x²)
        LN              ; X = ln(x + sqrt(1 + x²))
        HALT

.END
