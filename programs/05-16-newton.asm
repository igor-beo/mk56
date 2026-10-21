; Program 5.16: Newton's method x(n+1) = x(n) − F(x(n))/F'(x(n)), stopping when the
; correction is machine zero
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.89 (book61.pdf page 90)
; The book's listing is a template: ПД, then code computing F(x)/F'(x) from x = Rd
; ("..."), then ИПД ↔ − ПД FBx Fx=0 01 ИПД С/П. Input: x0 in X. Output: root in X.
; FBx recalls the correction F/F' (X1 holds the X operand of the preceding −).
; This instance uses the book's check example F(x) = x − sin x − 0,25,
; F/F' = (x − sin x − 0,25)/(1 − cos x): "ИПД В↑ Fsin − ИП9 − 1 ИПД Fcos − ÷",
; 0,25 = R9, angle mode radians.
; NOTE: the loop ends only when the correction is exactly 0. In the emulator
; x settles at 1,1712296 with a correction of -4,91e-8, below the last digit of
; x, so x never changes and the loop never ends. The real chip's sin differs in
; the last digits and gives F(x) = 0 exactly at 1,1712297. Matching that needs
; the chip's own algorithms (microcode-level emulation).
; @xfail depends on the real chip's sin digits
;
; Book example: x0 = b = 1,3 -> x = 1,1712297 (about 30 s)
; @angle rad
; @reg R9=0.25
; @input 1.3
; @expect X=1.1712297 tol=1e-6
;
; As printed:
;   00: Пd ИПd В↑ Fsin − ИП9 − 1 ИПd Fcos
;   10: − ÷ ИПd ↔ − Пd FBx Fx=0 01 ИПd
;   20: С/П
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
        JNZ L01         ; 17  Fx=0 01        5E 01
        RCL RD          ; 19  ИПd            6D
        HALT            ; 20  С/П            50
