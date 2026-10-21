; Program 4.20: Value of the Laguerre polynomial Ln(x) by the recurrence
;   L0 = 1, L1 = 1 − x, L(i+1) = [(2i + 1 − x)Li − i·L(i-1)]/(i + 1)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.69-70 (book61.pdf pages 70-71)
; Input: n in Rd (n >= 2), x in X.  Output: Ln(x) in X.
;
; Book example: x = 3: L2(3) = −0,5; L3(3) = 1; L4(3) = 1,375
; @reg Rd=2
; @input 3
; @expect X=-0.5
; @reg Rd=3
; @input 3
; @expect X=1
; @reg Rd=4
; @input 3
; @expect X=1.375
;
; As printed:
;   00: П7 1 ↔ − П9 1 П8 П6 ИП6 ИП8
;   10: /-/ × ИП6 2 × 1 + ИП7 − ИП9
;   20: П8 × + ИП6 1 + П6 ÷ П9 ИП6
;   30: ИПd − Fx≥0 08 ИП9 С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R7          ; 00  П7             47
        1               ; 01  1              01
        SWAP            ; 02  ↔              14
        SUB             ; 03  −              11
        STO R9          ; 04  П9             49
        1               ; 05  1              01
        STO R8          ; 06  П8             48
        STO R6          ; 07  П6             46

L08:
        RCL R6          ; 08  ИП6            66
        RCL R8          ; 09  ИП8            68
        CHS             ; 10  /-/            0B
        MUL             ; 11  ×              12
        RCL R6          ; 12  ИП6            66
        2               ; 13  2              02
        MUL             ; 14  ×              12
        1               ; 15  1              01
        ADD             ; 16  +              10
        RCL R7          ; 17  ИП7            67
        SUB             ; 18  −              11
        RCL R9          ; 19  ИП9            69
        STO R8          ; 20  П8             48
        MUL             ; 21  ×              12
        ADD             ; 22  +              10
        RCL R6          ; 23  ИП6            66
        1               ; 24  1              01
        ADD             ; 25  +              10
        STO R6          ; 26  П6             46
        DIV             ; 27  ÷              13
        STO R9          ; 28  П9             49
        RCL R6          ; 29  ИП6            66
        RCL RD          ; 30  ИПd            6D
        SUB             ; 31  −              11
        JLT L08         ; 32  Fx≥0 08        59 08
        RCL R9          ; 34  ИП9            69
        HALT            ; 35  С/П            50
        JMP L00         ; 36  БП 00          51 00
