; Program 3.19: Permutations P(n) = n!, arrangements A(n,m) = n!/(n − m)!
;   and combinations C(n,m) = n!/((n − m)! m!)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.62 (book61.pdf page 63)
; Input: n in X, С/П; m in X, С/П.
; Output: C(n,m) in X and Rc; m! in R4, n! in R5, (n − m)! in R6, A(n,m) in Ra.
; Factorial subroutine at 26 (R0 counter); needs n > m >= 1 (FL0 with R0 = 0 does not stop).
; Steps 18 and 21 are printed with the "+"-like glyph; both are ÷ (A = n!/(n−m)!, C = A/m!).
;
; Book example: n = 10, m = 5 -> C = 252, A = 30240, P = 3628800 (about 30 s)
; @input 10
; @input 5
; @expect X=252
; @expect Rc=252
; @expect Ra=30240
; @expect R5=3628800
; @expect R4=120
; @expect R6=120
;
; As printed:
;   00: П9 С/П П8 ПП 26 П4 ИП9 ПП 26 П5
;   10: ИП9 ИП8 − ПП 26 П6 ИП5 ↔ ÷ Пa
;   20: ИП4 ÷ Пc С/П БП 00 П0 1 ИП0 ×
;   30: FL0 28 В/О
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        HALT            ; 01  С/П            50
        STO R8          ; 02  П8             48
        CALL sub26      ; 03  ПП 26          53 26
        STO R4          ; 05  П4             44
        RCL R9          ; 06  ИП9            69
        CALL sub26      ; 07  ПП 26          53 26
        STO R5          ; 09  П5             45
        RCL R9          ; 10  ИП9            69
        RCL R8          ; 11  ИП8            68
        SUB             ; 12  −              11
        CALL sub26      ; 13  ПП 26          53 26
        STO R6          ; 15  П6             46
        RCL R5          ; 16  ИП5            65
        SWAP            ; 17  ↔              14
        DIV             ; 18  ÷              13
        STO RA          ; 19  Пa             4A
        RCL R4          ; 20  ИП4            64
        DIV             ; 21  ÷              13
        STO RC          ; 22  Пc             4C
        HALT            ; 23  С/П            50
        JMP L00         ; 24  БП 00          51 00

sub26:
        STO R0          ; 26  П0             40
        1               ; 27  1              01

L28:
        RCL R0          ; 28  ИП0            60
        MUL             ; 29  ×              12
        LOOP0 L28       ; 30  FL0 28         5D 28
        RTN             ; 32  В/О            52
