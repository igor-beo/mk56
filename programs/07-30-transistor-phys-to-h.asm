; Program 7.30: h-parameters of a bipolar transistor from its physical parameters (table 7.4)
;   Common emitter / common collector, with Δ = rэ + rк − a rк:
;     h11 = rб + rэ rк/Δ, h22 = 1/Δ;
;     CE: h12 = rэ/Δ, h21 = (a rк − rэ)/Δ;  CC: h12 = (rк − a rк)/Δ, h21 = −rк/Δ
;   Common base: h11 = rэ + (1 − a) rб rк/(rб + rк), h12 = rб/(rк + rб),
;     h21 = −(rб + a rк)/(rб + rк), h22 = 1/(rк + rб)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.192-193 (book61.pdf pages 193-194)
; Input: rб = R1, rэ = R2, rк = R3, a = R4, then В/О С/П.
; Output: h11 = Ra, h12 = Rb, h21 = Rc = X, h22 = Rd.
; First С/П: common emitter; second: common collector; third: common base.
;
; Book example (p.193): rб = 400 Ohm, rэ = 25 Ohm, rк = 10^6 Ohm, a = 0,985
; @reg R1=400 R2=25 R3=1e6 R4=0.985
; CE: h11 = 2063,8935, h12 = 1,6638935*10^-3, h21 = 65,55574, h22 = 6,655574*10^-5
; @run
; @expect X=65.55574
; @expect Ra=2063.8935
; @expect Rb=1.6638935e-3 tol=1e-10
; @expect Rd=6.655574e-5 tol=1e-12
; CC: h11 = 2063,8935, h12 = 0,9983361, h21 = −66,55574, h22 = 6,655574*10^-5
; @run
; @expect X=-66.55574
; @expect Ra=2063.8935
; @expect Rb=0.9983361
; @expect Rd=6.655574e-5 tol=1e-12
; CB: h11 = 30,997601, h12 = 3,9984006*10^-4, h21 = −0,98500599, h22 = 9,9960015*10^-7
; @run
; @expect X=-0.98500599
; @expect Ra=30.997601
; @expect Rb=3.9984006e-4 tol=1e-11
; @expect Rd=9.9960015e-7 tol=1e-14
;
; As printed:
;   00: ИП1 ИП3 + F1/x П9 ИП2 ИП3 + ИП3 ИП4
;   10: × П7 − F1/x П8 Пd ИП2 × Пb ИП2
;   20: ИП3 ИП8 × × ИП1 + Пa ИП7 ИП2 −
;   30: ИП8 × Пc С/П ИП3 ИП7 − ИП8 × Пb
;   40: ИП3 /−/ ИП8 × Пc С/П 1 ИП4 − ИП1
;   50: × ИП3 × ИП9 × ИП2 + Пa ИП9 Пd
;   60: ИП1 × Пb ИП1 ИП4 ИП3 × + ИП9 /−/
;   70: × Пc С/П
;
; Each line: instruction ; address, keys, codes

        RCL R1          ; 00  ИП1            61
        RCL R3          ; 01  ИП3            63
        ADD             ; 02  +              10
        INV             ; 03  F1/x           23
        STO R9          ; 04  П9             49
        RCL R2          ; 05  ИП2            62
        RCL R3          ; 06  ИП3            63
        ADD             ; 07  +              10
        RCL R3          ; 08  ИП3            63
        RCL R4          ; 09  ИП4            64
        MUL             ; 10  ×              12
        STO R7          ; 11  П7             47
        SUB             ; 12  −              11
        INV             ; 13  F1/x           23
        STO R8          ; 14  П8             48
        STO RD          ; 15  Пd             4D
        RCL R2          ; 16  ИП2            62
        MUL             ; 17  ×              12
        STO RB          ; 18  Пb             4B
        RCL R2          ; 19  ИП2            62
        RCL R3          ; 20  ИП3            63
        RCL R8          ; 21  ИП8            68
        MUL             ; 22  ×              12
        MUL             ; 23  ×              12
        RCL R1          ; 24  ИП1            61
        ADD             ; 25  +              10
        STO RA          ; 26  Пa             4A
        RCL R7          ; 27  ИП7            67
        RCL R2          ; 28  ИП2            62
        SUB             ; 29  −              11
        RCL R8          ; 30  ИП8            68
        MUL             ; 31  ×              12
        STO RC          ; 32  Пc             4C
        HALT            ; 33  С/П            50
        RCL R3          ; 34  ИП3            63
        RCL R7          ; 35  ИП7            67
        SUB             ; 36  −              11
        RCL R8          ; 37  ИП8            68
        MUL             ; 38  ×              12
        STO RB          ; 39  Пb             4B
        RCL R3          ; 40  ИП3            63
        CHS             ; 41  /-/            0B
        RCL R8          ; 42  ИП8            68
        MUL             ; 43  ×              12
        STO RC          ; 44  Пc             4C
        HALT            ; 45  С/П            50
        1               ; 46  1              01
        RCL R4          ; 47  ИП4            64
        SUB             ; 48  −              11
        RCL R1          ; 49  ИП1            61
        MUL             ; 50  ×              12
        RCL R3          ; 51  ИП3            63
        MUL             ; 52  ×              12
        RCL R9          ; 53  ИП9            69
        MUL             ; 54  ×              12
        RCL R2          ; 55  ИП2            62
        ADD             ; 56  +              10
        STO RA          ; 57  Пa             4A
        RCL R9          ; 58  ИП9            69
        STO RD          ; 59  Пd             4D
        RCL R1          ; 60  ИП1            61
        MUL             ; 61  ×              12
        STO RB          ; 62  Пb             4B
        RCL R1          ; 63  ИП1            61
        RCL R4          ; 64  ИП4            64
        RCL R3          ; 65  ИП3            63
        MUL             ; 66  ×              12
        ADD             ; 67  +              10
        RCL R9          ; 68  ИП9            69
        CHS             ; 69  /-/            0B
        MUL             ; 70  ×              12
        STO RC          ; 71  Пc             4C
        HALT            ; 72  С/П            50
