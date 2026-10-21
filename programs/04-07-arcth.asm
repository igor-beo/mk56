; Program 4.7: Inverse hyperbolic cotangent arcth(x) = ln sqrt(1 + 2/(x − 1)), x > 1
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.65 (book61.pdf page 66)
; Input: x in X.  Output: arcth(x) in X.
;
; Book example: x = 1,3130352 -> arcth(x) = 1,0000001
; @input 1.3130352
; @expect X=1.0000001 tol=1e-5
;
; As printed:
;   00: В↑ 1 − 2 ↔ ÷ 1 + F√ Fln
;   10: С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        1               ; 01  1              01
        SUB             ; 02  −              11
        2               ; 03  2              02
        SWAP            ; 04  ↔              14
        DIV             ; 05  ÷              13
        1               ; 06  1              01
        ADD             ; 07  +              10
        SQRT            ; 08  F√             21
        LN              ; 09  Fln            18
        HALT            ; 10  С/П            50
