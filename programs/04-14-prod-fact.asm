; Program 4.14: Product of factorials P(n!) = 1!·2!·3!·...·n!
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.67 (book61.pdf page 68)
; Input: n in X.  Output: P in X.  Same structure as program 4.13 with × in place
; of + at step 12.
;
; Book example: n = 4 -> P(n!) = 288
; @input 4
; @expect X=288
;
; As printed:
;   00: П7 0 П6 1 П8 П9 КИП6 ИП6 ИП8 ×
;   10: П8 ИП9 × П9 ИП6 ИП7 − Fx=0 06 ИП9
;   20: С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R7          ; 00  П7             47
        0               ; 01  0              00
        STO R6          ; 02  П6             46
        1               ; 03  1              01
        STO R8          ; 04  П8             48
        STO R9          ; 05  П9             49

L06:
        RCL (R6)        ; 06  КИП6           D6
        RCL R6          ; 07  ИП6            66
        RCL R8          ; 08  ИП8            68
        MUL             ; 09  ×              12
        STO R8          ; 10  П8             48
        RCL R9          ; 11  ИП9            69
        MUL             ; 12  ×              12
        STO R9          ; 13  П9             49
        RCL R6          ; 14  ИП6            66
        RCL R7          ; 15  ИП7            67
        SUB             ; 16  −              11
        JNZ L06         ; 17  Fx=0 06        5E 06
        RCL R9          ; 19  ИП9            69
        HALT            ; 20  С/П            50
        JMP L00         ; 21  БП 00          51 00
