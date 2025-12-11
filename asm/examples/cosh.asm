; ============================================
; Program: Hyperbolic Cosine
; Purpose: Calculate ch(x) = (e^x + 1/e^x) / 2
; Input:   x in X register
; Output:  ch(x) in X register
; Registers Used: none (stack only)
; Source: Program 4.2 from Dyakonov
; ============================================
; Original: Feˣ ↑ F1/x + 2 ÷ С/П
; Test: x = 1 → ch(1) = 1.5430806
; ============================================

.ORG 0

cosh:
        EXP             ; e^x
        ENTER           ; duplicate: Y=e^x, X=e^x
        INV             ; X = 1/e^x
        ADD             ; X = e^x + 1/e^x
        2               ; push 2
        DIV             ; X = (e^x + 1/e^x) / 2
        HALT            ; stop, result in X

.END
