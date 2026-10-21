; Program 4.11: Polynomial of degree n <= 10 of a complex variable Z = a + jb
;   by Horner's scheme
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.66 (book61.pdf page 67)
; Input: a0..a9 = R0..R9, a10 = Ra; a in Y, b in X.
; Output: P(Z) = c + jd: c in X, d in Y (d is also left in Rd).
; Subroutine at 42 performs one complex Horner step.
;
; Book example: P(Z) = 1 + Z + 2Z² + ... + 8Z⁸ (a9 = a10 = 0), Z = 1 + j·1:
;   P(Z) = 144 − j·113
; @reg R0=1 R1=1 R2=2 R3=3 R4=4 R5=5 R6=6 R7=7 R8=8 R9=0 Ra=0
; @stack Y=1 X=1
; @run
; @expect X=144
; @expect Rd=-113
;
; As printed:
;   00: Пc ↔ Пb ИПa × ИП9 + ИПc ИПa ×
;   10: Пd ↔ ИП8 ПП 42 ИП7 ПП 42 ИП6 ПП 42
;   21: ИП5 ПП 42 ИП4 ПП 42 ИП3 ПП 42
;   30: ИП2 ПП 42 ИП1 ПП 42 ИП0 ПП 42 С/П
;   40: БП 00 ИПd ИПc × − ↔ ИПb × +
;   50: ↔ ИПc × ИПd ИПb × + Пd ↔ В/О
;
; Each line: instruction ; address, keys, codes

L00:
        STO RC          ; 00  Пc             4C
        SWAP            ; 01  ↔              14
        STO RB          ; 02  Пb             4B
        RCL RA          ; 03  ИПa            6A
        MUL             ; 04  ×              12
        RCL R9          ; 05  ИП9            69
        ADD             ; 06  +              10
        RCL RC          ; 07  ИПc            6C
        RCL RA          ; 08  ИПa            6A
        MUL             ; 09  ×              12
        STO RD          ; 10  Пd             4D
        SWAP            ; 11  ↔              14
        RCL R8          ; 12  ИП8            68
        CALL sub42      ; 13  ПП 42          53 42
        RCL R7          ; 15  ИП7            67
        CALL sub42      ; 16  ПП 42          53 42
        RCL R6          ; 18  ИП6            66
        CALL sub42      ; 19  ПП 42          53 42
        RCL R5          ; 21  ИП5            65
        CALL sub42      ; 22  ПП 42          53 42
        RCL R4          ; 24  ИП4            64
        CALL sub42      ; 25  ПП 42          53 42
        RCL R3          ; 27  ИП3            63
        CALL sub42      ; 28  ПП 42          53 42
        RCL R2          ; 30  ИП2            62
        CALL sub42      ; 31  ПП 42          53 42
        RCL R1          ; 33  ИП1            61
        CALL sub42      ; 34  ПП 42          53 42
        RCL R0          ; 36  ИП0            60
        CALL sub42      ; 37  ПП 42          53 42
        HALT            ; 39  С/П            50
        JMP L00         ; 40  БП 00          51 00

sub42:
        RCL RD          ; 42  ИПd            6D
        RCL RC          ; 43  ИПc            6C
        MUL             ; 44  ×              12
        SUB             ; 45  −              11
        SWAP            ; 46  ↔              14
        RCL RB          ; 47  ИПb            6B
        MUL             ; 48  ×              12
        ADD             ; 49  +              10
        SWAP            ; 50  ↔              14
        RCL RC          ; 51  ИПc            6C
        MUL             ; 52  ×              12
        RCL RD          ; 53  ИПd            6D
        RCL RB          ; 54  ИПb            6B
        MUL             ; 55  ×              12
        ADD             ; 56  +              10
        STO RD          ; 57  Пd             4D
        SWAP            ; 58  ↔              14
        RTN             ; 59  В/О            52
