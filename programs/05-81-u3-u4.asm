; Program 5.81: Auxiliary coefficients U3 and U4 (normality test for A and E)
;   U3 = sqrt(6(N−1)/((N+1)(N+3))), U4 = sqrt(24N(N−2)(N−3)/((N−1)²(N+3)(N+5)))
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.136 (book61.pdf page 137)
; Input: N in X. Output: U3 in X; С/П: U4 in X.
; The U4 branch reuses the "+ ÷ ИП0 3 + ÷ F√ С/П" tail via БП 07.
;
; Book example: N = 10 -> U3 = 0,61450986, U4 = 0,92244356
; @input 10
; @expect X=0.61450986
; @run
; @expect X=0.92244356
;
; As printed:
;   00: П0 1 − 6 × ИП0 1 + ÷ ИП0
;   10: 3 + ÷ F√ С/П ИП0 2 4 × ИП0
;   20: 2 − × ИП0 3 − × ИП0 1 −
;   30: Fx² ÷ ИП0 5 БП 07
;
; Each line: instruction ; address, keys, codes

        STO R0          ; 00  П0             40
        1               ; 01  1              01
        SUB             ; 02  −              11
        6               ; 03  6              06
        MUL             ; 04  ×              12
        RCL R0          ; 05  ИП0            60
        1               ; 06  1              01

L07:
        ADD             ; 07  +              10
        DIV             ; 08  ÷              13
        RCL R0          ; 09  ИП0            60
        3               ; 10  3              03
        ADD             ; 11  +              10
        DIV             ; 12  ÷              13
        SQRT            ; 13  F√             21
        HALT            ; 14  С/П            50
        RCL R0          ; 15  ИП0            60
        24              ; 16  2 4            02 04
        MUL             ; 18  ×              12
        RCL R0          ; 19  ИП0            60
        2               ; 20  2              02
        SUB             ; 21  −              11
        MUL             ; 22  ×              12
        RCL R0          ; 23  ИП0            60
        3               ; 24  3              03
        SUB             ; 25  −              11
        MUL             ; 26  ×              12
        RCL R0          ; 27  ИП0            60
        1               ; 28  1              01
        SUB             ; 29  −              11
        SQ              ; 30  Fx²            22
        DIV             ; 31  ÷              13
        RCL R0          ; 32  ИП0            60
        5               ; 33  5              05
        JMP L07         ; 34  БП 07          51 07
