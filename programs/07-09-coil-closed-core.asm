; Program 7.9: Number of turns w of a coil with a closed core (fig. 7.7)
;   w = sqrt(L0 lm (1 + mu dl/(a lm))/(4 pi mu Fc))
;   (Fc = core cross-section, lm = mean magnetic path length, dl = gap)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.179-180 (book61.pdf pages 180-181)
; Input: Fc, lm, a, dl, mu and L0 into X, each followed by С/П
; (Fc = R9, lm = R8, a = R7, dl = R6, mu = R5).  Output: w in X.
; For a new L0 key it and press С/П.
;
; Book example: Fc = 1 cm², lm = 10 cm, a = 1,5 cm, dl = 0,05 cm, mu = 1000,
;   L0 = 5*10^7 nH -> w = 415,23228; L0 = 1*10^7 nH -> w = 185,69752
; @input 1
; @input 10
; @input 1.5
; @input 0.05
; @input 1000
; @input 5e7
; @expect X=415.23228 tol=1e-5
; @input 1e7
; @expect X=185.69752 tol=1e-5
;
; As printed:
;   00: П9 С/П П8 С/П П7 С/П П6 С/П П5 С/П
;   10: ИП8 × 4 ÷ Fπ ÷ ИП9 ÷ ИП5 ÷
;   20: ИП5 ИП6 × ИП7 ÷ ИП8 ÷ 1 + ×
;   30: F√ БП 09
;
; Each line: instruction ; address, keys, codes

        STO R9          ; 00  П9             49
        HALT            ; 01  С/П            50
        STO R8          ; 02  П8             48
        HALT            ; 03  С/П            50
        STO R7          ; 04  П7             47
        HALT            ; 05  С/П            50
        STO R6          ; 06  П6             46
        HALT            ; 07  С/П            50
        STO R5          ; 08  П5             45

L09:
        HALT            ; 09  С/П            50
        RCL R8          ; 10  ИП8            68
        MUL             ; 11  ×              12
        4               ; 12  4              04
        DIV             ; 13  ÷              13
        PI              ; 14  Fπ             20
        DIV             ; 15  ÷              13
        RCL R9          ; 16  ИП9            69
        DIV             ; 17  ÷              13
        RCL R5          ; 18  ИП5            65
        DIV             ; 19  ÷              13
        RCL R5          ; 20  ИП5            65
        RCL R6          ; 21  ИП6            66
        MUL             ; 22  ×              12
        RCL R7          ; 23  ИП7            67
        DIV             ; 24  ÷              13
        RCL R8          ; 25  ИП8            68
        DIV             ; 26  ÷              13
        1               ; 27  1              01
        ADD             ; 28  +              10
        MUL             ; 29  ×              12
        SQRT            ; 30  F√             21
        JMP L09         ; 31  БП 09          51 09
