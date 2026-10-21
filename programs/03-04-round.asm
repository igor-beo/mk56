; Program 3.4: Round x of any sign to a step eps = 1*10^-n (last digit kept if the
; next digit is < 5, incremented if it is > 5)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.56 (book61.pdf page 57)
; Input: eps in Rd, x in X.  Output: rounded x in X.  R9 = sign(x).
;
; Book example: x = ±12,345678, eps = 1*10^-2 -> ±12,35;  x = ±12,344999 -> ±12,34
; @reg Rd=0.01
; @input 12.345678
; @expect X=12.35
; @reset
; @reg Rd=0.01
; @input -12.345678
; @expect X=-12.35
; @reset
; @reg Rd=0.01
; @input 12.344999
; @expect X=12.34
; @reset
; @reg Rd=0.01
; @input -12.344999
; @expect X=-12.34
;
; As printed:
;   00: В↑ Fx<0 04 /-/ ÷ П9 FBx ИПd ÷ Пc
;   10: КИПc ↔ ИПc − F1/x 2 − Fx<0 23 ИПc
;   20: 1 + Пc ИПc ИПd × ИП9 × С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        JGE L04         ; 01  Fx<0 04        5C 04
        CHS             ; 03  /-/            0B

L04:
        DIV             ; 04  ÷              13
        STO R9          ; 05  П9             49
        LASTX           ; 06  FBx            0F
        RCL RD          ; 07  ИПd            6D
        DIV             ; 08  ÷              13
        STO RC          ; 09  Пc             4C
        RCL (RC)        ; 10  КИПc           DC
        SWAP            ; 11  ↔              14
        RCL RC          ; 12  ИПc            6C
        SUB             ; 13  −              11
        INV             ; 14  F1/x           23
        2               ; 15  2              02
        SUB             ; 16  −              11
        JGE L23         ; 17  Fx<0 23        5C 23
        RCL RC          ; 19  ИПc            6C
        1               ; 20  1              01
        ADD             ; 21  +              10
        STO RC          ; 22  Пc             4C

L23:
        RCL RC          ; 23  ИПc            6C
        RCL RD          ; 24  ИПd            6D
        MUL             ; 25  ×              12
        RCL R9          ; 26  ИП9            69
        MUL             ; 27  ×              12
        HALT            ; 28  С/П            50
