; Program 6.32: Probability integral Φ(y) for y > 4 by the asymptotic expansion (6.19):
;   Φ(y) = 1 − (exp(−y²/2)/y)·sqrt(2/π)·(1 − 1/y² + 1·3/y⁴ − ...)  (three terms used)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.167-168 (book61.pdf pages 168-169)
; Input: y in X.  Output: Φ(y) in X.
; Step 05 is printed as a small bold "+"; it is ÷ (−y²/2 is needed for Feˣ, and
; only ÷ reproduces the book's example).
;
; Book example: Φ(4) = 0,9999365 (10 s)
; @input 4
; @expect X=0.9999365
;
; As printed:
;   00: П9 Fx² П8 2 /-/ ÷ Feˣ 2 Fπ ÷
;   10: F√ × ИП9 ÷ П9 3 ИП8 ÷ 1 ↔
;   20: − ИП8 ÷ 1 − ИП9 × 1 + С/П
;   30: БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        SQ              ; 01  Fx²            22
        STO R8          ; 02  П8             48
        -2              ; 03  2 /-/          02 0B
        DIV             ; 05  ÷              13
        EXP             ; 06  Feˣ            16
        2               ; 07  2              02
        PI              ; 08  Fπ             20
        DIV             ; 09  ÷              13
        SQRT            ; 10  F√             21
        MUL             ; 11  ×              12
        RCL R9          ; 12  ИП9            69
        DIV             ; 13  ÷              13
        STO R9          ; 14  П9             49
        3               ; 15  3              03
        RCL R8          ; 16  ИП8            68
        DIV             ; 17  ÷              13
        1               ; 18  1              01
        SWAP            ; 19  ↔              14
        SUB             ; 20  −              11
        RCL R8          ; 21  ИП8            68
        DIV             ; 22  ÷              13
        1               ; 23  1              01
        SUB             ; 24  −              11
        RCL R9          ; 25  ИП9            69
        MUL             ; 26  ×              12
        1               ; 27  1              01
        ADD             ; 28  +              10
        HALT            ; 29  С/П            50
        JMP L00         ; 30  БП 00          51 00
