; Program 4.9: Rational function f(x) = (15 − 21x² + x⁴)/(15 − 6x²)
;   = [1; −x²/1; −x²/3; −x²/5]
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.65 (book61.pdf page 66)
; Input: x in X.  Output: f(x) in X.  С/П again with a new x.
;
; Book examples: f(0) = 1, f(1) = −0,5555554, f(2) = 5,8888889
; (f(1) = −5/9 exactly; the printed last digit comes from 8-digit arithmetic)
; @input 0
; @expect X=1
; @input 1
; @expect X=-0.5555554 tol=1e-6
; @input 2
; @expect X=5.8888889
;
; As printed:
;   00: П9 ИП9 /-/ × П8 5 ÷ 3 + ИП8
;   10: ↔ ÷ 1 + ИП8 ↔ ÷ 1 + С/П
;   20: БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        RCL R9          ; 01  ИП9            69
        CHS             ; 02  /-/            0B
        MUL             ; 03  ×              12
        STO R8          ; 04  П8             48
        5               ; 05  5              05
        DIV             ; 06  ÷              13
        3               ; 07  3              03
        ADD             ; 08  +              10
        RCL R8          ; 09  ИП8            68
        SWAP            ; 10  ↔              14
        DIV             ; 11  ÷              13
        1               ; 12  1              01
        ADD             ; 13  +              10
        RCL R8          ; 14  ИП8            68
        SWAP            ; 15  ↔              14
        DIV             ; 16  ÷              13
        1               ; 17  1              01
        ADD             ; 18  +              10
        HALT            ; 19  С/П            50
        JMP L00         ; 20  БП 00          51 00
