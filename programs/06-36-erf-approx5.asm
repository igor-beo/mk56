; Program 6.36: Φ(x) = erf(x) by the approximation (Abramowitz–Stegun 7.1.26),
;   error at most 1,5·10⁻⁷:
;   Φ(x) = 1 − (a1λ + a2λ² + a3λ³ + a4λ⁴ + a5λ⁵)/exp(x²),  λ = 1/(1 + a6·x)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.169 (book61.pdf page 170)
; Input: a1 = 0,2548295 in R1, a2 = −0,28449673 in R2, a3 = 1,4214137 in R3,
;   a4 = −1,453152 in R4, a5 = 1,0614054 in R5, a6 = 0,3275911 in R6; x in X.
; Output: Φ(x) in X.
; Horner loop: КИП0 pre-decrements R0 from 5 and fetches R4..R1; the last pass
; fetches R0 = 0, which ends the loop and adds nothing.
;
; Book examples: Φ(0,1) = 0,1124632; Φ(2) = 0,9953221
; @reg R1=0.2548295 R2=-0.28449673 R3=1.4214137 R4=-1.453152 R5=1.0614054 R6=0.3275911
; @input 0.1
; @expect X=0.1124632
; @input 2
; @expect X=0.9953221
;
; As printed:
;   00: П9 ИП6 × 1 + F1/x П8 5 П0 ИП5
;   10: В↑ ↔ ИП8 × КИП0 + ИП0 Fx=0 11 ↔
;   20: ИП9 Fx² Feˣ ÷ 1 ↔ − С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        RCL R6          ; 01  ИП6            66
        MUL             ; 02  ×              12
        1               ; 03  1              01
        ADD             ; 04  +              10
        INV             ; 05  F1/x           23
        STO R8          ; 06  П8             48
        5               ; 07  5              05
        STO R0          ; 08  П0             40
        RCL R5          ; 09  ИП5            65
        ENTER           ; 10  В↑             0E

L11:
        SWAP            ; 11  ↔              14
        RCL R8          ; 12  ИП8            68
        MUL             ; 13  ×              12
        RCL (R0)        ; 14  КИП0           D0
        ADD             ; 15  +              10
        RCL R0          ; 16  ИП0            60
        JNZ L11         ; 17  Fx=0 11        5E 11
        SWAP            ; 19  ↔              14
        RCL R9          ; 20  ИП9            69
        SQ              ; 21  Fx²            22
        EXP             ; 22  Feˣ            16
        DIV             ; 23  ÷              13
        1               ; 24  1              01
        SWAP            ; 25  ↔              14
        SUB             ; 26  −              11
        HALT            ; 27  С/П            50
        JMP L00         ; 28  БП 00          51 00
