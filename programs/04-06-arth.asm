; Program 4.6: Inverse hyperbolic tangent arth(x) = ln sqrt((x + 1)/(1 − x)), −1 < x < 1
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.64 (book61.pdf page 65)
; Input: x in X.  Output: arth(x) in X.
; FBx recalls x (X1 holds the X operand of the preceding +).
;
; Book example: x = 0,7615942 -> arth(x) = 1,0000001
; @input 0.7615942
; @expect X=1.0000001 tol=1e-5
;
; As printed:
;   00: В↑ 1 ↔ + FBx 1 ↔ − ÷ F√
;   10: Fln С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        1               ; 01  1              01
        SWAP            ; 02  ↔              14
        ADD             ; 03  +              10
        LASTX           ; 04  FBx            0F
        1               ; 05  1              01
        SWAP            ; 06  ↔              14
        SUB             ; 07  −              11
        DIV             ; 08  ÷              13
        SQRT            ; 09  F√             21
        LN              ; 10  Fln            18
        HALT            ; 11  С/П            50
