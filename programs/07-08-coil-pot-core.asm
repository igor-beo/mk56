; Program 7.8: Number of turns w of a coil on a pot (armoured) core (fig. 7.6)
;   w = sqrt(L0 (A + B)/(19,74 mu)),
;   A = (h1 + h2)(1/(d4² − d3²) + 1/(d2² − d1²)),  B = ln((d3 + d4)/(d1 + d2))/(h2 − h1)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.179 (book61.pdf page 180)
; Input (after В/О and С/П): d1, d2, d3, d4, h1, h2, mu and L0 into X, each
; followed by С/П. The input loop stores them by КП0 (R0 counts 8 -> 1):
; d1 = R7, d2 = R6, d3 = R5, d4 = R4, h1 = R3, h2 = R2, mu = R1; L0 = R8.
; Output: w in X. For a new L0 key it and press С/П.
;
; Book example: d1 = 1 cm, d2 = 2 cm, d3 = 4 cm, d4 = 5 cm, h1 = 3 cm, h2 = 4 cm,
;   mu = 10, L0 = 5*10^5 nH -> w = 103,26144; L0 = 1*10^5 nH -> w = 46,179922
; @run
; @input 1
; @input 2
; @input 4
; @input 5
; @input 3
; @input 4
; @input 10
; @input 5e5
; @expect X=103.26144 tol=1e-5
; @input 1e5
; @expect X=46.179922 tol=1e-5
;
; As printed:
;   00: 8 П0 0 С/П КП0 ИП0 1 − Fx=0 02
;   10: С/П П8 ИП4 Fx² ИП5 Fx² − F1/x ИП6 Fx²
;   20: ИП7 Fx² − F1/x + ИП3 ИП2 + × Пa
;   30: ИП5 ИП4 + ИП7 ИП6 + ÷ Fln ИП2 ИП3
;   40: − ÷ Пa + ИП8 × ИП1 ÷ 1 9
;   50: , 7 4 ÷ F√ БП 10
;
; Each line: instruction ; address, keys, codes

        8               ; 00  8              08
        STO R0          ; 01  П0             40

L02:
        0               ; 02  0              00
        HALT            ; 03  С/П            50
        STO (R0)        ; 04  КП0            B0
        RCL R0          ; 05  ИП0            60
        1               ; 06  1              01
        SUB             ; 07  −              11
        JNZ L02         ; 08  Fx=0 02        5E 02

L10:
        HALT            ; 10  С/П            50
        STO R8          ; 11  П8             48
        RCL R4          ; 12  ИП4            64
        SQ              ; 13  Fx²            22
        RCL R5          ; 14  ИП5            65
        SQ              ; 15  Fx²            22
        SUB             ; 16  −              11
        INV             ; 17  F1/x           23
        RCL R6          ; 18  ИП6            66
        SQ              ; 19  Fx²            22
        RCL R7          ; 20  ИП7            67
        SQ              ; 21  Fx²            22
        SUB             ; 22  −              11
        INV             ; 23  F1/x           23
        ADD             ; 24  +              10
        RCL R3          ; 25  ИП3            63
        RCL R2          ; 26  ИП2            62
        ADD             ; 27  +              10
        MUL             ; 28  ×              12
        STO RA          ; 29  Пa             4A
        RCL R5          ; 30  ИП5            65
        RCL R4          ; 31  ИП4            64
        ADD             ; 32  +              10
        RCL R7          ; 33  ИП7            67
        RCL R6          ; 34  ИП6            66
        ADD             ; 35  +              10
        DIV             ; 36  ÷              13
        LN              ; 37  Fln            18
        RCL R2          ; 38  ИП2            62
        RCL R3          ; 39  ИП3            63
        SUB             ; 40  −              11
        DIV             ; 41  ÷              13
        STO RA          ; 42  Пa             4A
        ADD             ; 43  +              10
        RCL R8          ; 44  ИП8            68
        MUL             ; 45  ×              12
        RCL R1          ; 46  ИП1            61
        DIV             ; 47  ÷              13
        19.74           ; 48  1 9 , 7 4      01 09 0A 07 04
        DIV             ; 53  ÷              13
        SQRT            ; 54  F√             21
        JMP L10         ; 55  БП 10          51 10
