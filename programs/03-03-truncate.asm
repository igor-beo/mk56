; Program 3.3: Truncate x (0 < x < 10^8) to a step eps = 1*10^-n
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.56 (book61.pdf page 57)
; Input: eps in Rd, x in X.  Output: x truncated to a multiple of eps, in X.
;
; Book example: eps = 1*10^-2, x = 123,4567 -> 123,45
; @reg Rd=0.01
; @input 123.4567
; @expect X=123.45
;
; As printed:
;   00: ИПd ÷ Пc КИПc ИПc ИПd × С/П
;
; Each line: instruction ; address, keys, codes

        RCL RD          ; 00  ИПd            6D
        DIV             ; 01  ÷              13
        STO RC          ; 02  Пc             4C
        RCL (RC)        ; 03  КИПc           DC
        RCL RC          ; 04  ИПc            6C
        RCL RD          ; 05  ИПd            6D
        MUL             ; 06  ×              12
        HALT            ; 07  С/П            50
