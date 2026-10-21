; Program 7.32: Small-signal amplifier stage, common emitter (fig. 7.11б, 7.12б)
;   Rвх = rб + rэ (rк + Rн)/(rк (1 − a) + rэ + Rн),
;   KI = −(a rк − rэ)/(rк (1 − a) + rэ + Rн),
;   KU = −(a rк − rэ) Rн/(rэ (rк + Rн) + rб ((1 − a) rк + rэ + Rн)),
;   KE = −(a rк − rэ) Rн/(rэ (rк + Rн) + (Rи + rб)((1 − a) rк + rэ + Rн)),
;   Rвых = rк (1 − a) + rэ (1 + (a rк − rэ)/(rэ + rб + Rи))
;   (the book's formula prints "a rк + rэ" in Rвых; the listing and the book's
;   result use a rк − rэ)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.195 (book61.pdf page 196)
; Input (as in 7.31): rб = R1, rэ = R2, rк = R3, Rи = R4, Rн = R5, a = R6, then В/О С/П.
; Output: KE = R0 = X, KU = Ra, KI = Rb, Rвх = Rc, Rвых = Rd.
;
; Book example: rб = 400 Ohm, rэ = 25 Ohm, rк = 10^6 Ohm, Rи = 1000 Ohm,
;   Rн = 5000 Ohm, a = 0,98 -> KU = −139,45851, KE = −81,447388, KI = −39,15984,
;   Rвх = 1403,996 Ohm, Rвых = 37217,544 Ohm
; @reg R1=400 R2=25 R3=1e6 R4=1000 R5=5000 R6=0.98
; @run
; @expect X=-81.447388
; @expect Ra=-139.45851
; @expect Rb=-39.15984
; @expect Rc=1403.996
; @expect Rd=37217.544
;
; As printed:
;   00: ИП6 ИП3 × ИП2 − П7 1 ИП6 − ИП3
;   10: × ИП2 + ИП5 + П8 ИП4 ИП1 + П9
;   20: ИП8 × ИП3 ИП5 + ИП2 × Пc + F1/x
;   30: ИП5 ИП7 /−/ × Пb × П0 ИПb ИП1 ИП8
;   40: × ИПc + ÷ Пa ИП7 /−/ ИП8 ÷ Пb
;   50: ИП2 ИП5 ИП3 + × ИП8 ÷ ИП1 + Пc
;   60: ИП3 ИП6 × ИП2 − ИП9 ИП2 + ÷ 1
;   70: + ИП2 × 1 ИП6 − ИП3 × + Пd
;   80: ИП0 С/П
;
; Each line: instruction ; address, keys, codes

        RCL R6          ; 00  ИП6            66
        RCL R3          ; 01  ИП3            63
        MUL             ; 02  ×              12
        RCL R2          ; 03  ИП2            62
        SUB             ; 04  −              11
        STO R7          ; 05  П7             47
        1               ; 06  1              01
        RCL R6          ; 07  ИП6            66
        SUB             ; 08  −              11
        RCL R3          ; 09  ИП3            63
        MUL             ; 10  ×              12
        RCL R2          ; 11  ИП2            62
        ADD             ; 12  +              10
        RCL R5          ; 13  ИП5            65
        ADD             ; 14  +              10
        STO R8          ; 15  П8             48
        RCL R4          ; 16  ИП4            64
        RCL R1          ; 17  ИП1            61
        ADD             ; 18  +              10
        STO R9          ; 19  П9             49
        RCL R8          ; 20  ИП8            68
        MUL             ; 21  ×              12
        RCL R3          ; 22  ИП3            63
        RCL R5          ; 23  ИП5            65
        ADD             ; 24  +              10
        RCL R2          ; 25  ИП2            62
        MUL             ; 26  ×              12
        STO RC          ; 27  Пc             4C
        ADD             ; 28  +              10
        INV             ; 29  F1/x           23
        RCL R5          ; 30  ИП5            65
        RCL R7          ; 31  ИП7            67
        CHS             ; 32  /-/            0B
        MUL             ; 33  ×              12
        STO RB          ; 34  Пb             4B
        MUL             ; 35  ×              12
        STO R0          ; 36  П0             40
        RCL RB          ; 37  ИПb            6B
        RCL R1          ; 38  ИП1            61
        RCL R8          ; 39  ИП8            68
        MUL             ; 40  ×              12
        RCL RC          ; 41  ИПc            6C
        ADD             ; 42  +              10
        DIV             ; 43  ÷              13
        STO RA          ; 44  Пa             4A
        RCL R7          ; 45  ИП7            67
        CHS             ; 46  /-/            0B
        RCL R8          ; 47  ИП8            68
        DIV             ; 48  ÷              13
        STO RB          ; 49  Пb             4B
        RCL R2          ; 50  ИП2            62
        RCL R5          ; 51  ИП5            65
        RCL R3          ; 52  ИП3            63
        ADD             ; 53  +              10
        MUL             ; 54  ×              12
        RCL R8          ; 55  ИП8            68
        DIV             ; 56  ÷              13
        RCL R1          ; 57  ИП1            61
        ADD             ; 58  +              10
        STO RC          ; 59  Пc             4C
        RCL R3          ; 60  ИП3            63
        RCL R6          ; 61  ИП6            66
        MUL             ; 62  ×              12
        RCL R2          ; 63  ИП2            62
        SUB             ; 64  −              11
        RCL R9          ; 65  ИП9            69
        RCL R2          ; 66  ИП2            62
        ADD             ; 67  +              10
        DIV             ; 68  ÷              13
        1               ; 69  1              01
        ADD             ; 70  +              10
        RCL R2          ; 71  ИП2            62
        MUL             ; 72  ×              12
        1               ; 73  1              01
        RCL R6          ; 74  ИП6            66
        SUB             ; 75  −              11
        RCL R3          ; 76  ИП3            63
        MUL             ; 77  ×              12
        ADD             ; 78  +              10
        STO RD          ; 79  Пd             4D
        RCL R0          ; 80  ИП0            60
        HALT            ; 81  С/П            50
