; Program 5.88: Normal random numbers r(n) = R + R''(n)·σ, where
;   R''(n) = sqrt(2 ln(1/V(n))) · sin(2π V(n−1)) and V(n) = D(37 V(n−1)) by (5.69)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.139 (book61.pdf page 140)
; Input: V0 in R0, mean R in Rb, σ in Rc; angle switch at Р (radians).
; Output: each С/П gives the next r(n).
;
; Book example: V0 = 0,1234567, R = 1, σ = 0,1 -> 1,0744877; 0,8771866; 1,0096652
; @angle rad
; @reg R0=0.1234567 Rb=1 Rc=0.1
; @run
; @expect X=1.0744877
; @run
; @expect X=0.8771866
; @run
; @expect X=1.0096652
;
; As printed:
;   00: ИП0 3 7 × 1 + Пd КИПd ↔ ИПd
;   10: − ИП0 2 × Fπ × Fsin ↔ П0 F1/x
;   20: Fln 2 × F√ × ИПc × ИПb + С/П
;   30: БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        RCL R0          ; 00  ИП0            60
        37              ; 01  3 7            03 07
        MUL             ; 03  ×              12
        1               ; 04  1              01
        ADD             ; 05  +              10
        STO RD          ; 06  Пd             4D
        RCL (RD)        ; 07  КИПd           DD
        SWAP            ; 08  ↔              14
        RCL RD          ; 09  ИПd            6D
        SUB             ; 10  −              11
        RCL R0          ; 11  ИП0            60
        2               ; 12  2              02
        MUL             ; 13  ×              12
        PI              ; 14  Fπ             20
        MUL             ; 15  ×              12
        SIN             ; 16  Fsin           1C
        SWAP            ; 17  ↔              14
        STO R0          ; 18  П0             40
        INV             ; 19  F1/x           23
        LN              ; 20  Fln            18
        2               ; 21  2              02
        MUL             ; 22  ×              12
        SQRT            ; 23  F√             21
        MUL             ; 24  ×              12
        RCL RC          ; 25  ИПc            6C
        MUL             ; 26  ×              12
        RCL RB          ; 27  ИПb            6B
        ADD             ; 28  +              10
        HALT            ; 29  С/П            50
        JMP L00         ; 30  БП 00          51 00
