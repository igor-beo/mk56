; Program 5.29: Roots of a2 x² + a1 x + a0 = 0 by
;   x1,2 = −a1/(2a2) ± √((a1/(2a2))² − a0/a2)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.97-98 (book61.pdf pages 98-99)
; Input: a0 in R0, a1 in R1, a2 in R2; В/О, С/П.
; Output: real roots: 7 in X, x1 in Y, x2 in R7;
;   complex roots x1,2 = d ± j·m: 4 in X, m in Y, d in R4.
;
; Book example: 2x² − 5x − 10 = 0 -> x1 = −1,3117376, x2 = 3,8117376
; @reg R0=-10 R1=-5 R2=2
; @run
; @expect X=7
; @expect Y=-1.3117376
; @expect R7=3.8117376
; @reset
; Book example: x² + 2x + 15 = 0 -> x1,2 = −1 ± j·3,7416573
; @reg R0=15 R1=2 R2=1
; @run
; @expect X=4
; @expect Y=3.7416573
; @expect R4=-1
; @reset
; Book example (p.98, comparing with 5.30): 3x² + 20000x + 12 = 0 -> x1 = −6666,666,
; x2 = −6,66666666·10^-4 (8-digit cancellation; exact x2 = −6·10^-4).
; x2 is not checked: p + √D with p = −3333,3333 can only be a multiple of 10^-4 in
; 8-digit arithmetic (the emulator gives −8·10^-4); the printed −6,67·10^-4 is not
; reproducible, so only x1 is tested here.
; @reg R0=12 R1=20000 R2=3
; @run
; @expect X=7
; @expect Y=-6666.666
;
; As printed:
;   00: ИП1 /-/ ИП2 ÷ 2 ÷ П4 Fx² ИП0 ИП2
;   10: ÷ − Fx<0 18 /-/ F√ 4 С/П F√ П3
;   20: ИП4 + П7 ИП4 ИП3 − 7 С/П
;
; Each line: instruction ; address, keys, codes

        RCL R1          ; 00  ИП1            61
        CHS             ; 01  /-/            0B
        RCL R2          ; 02  ИП2            62
        DIV             ; 03  ÷              13
        2               ; 04  2              02
        DIV             ; 05  ÷              13
        STO R4          ; 06  П4             44
        SQ              ; 07  Fx²            22
        RCL R0          ; 08  ИП0            60
        RCL R2          ; 09  ИП2            62
        DIV             ; 10  ÷              13
        SUB             ; 11  −              11
        JGE L18         ; 12  Fx<0 18        5C 18
        CHS             ; 14  /-/            0B
        SQRT            ; 15  F√             21
        4               ; 16  4              04
        HALT            ; 17  С/П            50

L18:
        SQRT            ; 18  F√             21
        STO R3          ; 19  П3             43
        RCL R4          ; 20  ИП4            64
        ADD             ; 21  +              10
        STO R7          ; 22  П7             47
        RCL R4          ; 23  ИП4            64
        RCL R3          ; 24  ИП3            63
        SUB             ; 25  −              11
        7               ; 26  7              07
        HALT            ; 27  С/П            50
