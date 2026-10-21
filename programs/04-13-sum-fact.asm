; Program 4.13: Sum of factorials S(n!) = 1! + 2! + ... + n!
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.67 (book61.pdf page 68)
; Input: n in X.  Output: S in X.
; R7 = n, R9 = running sum, R6 = i (advanced by КИП6, which increments R6 since
; 4 <= 6 <= 6; the value it loads is discarded), R8 = (i-1)!. Stops when i - n = 0.
;
; Book example: n = 4 -> S(n!) = 33
; @input 4
; @expect X=33
;
; As printed:
;   00: П7 0 П9 П6 1 П8 КИП6 ИП6 ИП8 ×
;   10: П8 ИП9 + П9 ИП6 ИП7 − Fx=0 06 ИП9
;   20: С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R7          ; 00  П7             47
        0               ; 01  0              00
        STO R9          ; 02  П9             49
        STO R6          ; 03  П6             46
        1               ; 04  1              01
        STO R8          ; 05  П8             48

L06:
        RCL (R6)        ; 06  КИП6           D6
        RCL R6          ; 07  ИП6            66
        RCL R8          ; 08  ИП8            68
        MUL             ; 09  ×              12
        STO R8          ; 10  П8             48
        RCL R9          ; 11  ИП9            69
        ADD             ; 12  +              10
        STO R9          ; 13  П9             49
        RCL R6          ; 14  ИП6            66
        RCL R7          ; 15  ИП7            67
        SUB             ; 16  −              11
        JNZ L06         ; 17  Fx=0 06        5E 06
        RCL R9          ; 19  ИП9            69
        HALT            ; 20  С/П            50
        JMP L00         ; 21  БП 00          51 00
