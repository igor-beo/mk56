; Program 3.13: Inverse of a 2x2 matrix (result replaces the input)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.60-61 (book61.pdf pages 61-62)
; Input: a11=R7 a21=R8 / a12=R4 a22=R5.  Output: inverse in the same registers.
;
; Book example: A = |7 8; 4 5| -> A^-1 = |1,6666666 -2,6666666; -1,3333333 2,3333333|
; @reg R7=7 R4=8 R8=4 R5=5
; @run
; @expect R7=1.6666666
; @expect R4=-2.6666666
; @expect R8=-1.3333333
; @expect R5=2.3333333
;
; As printed:
;   00: ИП4 ИП8 × П2 ИП7 П9 ИП5 × ИП2 −
;   10: П2 ИП5 ↔ ÷ П7 ИП9 ИП2 ÷ П5 ИП4
;   20: ИП2 /-/ ÷ П4 ИП8 ИП2 /-/ ÷ П8 С/П
;   30: БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        RCL R4          ; 00  ИП4            64
        RCL R8          ; 01  ИП8            68
        MUL             ; 02  ×              12
        STO R2          ; 03  П2             42
        RCL R7          ; 04  ИП7            67
        STO R9          ; 05  П9             49
        RCL R5          ; 06  ИП5            65
        MUL             ; 07  ×              12
        RCL R2          ; 08  ИП2            62
        SUB             ; 09  −              11
        STO R2          ; 10  П2             42
        RCL R5          ; 11  ИП5            65
        SWAP            ; 12  ↔              14
        DIV             ; 13  ÷              13
        STO R7          ; 14  П7             47
        RCL R9          ; 15  ИП9            69
        RCL R2          ; 16  ИП2            62
        DIV             ; 17  ÷              13
        STO R5          ; 18  П5             45
        RCL R4          ; 19  ИП4            64
        RCL R2          ; 20  ИП2            62
        CHS             ; 21  /-/            0B
        DIV             ; 22  ÷              13
        STO R4          ; 23  П4             44
        RCL R8          ; 24  ИП8            68
        RCL R2          ; 25  ИП2            62
        CHS             ; 26  /-/            0B
        DIV             ; 27  ÷              13
        STO R8          ; 28  П8             48
        HALT            ; 29  С/П            50
        JMP L00         ; 30  БП 00          51 00
