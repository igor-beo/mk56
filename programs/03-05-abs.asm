; Program 3.5: Absolute value |x|
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.56 (book61.pdf page 57)
; The book gives only the fragment "... Fx<0 N /-/ ..." (N = address of the step
; after /-/), meant to be embedded in a larger program. This listing is the minimal
; instance: the fragment at 00, N = 03, followed by С/П.
; Input: x in X.  Output: |x| in X.
;
; expected values computed, not printed in the book
; @input -5.5
; @expect X=5.5
; @reset
; @input 7
; @expect X=7
;
; As printed:
;   00: Fx<0 03 /-/ С/П
;
; Each line: instruction ; address, keys, codes

        JGE L03         ; 00  Fx<0 03        5C 03
        CHS             ; 02  /-/            0B

L03:
        HALT            ; 03  С/П            50
