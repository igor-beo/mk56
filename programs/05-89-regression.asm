; Program 5.89: Least-squares line y = b0 + b1·x
;   b1 = (sum x sum y − N sum xy)/((sum x)² − N sum x²), b0 = (sum y − b1 sum x)/N
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.140 (book61.pdf page 141)
; Input: N in X, В/О С/П (shows i = 1), then x_i С/П (shows x_i), y_i С/П (shows i+1), ...
; Output: after y_N: b1 in X (also Ra); С/П: b0 in X (also Rb).
; Sums: x R4, y R6, x² R5, xy R7.
;
; Book example: N = 5, y(x) = 5,5(2), 6,3(4), 7,2(6), 8(8), 8,6(10)
;   -> b1 = 0,395, b0 = 4,75
; @input 5
; @expect X=1
; @input 2
; @expect X=2
; @input 5.5
; @expect X=2
; @input 4
; @input 6.3
; @input 6
; @input 7.2
; @input 8
; @input 8
; @input 10
; @input 8.6
; @expect X=0.395
; @run
; @expect X=4.75
;
; As printed:
;   00: П1 П0 0 П4 П5 П6 П7 ИП1 ИП0 −
;   10: 1 + С/П П2 С/П П3 ИП6 + П6 ИП2
;   20: ИП4 + П4 ИП2 Fx² ИП5 + П5 ИП2 ИП3
;   30: × ИП7 + П7 FL0 07 ИП4 Fx² ИП1 ИП5
;   40: × − П8 ИП4 ИП6 × ИП1 ИП7 × −
;   50: ИП8 ÷ Пa С/П ИП6 ИПa ИП4 × − ИП1
;   60: ÷ Пb С/П
;
; Each line: instruction ; address, keys, codes

        STO R1          ; 00  П1             41
        STO R0          ; 01  П0             40
        0               ; 02  0              00
        STO R4          ; 03  П4             44
        STO R5          ; 04  П5             45
        STO R6          ; 05  П6             46
        STO R7          ; 06  П7             47

L07:
        RCL R1          ; 07  ИП1            61
        RCL R0          ; 08  ИП0            60
        SUB             ; 09  −              11
        1               ; 10  1              01
        ADD             ; 11  +              10
        HALT            ; 12  С/П            50
        STO R2          ; 13  П2             42
        HALT            ; 14  С/П            50
        STO R3          ; 15  П3             43
        RCL R6          ; 16  ИП6            66
        ADD             ; 17  +              10
        STO R6          ; 18  П6             46
        RCL R2          ; 19  ИП2            62
        RCL R4          ; 20  ИП4            64
        ADD             ; 21  +              10
        STO R4          ; 22  П4             44
        RCL R2          ; 23  ИП2            62
        SQ              ; 24  Fx²            22
        RCL R5          ; 25  ИП5            65
        ADD             ; 26  +              10
        STO R5          ; 27  П5             45
        RCL R2          ; 28  ИП2            62
        RCL R3          ; 29  ИП3            63
        MUL             ; 30  ×              12
        RCL R7          ; 31  ИП7            67
        ADD             ; 32  +              10
        STO R7          ; 33  П7             47
        LOOP0 L07       ; 34  FL0 07         5D 07
        RCL R4          ; 36  ИП4            64
        SQ              ; 37  Fx²            22
        RCL R1          ; 38  ИП1            61
        RCL R5          ; 39  ИП5            65
        MUL             ; 40  ×              12
        SUB             ; 41  −              11
        STO R8          ; 42  П8             48
        RCL R4          ; 43  ИП4            64
        RCL R6          ; 44  ИП6            66
        MUL             ; 45  ×              12
        RCL R1          ; 46  ИП1            61
        RCL R7          ; 47  ИП7            67
        MUL             ; 48  ×              12
        SUB             ; 49  −              11
        RCL R8          ; 50  ИП8            68
        DIV             ; 51  ÷              13
        STO RA          ; 52  Пa             4A
        HALT            ; 53  С/П            50
        RCL R6          ; 54  ИП6            66
        RCL RA          ; 55  ИПa            6A
        RCL R4          ; 56  ИП4            64
        MUL             ; 57  ×              12
        SUB             ; 58  −              11
        RCL R1          ; 59  ИП1            61
        DIV             ; 60  ÷              13
        STO RB          ; 61  Пb             4B
        HALT            ; 62  С/П            50
