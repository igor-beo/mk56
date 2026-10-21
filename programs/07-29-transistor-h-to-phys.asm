; Program 7.29: Physical parameters of a transistor from its h-parameters (table 7.3)
;   Common base (code 0): rэ = h11 − (1 + h21) h12/h22, rб = h12/h22,
;     rк = (1 − h12)/h22, rm = −(h12 + h21)/h22, a = −(h12 + h21)/(1 − h12)
;   Common emitter (code 1): rэ = h12/h22, rб = h11 − h12 (1 + h21)/h22,
;     rк = (1 + h21)/h22, rm = (h12 + h21)/h22, a = (h12 + h21)/(1 + h21)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.191-192 (book61.pdf pages 192-193)
; Input: h11 = Ra, h12 = Rb, h21 = Rc, h22 = Rd; code (0 = common base,
; 1 = common emitter) into X, then С/П (from step 00).
; Output: rб = R1, rэ = R2, rк = R3, rm = R4, a = R6 = X.
; For new data store the h-parameters, key the code and press С/П.
;
; Book example (p.192), common base: h11 = 25 Ohm, h12 = 0,25*10^-3, h21 = −0,98,
;   h22 = 3*10^-6 S, code 0 -> rб = 83,333333, rэ = 23,333333, rк = 333250,
;   rm = 326583,33, a = 0,97999499
; @reg Ra=25 Rb=0.25e-3 Rc=-0.98 Rd=3e-6
; @input 0
; @expect X=0.97999499
; @expect R1=83.333333
; @expect R2=23.333333
; @expect R3=333250
; @expect R4=326583.33
; Common emitter: h11 = 2800 Ohm, h12 = 2*10^-3, h21 = 60, h22 = 5*10^-5 S, code 1
;   -> rб = 360, rэ = 40, rк = 1220000, rm = 1200040, a = 0,98363934
; @reg Ra=2800 Rb=2e-3 Rc=60 Rd=5e-5
; @input 1
; @expect X=0.98363934
; @expect R1=360
; @expect R2=40
; @expect R3=1220000
; @expect R4=1200040
;
; As printed:
;   00: П5 ИПa 1 ИПc + ИПb × ИПd ÷ −
;   10: П2 ИПb ИПd ÷ П1 ИПb ИПc + П9 ИПd
;   20: ÷ П4 ИП5 Fx=0 44 1 ИПb − ИПd ÷
;   30: П3 ИП4 /−/ П4 ИП9 /−/ 1 ИПb − ÷
;   40: П6 С/П БП 00 ИП1 ИП2 ↔ П2 ↔ П1
;   50: 1 ИПc + ИПd ÷ П3 ИП9 1 ИПc +
;   60: ÷ П6 БП 41
;
; Each line: instruction ; address, keys, codes

L00:
        STO R5          ; 00  П5             45
        RCL RA          ; 01  ИПa            6A
        1               ; 02  1              01
        RCL RC          ; 03  ИПc            6C
        ADD             ; 04  +              10
        RCL RB          ; 05  ИПb            6B
        MUL             ; 06  ×              12
        RCL RD          ; 07  ИПd            6D
        DIV             ; 08  ÷              13
        SUB             ; 09  −              11
        STO R2          ; 10  П2             42
        RCL RB          ; 11  ИПb            6B
        RCL RD          ; 12  ИПd            6D
        DIV             ; 13  ÷              13
        STO R1          ; 14  П1             41
        RCL RB          ; 15  ИПb            6B
        RCL RC          ; 16  ИПc            6C
        ADD             ; 17  +              10
        STO R9          ; 18  П9             49
        RCL RD          ; 19  ИПd            6D
        DIV             ; 20  ÷              13
        STO R4          ; 21  П4             44
        RCL R5          ; 22  ИП5            65
        JNZ L44         ; 23  Fx=0 44        5E 44
        1               ; 25  1              01
        RCL RB          ; 26  ИПb            6B
        SUB             ; 27  −              11
        RCL RD          ; 28  ИПd            6D
        DIV             ; 29  ÷              13
        STO R3          ; 30  П3             43
        RCL R4          ; 31  ИП4            64
        CHS             ; 32  /-/            0B
        STO R4          ; 33  П4             44
        RCL R9          ; 34  ИП9            69
        CHS             ; 35  /-/            0B
        1               ; 36  1              01
        RCL RB          ; 37  ИПb            6B
        SUB             ; 38  −              11
        DIV             ; 39  ÷              13
        STO R6          ; 40  П6             46

L41:
        HALT            ; 41  С/П            50
        JMP L00         ; 42  БП 00          51 00

L44:
        RCL R1          ; 44  ИП1            61
        RCL R2          ; 45  ИП2            62
        SWAP            ; 46  ↔              14
        STO R2          ; 47  П2             42
        SWAP            ; 48  ↔              14
        STO R1          ; 49  П1             41
        1               ; 50  1              01
        RCL RC          ; 51  ИПc            6C
        ADD             ; 52  +              10
        RCL RD          ; 53  ИПd            6D
        DIV             ; 54  ÷              13
        STO R3          ; 55  П3             43
        RCL R9          ; 56  ИП9            69
        1               ; 57  1              01
        RCL RC          ; 58  ИПc            6C
        ADD             ; 59  +              10
        DIV             ; 60  ÷              13
        STO R6          ; 61  П6             46
        JMP L41         ; 62  БП 41          51 41
