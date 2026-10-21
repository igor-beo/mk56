; Program 5.82: Sample correlation coefficient
;   r = (sum XY − sum X sum Y/N) / sqrt((sum X² − (sum X)²/N)(sum Y² − (sum Y)²/N))
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.136 (book61.pdf page 137)
; Input: N in X, В/О С/П (shows 0), then X1 С/П (shows X1), Y1 С/П, ..., XN С/П, YN С/П.
; Output: r in X (also in R2). Sums: X R7, X² R6, Y R5, Y² R4, XY R3.
;
; Book example: N = 5, Y(X) = 2(0,95), 4,05(2,1), 5,8(3), 8,1(4,1), 9,2(4,9)
;   -> r = 0,99872802
; @input 5
; @expect X=0
; @input 0.95
; @expect X=0.95
; @input 2
; @input 2.1
; @input 4.05
; @input 3
; @input 5.8
; @input 4.1
; @input 8.1
; @input 4.9
; @input 9.2
; @expect X=0.99872802
;
; As printed:
;   00: П0 П1 0 П3 П4 П5 П6 П7 П9 ИП9
;   10: С/П П8 ИП7 + П7 ИП8 Fx² ИП6 + П6
;   20: ИП8 С/П П9 ИП5 + П5 ИП9 Fx² ИП4 +
;   30: П4 ИП8 ИП9 × ИП3 + П3 FL0 09 ИП6
;   40: ИП7 Fx² ИП1 ÷ − ИП4 ИП5 Fx² ИП1 ÷
;   50: − × F√ П2 ИП3 ИП7 ИП5 × ИП1 ÷
;   60: − ИП2 ÷ П2 С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R0          ; 00  П0             40
        STO R1          ; 01  П1             41
        0               ; 02  0              00
        STO R3          ; 03  П3             43
        STO R4          ; 04  П4             44
        STO R5          ; 05  П5             45
        STO R6          ; 06  П6             46
        STO R7          ; 07  П7             47
        STO R9          ; 08  П9             49

L09:
        RCL R9          ; 09  ИП9            69
        HALT            ; 10  С/П            50
        STO R8          ; 11  П8             48
        RCL R7          ; 12  ИП7            67
        ADD             ; 13  +              10
        STO R7          ; 14  П7             47
        RCL R8          ; 15  ИП8            68
        SQ              ; 16  Fx²            22
        RCL R6          ; 17  ИП6            66
        ADD             ; 18  +              10
        STO R6          ; 19  П6             46
        RCL R8          ; 20  ИП8            68
        HALT            ; 21  С/П            50
        STO R9          ; 22  П9             49
        RCL R5          ; 23  ИП5            65
        ADD             ; 24  +              10
        STO R5          ; 25  П5             45
        RCL R9          ; 26  ИП9            69
        SQ              ; 27  Fx²            22
        RCL R4          ; 28  ИП4            64
        ADD             ; 29  +              10
        STO R4          ; 30  П4             44
        RCL R8          ; 31  ИП8            68
        RCL R9          ; 32  ИП9            69
        MUL             ; 33  ×              12
        RCL R3          ; 34  ИП3            63
        ADD             ; 35  +              10
        STO R3          ; 36  П3             43
        LOOP0 L09       ; 37  FL0 09         5D 09
        RCL R6          ; 39  ИП6            66
        RCL R7          ; 40  ИП7            67
        SQ              ; 41  Fx²            22
        RCL R1          ; 42  ИП1            61
        DIV             ; 43  ÷              13
        SUB             ; 44  −              11
        RCL R4          ; 45  ИП4            64
        RCL R5          ; 46  ИП5            65
        SQ              ; 47  Fx²            22
        RCL R1          ; 48  ИП1            61
        DIV             ; 49  ÷              13
        SUB             ; 50  −              11
        MUL             ; 51  ×              12
        SQRT            ; 52  F√             21
        STO R2          ; 53  П2             42
        RCL R3          ; 54  ИП3            63
        RCL R7          ; 55  ИП7            67
        RCL R5          ; 56  ИП5            65
        MUL             ; 57  ×              12
        RCL R1          ; 58  ИП1            61
        DIV             ; 59  ÷              13
        SUB             ; 60  −              11
        RCL R2          ; 61  ИП2            62
        DIV             ; 62  ÷              13
        STO R2          ; 63  П2             42
        HALT            ; 64  С/П            50
        JMP L00         ; 65  БП 00          51 00
