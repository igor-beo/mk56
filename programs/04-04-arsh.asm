; Program 4.4: Inverse hyperbolic sine arsh(x) = ln(x + sqrt(1 + x²)), any x
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.64 (book61.pdf page 65)
; Input: x in X.  Output: arsh(x) in X.
;
; Book example: arsh(1) = 0,88137355
; @input 1
; @expect X=0.88137355 tol=1e-5
;
; As printed:
;   00: В↑ Fx² 1 + F√ + Fln С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        SQ              ; 01  Fx²            22
        1               ; 02  1              01
        ADD             ; 03  +              10
        SQRT            ; 04  F√             21
        ADD             ; 05  +              10
        LN              ; 06  Fln            18
        HALT            ; 07  С/П            50
