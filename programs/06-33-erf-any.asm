; Program 6.33: Probability integral Φ(y) for any y >= 0: the series (6.18) for
;   y < 4 (as in program 6.31) and the asymptotic expansion (6.19) for y >= 4
;   (as in program 6.32, with R6 in place of R8)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.168 (book61.pdf page 169)
; Input: y in X.  Output: Φ(y) in X.
; П(x) follows from (6.17): Φ(x) ↑ 1 + 2 ÷  (the book gives П(0,1) = 0,53982785).
;
; Book examples: Φ(0,1) = 0,079655675; Φ(4) = 0,9999365
; @input 0.1
; @expect X=0.079655675
; @input 4
; @expect X=0.9999365
;
; As printed:
;   00: П9 4 − Fx<0 52 ИП9 Fx² 2 /-/ ÷
;   10: П6 2 Fπ ÷ F√ ИП9 × П7 П8 0
;   20: П4 КИП4 ИП4 2 × 1 + П5 ИП4 2
;   30: × 1 − ИП6 × ИП4 ÷ ИП5 ÷ ИП7
;   40: × П7 ИП8 + П8 FBx − Fx=0 21 ИП8
;   50: БП 81 ИП9 Fx² П6 2 /-/ ÷ Feˣ 2
;   60: Fπ ÷ F√ × ИП9 ÷ П9 3 ИП6 ÷
;   70: 1 ↔ − ИП6 ÷ 1 − ИП9 × 1
;   80: + С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        4               ; 01  4              04
        SUB             ; 02  −              11
        JGE L52         ; 03  Fx<0 52        5C 52
        RCL R9          ; 05  ИП9            69
        SQ              ; 06  Fx²            22
        -2              ; 07  2 /-/          02 0B
        DIV             ; 09  ÷              13
        STO R6          ; 10  П6             46
        2               ; 11  2              02
        PI              ; 12  Fπ             20
        DIV             ; 13  ÷              13
        SQRT            ; 14  F√             21
        RCL R9          ; 15  ИП9            69
        MUL             ; 16  ×              12
        STO R7          ; 17  П7             47
        STO R8          ; 18  П8             48
        0               ; 19  0              00
        STO R4          ; 20  П4             44

L21:
        RCL (R4)        ; 21  КИП4           D4
        RCL R4          ; 22  ИП4            64
        2               ; 23  2              02
        MUL             ; 24  ×              12
        1               ; 25  1              01
        ADD             ; 26  +              10
        STO R5          ; 27  П5             45
        RCL R4          ; 28  ИП4            64
        2               ; 29  2              02
        MUL             ; 30  ×              12
        1               ; 31  1              01
        SUB             ; 32  −              11
        RCL R6          ; 33  ИП6            66
        MUL             ; 34  ×              12
        RCL R4          ; 35  ИП4            64
        DIV             ; 36  ÷              13
        RCL R5          ; 37  ИП5            65
        DIV             ; 38  ÷              13
        RCL R7          ; 39  ИП7            67
        MUL             ; 40  ×              12
        STO R7          ; 41  П7             47
        RCL R8          ; 42  ИП8            68
        ADD             ; 43  +              10
        STO R8          ; 44  П8             48
        LASTX           ; 45  FBx            0F
        SUB             ; 46  −              11
        JNZ L21         ; 47  Fx=0 21        5E 21
        RCL R8          ; 49  ИП8            68
        JMP L81         ; 50  БП 81          51 81

L52:
        RCL R9          ; 52  ИП9            69
        SQ              ; 53  Fx²            22
        STO R6          ; 54  П6             46
        -2              ; 55  2 /-/          02 0B
        DIV             ; 57  ÷              13
        EXP             ; 58  Feˣ            16
        2               ; 59  2              02
        PI              ; 60  Fπ             20
        DIV             ; 61  ÷              13
        SQRT            ; 62  F√             21
        MUL             ; 63  ×              12
        RCL R9          ; 64  ИП9            69
        DIV             ; 65  ÷              13
        STO R9          ; 66  П9             49
        3               ; 67  3              03
        RCL R6          ; 68  ИП6            66
        DIV             ; 69  ÷              13
        1               ; 70  1              01
        SWAP            ; 71  ↔              14
        SUB             ; 72  −              11
        RCL R6          ; 73  ИП6            66
        DIV             ; 74  ÷              13
        1               ; 75  1              01
        SUB             ; 76  −              11
        RCL R9          ; 77  ИП9            69
        MUL             ; 78  ×              12
        1               ; 79  1              01
        ADD             ; 80  +              10

L81:
        HALT            ; 81  С/П            50
        JMP L00         ; 82  БП 00          51 00
