; ============================================
; Program: 2x2 Determinant
; Purpose: Calculate determinant of 2x2 matrix
;          |a  b|
;          |c  d| = ad - bc
; Input:   a=R8, b=R9, c=R5, d=R6
; Output:  determinant in X
; Registers Used: R5, R6, R8, R9
; Source: Program 3.8 from Dyakonov
; ============================================
; Original: ИП8 ИП6 × ИП5 ИП9 × − С/П
; Test: |5 4; 1.5 3| = 5×3 - 4×1.5 = 15 - 6 = 9
; ============================================

.ORG 0

; Pre-load registers before running:
; R8 = a (top-left)
; R9 = b (top-right)  
; R5 = c (bottom-left)
; R6 = d (bottom-right)

det2x2:
        RCL R8          ; a
        RCL R6          ; d
        MUL             ; a*d
        RCL R5          ; c
        RCL R9          ; b
        MUL             ; b*c (now Y=a*d, X=b*c)
        SUB             ; a*d - b*c
        HALT

.END
