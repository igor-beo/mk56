; Program 5.17: Newton's method, stopping when (x(n+1) − x(n))² < eps²
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.89 (book61.pdf page 90)
; The book's listing is a template: ПД, then code computing F(x)/F'(x) from x = Rd
; ("..."), then ИПД ↔ − ПД FBx Fx² ИПС − Fx<0 01 ИПД С/П.
; Input: eps² in Rc, x0 in X. Output: root in X.
; This instance uses the book's check example (p.89): F/F' = (x − sin x − 0,25)/(1 − cos x)
; = "ИПД В↑ Fsin − ИП9 − 1 ИПД Fcos − ÷", 0,25 = R9, angle mode radians.
;
; The book gives the root 1,1712297 for this equation (with program 5.16) but no
; eps for 5.17; eps² = 1*10^-10 is our choice.
; expected value computed, not printed in the book (for this eps)
; @angle rad
; @reg R9=0.25 Rc=1e-10
; @input 1.3
; @expect X=1.1712297 tol=1e-6
;
; As printed:
;   00: Пd ИПd В↑ Fsin − ИП9 − 1 ИПd Fcos
;   10: − ÷ ИПd ↔ − Пd FBx Fx² ИПc −
;   20: Fx<0 01 ИПd С/П
;
; Each line: instruction ; address, keys, codes

        STO RD          ; 00  Пd             4D

L01:
        RCL RD          ; 01  ИПd            6D
        ENTER           ; 02  В↑             0E
        SIN             ; 03  Fsin           1C
        SUB             ; 04  −              11
        RCL R9          ; 05  ИП9            69
        SUB             ; 06  −              11
        1               ; 07  1              01
        RCL RD          ; 08  ИПd            6D
        COS             ; 09  Fcos           1D
        SUB             ; 10  −              11
        DIV             ; 11  ÷              13
        RCL RD          ; 12  ИПd            6D
        SWAP            ; 13  ↔              14
        SUB             ; 14  −              11
        STO RD          ; 15  Пd             4D
        LASTX           ; 16  FBx            0F
        SQ              ; 17  Fx²            22
        RCL RC          ; 18  ИПc            6C
        SUB             ; 19  −              11
        JGE L01         ; 20  Fx<0 01        5C 01
        RCL RD          ; 22  ИПd            6D
        HALT            ; 23  С/П            50
