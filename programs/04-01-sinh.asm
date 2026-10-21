; Program 4.1: Hyperbolic sine sh(x) = (eˣ − 1/eˣ)/2
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.64 (book61.pdf page 65)
; Input: x in X.  Output: sh(x) in X.
;
; Book example: sh(1) = 1,1752012
; @input 1
; @expect X=1.1752012 tol=1e-5
;
; As printed:
;   00: Feˣ В↑ F1/x − 2 ÷ С/П
;
; Each line: instruction ; address, keys, codes

        EXP             ; 00  Feˣ            16
        ENTER           ; 01  В↑             0E
        INV             ; 02  F1/x           23
        SUB             ; 03  −              11
        2               ; 04  2              02
        DIV             ; 05  ÷              13
        HALT            ; 06  С/П            50
