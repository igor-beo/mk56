; Program 3.14: Inverse of a 3x3 matrix (result replaces the input)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.61 (book61.pdf page 62)
; Input: a11=R7 a12=R8 a13=R9 / a21=R4 a22=R5 a23=R6 / a31=R1 a32=R2 a33=R3.
; Output: inverse in the same registers.
;
; Book example: A = |4 8 0; 8 8 8; 2 0 1| ->
;   A^-1 = |0,08333333 -0,08333333 0,66666666; 0,08333333 0,04166667 -0,33333333;
;           -0,16666666 0,16666666 -0,33333333|
; @reg R7=4 R8=8 R9=0 R4=8 R5=8 R6=8 R1=2 R2=0 R3=1
; @run
; @expect R7=0.08333333
; @expect R8=-0.08333333
; @expect R9=0.66666666
; @expect R4=0.08333333
; @expect R5=0.04166667
; @expect R6=-0.33333333
; @expect R1=-0.16666666
; @expect R2=0.16666666
; @expect R3=-0.33333333
;
; As printed:
;   00: 3 П0 ИП4 ИП7 ÷ Пd ИПd /-/ Пc ИП5
;   10: ИПd ИП8 × − Пa ИП6 ИПd ИП9 × −
;   20: Пb ИП1 ИП7 ÷ Пd ИПd /-/ П6 ИП2 ИПd
;   30: ИП8 × − П4 ИП3 ИПd ИП9 × − П5
;   40: ИП8 ИП7 ÷ П1 ИП9 ИП7 ÷ П2 ИП7 F1/x
;   50: П3 ИПa П7 ИПb П8 ИПc П9 FL0 02 С/П
;
; Each line: instruction ; address, keys, codes

        3               ; 00  3              03
        STO R0          ; 01  П0             40

L02:
        RCL R4          ; 02  ИП4            64
        RCL R7          ; 03  ИП7            67
        DIV             ; 04  ÷              13
        STO RD          ; 05  Пd             4D
        RCL RD          ; 06  ИПd            6D
        CHS             ; 07  /-/            0B
        STO RC          ; 08  Пc             4C
        RCL R5          ; 09  ИП5            65
        RCL RD          ; 10  ИПd            6D
        RCL R8          ; 11  ИП8            68
        MUL             ; 12  ×              12
        SUB             ; 13  −              11
        STO RA          ; 14  Пa             4A
        RCL R6          ; 15  ИП6            66
        RCL RD          ; 16  ИПd            6D
        RCL R9          ; 17  ИП9            69
        MUL             ; 18  ×              12
        SUB             ; 19  −              11
        STO RB          ; 20  Пb             4B
        RCL R1          ; 21  ИП1            61
        RCL R7          ; 22  ИП7            67
        DIV             ; 23  ÷              13
        STO RD          ; 24  Пd             4D
        RCL RD          ; 25  ИПd            6D
        CHS             ; 26  /-/            0B
        STO R6          ; 27  П6             46
        RCL R2          ; 28  ИП2            62
        RCL RD          ; 29  ИПd            6D
        RCL R8          ; 30  ИП8            68
        MUL             ; 31  ×              12
        SUB             ; 32  −              11
        STO R4          ; 33  П4             44
        RCL R3          ; 34  ИП3            63
        RCL RD          ; 35  ИПd            6D
        RCL R9          ; 36  ИП9            69
        MUL             ; 37  ×              12
        SUB             ; 38  −              11
        STO R5          ; 39  П5             45
        RCL R8          ; 40  ИП8            68
        RCL R7          ; 41  ИП7            67
        DIV             ; 42  ÷              13
        STO R1          ; 43  П1             41
        RCL R9          ; 44  ИП9            69
        RCL R7          ; 45  ИП7            67
        DIV             ; 46  ÷              13
        STO R2          ; 47  П2             42
        RCL R7          ; 48  ИП7            67
        INV             ; 49  F1/x           23
        STO R3          ; 50  П3             43
        RCL RA          ; 51  ИПa            6A
        STO R7          ; 52  П7             47
        RCL RB          ; 53  ИПb            6B
        STO R8          ; 54  П8             48
        RCL RC          ; 55  ИПc            6C
        STO R9          ; 56  П9             49
        LOOP0 L02       ; 57  FL0 02         5D 02
        HALT            ; 59  С/П            50
