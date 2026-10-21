; Program 5.86: Up to 9000 non-repeating uniform random numbers, V(n+1) = D(11·V(n) + π)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.138 (book61.pdf page 139)
; Input: V0 < 1 in Y (here: key V0, С/П; the first digit lifts it into Y).
; Output: each С/П gives the next V in X.
;
; Book example (p.139): V0 = 0,002 -> 0,1635926; 0,9411112; 0,493816
; The third value depends on the last digit of 10,352223 + 3,1415926 = 13,4938156:
; the emulator truncates to 0,493815, the book prints 0,493816 (rounded on the
; chip, or a misprint); checked with a tolerance.
; @input 0.002
; @expect X=0.1635926
; @run
; @expect X=0.9411112
; @run
; @expect X=0.493816 tol=1e-5
;
; As printed:
;   00: 1 1 × Fπ + Пd КИПd ↔ ИПd −
;   10: С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        11              ; 00  1 1            01 01
        MUL             ; 02  ×              12
        PI              ; 03  Fπ             20
        ADD             ; 04  +              10
        STO RD          ; 05  Пd             4D
        RCL (RD)        ; 06  КИПd           DD
        SWAP            ; 07  ↔              14
        RCL RD          ; 08  ИПd            6D
        SUB             ; 09  −              11
        HALT            ; 10  С/П            50
        JMP L00         ; 11  БП 00          51 00
