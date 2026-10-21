; Program 3.6: Angle in radians -> degrees, minutes, seconds
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.56-57 (book61.pdf pages 57-58)
; Input: phi (radians) in X.  Output: three stops: degrees, then minutes, then seconds.
; Uses two nested subroutines (19: multiply, 27: split integer/fraction).
;
; Book example: phi = 2 rad, pressing С/П three times gives 114, 35 and 29,616.
; The printed 29,616 is an artefact of 8-digit arithmetic: 360/pi is kept as
; 114,59156, so the fraction is 0,59156 exactly. With full double precision the
; seconds come out as 29,6195 (pi = 3,1415926) or 29,6125 (exact pi);
; tol=2e-4 covers all three.
; @input 2
; @expect X=114
; @run
; @expect X=35
; @run
; @expect X=29.616 tol=2e-4
;
; As printed:
;   00: Fπ ÷ 1 8 0 ПП 19 ИП8 6 0
;   10: ПП 19 ИП8 6 0 × С/П БП 00 ×
;   20: ПП 27 ИП9 1 − С/П В/О 1 + П9
;   30: КИП9 ↔ ИП9 − П8 В/О
;
; Each line: instruction ; address, keys, codes

L00:
        PI              ; 00  Fπ             20
        DIV             ; 01  ÷              13
        180             ; 02  1 8 0          01 08 00
        CALL sub19      ; 05  ПП 19          53 19
        RCL R8          ; 07  ИП8            68
        60              ; 08  6 0            06 00
        CALL sub19      ; 10  ПП 19          53 19
        RCL R8          ; 12  ИП8            68
        60              ; 13  6 0            06 00
        MUL             ; 15  ×              12
        HALT            ; 16  С/П            50
        JMP L00         ; 17  БП 00          51 00

sub19:
        MUL             ; 19  ×              12
        CALL sub27      ; 20  ПП 27          53 27
        RCL R9          ; 22  ИП9            69
        1               ; 23  1              01
        SUB             ; 24  −              11
        HALT            ; 25  С/П            50
        RTN             ; 26  В/О            52

sub27:
        1               ; 27  1              01
        ADD             ; 28  +              10
        STO R9          ; 29  П9             49
        RCL (R9)        ; 30  КИП9           D9
        SWAP            ; 31  ↔              14
        RCL R9          ; 32  ИП9            69
        SUB             ; 33  −              11
        STO R8          ; 34  П8             48
        RTN             ; 35  В/О            52
