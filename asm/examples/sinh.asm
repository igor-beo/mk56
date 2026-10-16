; ============================================
; Program: Hyperbolic Sine
; Purpose: Calculate sh(x) = (e^x - 1/e^x) / 2
; Input:   x in X register
; Output:  sh(x) in X register
; Registers Used: none (stack only)
; Source: Program 4.1 from Dyakonov
; ============================================
; Original: Feˣ ↑ F1/x − 2 ÷ С/П
; Test: x = 1 → sh(1) = 1.1752012
; ============================================

;
; @input 1
; @expect X=1.1752012 tol=1e-6

.ORG 0

sinh:
        EXP             ; e^x
        ENTER           ; duplicate: Y=e^x, X=e^x
        INV             ; X = 1/e^x
        SUB             ; X = e^x - 1/e^x
        2               ; push 2
        DIV             ; X = (e^x - 1/e^x) / 2
        HALT            ; stop, result in X

.END
