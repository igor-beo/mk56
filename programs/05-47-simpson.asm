; Program 5.47: Numerical integration by Simpson's rule (parabolas), n = 2
;   I = h/3 [f(a) + 4f(a+h) + 2f(a+2h) + ... + 4f(b-h) + f(b)], h = (b - a)/2m
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.107 (book61.pdf page 108)
; Input: 2m (even) С/П, b С/П, a С/П. Output: I in X.
; Registers 0, A (h), B (x), C (sum) are used; the subroutine at 44 must return
; f(x) for x in Rb (the book's "..." between ПВ and В/О).
; This instance uses the book's first example (p.106, table 5.4) with x read from Rb:
; f(x) = x³/(x⁴ + 16) = "ИПВ ↑ Fx² × FBx Fx² ИП8 + ÷", 16 in R8, a = 1, b = 5.
; (The book prints that fragment with ИПА for programs 5.44-5.46, where x is in Ra.)
;
; Book results (table 5.4): m = 8 -> 0,9074589, m = 32 -> 0,9074541. The table's m
; matches 2m = 16 and 2m = 64 keyed in. After the result the program stops at 31;
; restart with В/О before the next run (@start 00 below).
; @reg R8=16
; @input 16
; @input 5
; @input 1
; @expect X=0.9074589 tol=1e-6
; @start 00
; @input 64
; @input 5
; @input 1
; @expect X=0.9074541 tol=1e-6
;
; As printed:
;   00: П0 С/П ПВ С/П ПА ПП 44 ПС ИПВ ИПА
;   10: ПВ − ИП0 ÷ ПА ПП 44 1 ПП 32
;   20: 4 ПП 32 2 БП 18 ИПС 3 ÷ ИПА
;   30: × С/П × ИПС + ПС FL0 40 БП 26
;   40: ИПВ ИПА + ПВ ИПВ ↑ Fx² × FBx Fx²
;   50: ИП8 + ÷ В/О
;
; Each line: instruction ; address, keys, codes

        STO R0          ; 00  П0             40
        HALT            ; 01  С/П            50
        STO RB          ; 02  Пb             4B
        HALT            ; 03  С/П            50
        STO RA          ; 04  Пa             4A
        CALL sub44      ; 05  ПП 44          53 44
        STO RC          ; 07  Пc             4C
        RCL RB          ; 08  ИПb            6B
        RCL RA          ; 09  ИПa            6A
        STO RB          ; 10  Пb             4B
        SUB             ; 11  −              11
        RCL R0          ; 12  ИП0            60
        DIV             ; 13  ÷              13
        STO RA          ; 14  Пa             4A
        CALL sub44      ; 15  ПП 44          53 44
        1               ; 17  1              01

L18:
        CALL sub32      ; 18  ПП 32          53 32
        4               ; 20  4              04
        CALL sub32      ; 21  ПП 32          53 32
        2               ; 23  2              02
        JMP L18         ; 24  БП 18          51 18

L26:
        RCL RC          ; 26  ИПc            6C
        3               ; 27  3              03
        DIV             ; 28  ÷              13
        RCL RA          ; 29  ИПa            6A
        MUL             ; 30  ×              12
        HALT            ; 31  С/П            50

sub32:
        MUL             ; 32  ×              12
        RCL RC          ; 33  ИПc            6C
        ADD             ; 34  +              10
        STO RC          ; 35  Пc             4C
        LOOP0 L40       ; 36  FL0 40         5D 40
        JMP L26         ; 38  БП 26          51 26

L40:
        RCL RB          ; 40  ИПb            6B
        RCL RA          ; 41  ИПa            6A
        ADD             ; 42  +              10
        STO RB          ; 43  Пb             4B

sub44:
        RCL RB          ; 44  ИПb            6B
        ENTER           ; 45  В↑             0E
        SQ              ; 46  Fx²            22
        MUL             ; 47  ×              12
        LASTX           ; 48  FBx            0F
        SQ              ; 49  Fx²            22
        RCL R8          ; 50  ИП8            68
        ADD             ; 51  +              10
        DIV             ; 52  ÷              13
        RTN             ; 53  В/О            52
