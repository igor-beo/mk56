; Program 4.5: Inverse hyperbolic cosine arch(x) = ln(x + sqrt(x² − 1)), x > 1
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.64 (book61.pdf page 65)
; Input: x in X.  Output: arch(x) in X.
;
; Book example: arch(2) = 1,3169579
; @input 2
; @expect X=1.3169579 tol=1e-5
;
; As printed:
;   00: В↑ Fx² 1 /-/ + F√ + Fln С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        SQ              ; 01  Fx²            22
        -1              ; 02  1 /-/          01 0B
        ADD             ; 04  +              10
        SQRT            ; 05  F√             21
        ADD             ; 06  +              10
        LN              ; 07  Fln            18
        HALT            ; 08  С/П            50
