; Program 3.2: Fractional part of x (0 < x < 10^8)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.56 (book61.pdf page 57)
; Input: x in X.  Output: frac(x) in X.
; The book writes the register as M (7, 8, 9, A, B, C or Д); this listing uses M = 7.
; 1 is added first so that КИП7 never sees a value below 1.
; The book prints no worked example for this program.
;
; expected value computed, not printed in the book
; @input 123.4567
; @expect X=0.4567 tol=1e-5
;
; As printed:
;   00: В↑ 1 + П7 КИП7 ↔ ИП7 − С/П
;
; Each line: instruction ; address, keys, codes

        ENTER           ; 00  В↑             0E
        1               ; 01  1              01
        ADD             ; 02  +              10
        STO R7          ; 03  П7             47
        RCL (R7)        ; 04  КИП7           D7
        SWAP            ; 05  ↔              14
        RCL R7          ; 06  ИП7            67
        SUB             ; 07  −              11
        HALT            ; 08  С/П            50
