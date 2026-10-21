; Program 4.18: Coefficients of the Hermite polynomial Hn(x)
; (the probabilists' form, leading coefficient 1)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.69 (book61.pdf page 70)
; Input: n in X.  Output: each С/П shows the next coefficient, highest power first
; (powers n, n-2, n-4, ...), until 0 is displayed.
;
; Book example: n = 8 -> H8(x) = 1x⁸ − 28x⁶ + 210x⁴ − 420x² + 105
; @input 8
; @expect X=1
; @run
; @expect X=-28
; @run
; @expect X=210
; @run
; @expect X=-420
; @run
; @expect X=105
; @run
; @expect X=0
;
; As printed:
;   00: П2 1 П3 П8 + П4 2 П5 ИП8 С/П
;   10: ИП4 1 − П9 1 − П4 ИП9 × ИП8
;   20: × ИП5 /-/ ÷ П8 ИП5 2 + П5 БП 08
;
; Each line: instruction ; address, keys, codes

        STO R2          ; 00  П2             42
        1               ; 01  1              01
        STO R3          ; 02  П3             43
        STO R8          ; 03  П8             48
        ADD             ; 04  +              10
        STO R4          ; 05  П4             44
        2               ; 06  2              02
        STO R5          ; 07  П5             45

L08:
        RCL R8          ; 08  ИП8            68
        HALT            ; 09  С/П            50
        RCL R4          ; 10  ИП4            64
        1               ; 11  1              01
        SUB             ; 12  −              11
        STO R9          ; 13  П9             49
        1               ; 14  1              01
        SUB             ; 15  −              11
        STO R4          ; 16  П4             44
        RCL R9          ; 17  ИП9            69
        MUL             ; 18  ×              12
        RCL R8          ; 19  ИП8            68
        MUL             ; 20  ×              12
        RCL R5          ; 21  ИП5            65
        CHS             ; 22  /-/            0B
        DIV             ; 23  ÷              13
        STO R8          ; 24  П8             48
        RCL R5          ; 25  ИП5            65
        2               ; 26  2              02
        ADD             ; 27  +              10
        STO R5          ; 28  П5             45
        JMP L08         ; 29  БП 08          51 08
