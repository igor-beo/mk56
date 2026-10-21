; Program 3.12: Product of a 3x4 matrix A and a 4x2 matrix B
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.59-60 (book61.pdf pages 60-61)
; Input: b11=R7 b12=R8 / b21=R4 b22=R5 / b31=R1 b32=R2 / b41=R0 b42=Ra.
; С/П shows 1: key a11, С/П shows 2: key a12, ... row by row (prompts 1 2 3 4);
; after the last element the display shows 0.
; Output: c11=R9 c12=Rb / c21=R6 c22=Rc / c31=R3 c32=Rd.
; "F," in the book is F⟳ (stack rotation).
;
; Book example: A = |2 0 3 1; 5 1 2 0; 0 0 4 1|, B = |1 3; 2 1; 4 0; 3 5|
;   -> C = |17 11; 15 16; 19 5|
; @reg R7=1 R8=3 R4=2 R5=1 R1=4 R2=0 R0=3 Ra=5
; @run
; @expect X=1
; @input 2
; @expect X=2
; @input 0
; @expect X=3
; @input 3
; @expect X=4
; @input 1
; @expect X=1
; @input 5
; @input 1
; @input 2
; @input 0
; @expect X=1
; @input 0
; @input 0
; @input 4
; @input 1
; @expect X=0
; @expect R9=17
; @expect Rb=11
; @expect R6=15
; @expect Rc=16
; @expect R3=19
; @expect Rd=5
;
; As printed:
;   00: ПП 16 ИП3 П9 ИПd Пb ПП 16 ИП3 П6
;   10: ИПd Пc ПП 16 0 С/П 1 С/П В↑ ИП7
;   20: × П3 F⟳ ИП8 × Пd 2 С/П В↑ ИП4
;   30: × ИП3 + П3 F⟳ ИП5 × ИПd + Пd
;   40: 3 С/П В↑ ИП1 × ИП3 + П3 F⟳ ИП2
;   50: × ИПd + Пd 4 С/П В↑ ИП0 × ИП3
;   60: + П3 F⟳ ИПa × ИПd + Пd В/О
;
; Each line: instruction ; address, keys, codes

        CALL sub16      ; 00  ПП 16          53 16
        RCL R3          ; 02  ИП3            63
        STO R9          ; 03  П9             49
        RCL RD          ; 04  ИПd            6D
        STO RB          ; 05  Пb             4B
        CALL sub16      ; 06  ПП 16          53 16
        RCL R3          ; 08  ИП3            63
        STO R6          ; 09  П6             46
        RCL RD          ; 10  ИПd            6D
        STO RC          ; 11  Пc             4C
        CALL sub16      ; 12  ПП 16          53 16
        0               ; 14  0              00
        HALT            ; 15  С/П            50

sub16:
        1               ; 16  1              01
        HALT            ; 17  С/П            50
        ENTER           ; 18  В↑             0E
        RCL R7          ; 19  ИП7            67
        MUL             ; 20  ×              12
        STO R3          ; 21  П3             43
        ROT             ; 22  F⟳             25
        RCL R8          ; 23  ИП8            68
        MUL             ; 24  ×              12
        STO RD          ; 25  Пd             4D
        2               ; 26  2              02
        HALT            ; 27  С/П            50
        ENTER           ; 28  В↑             0E
        RCL R4          ; 29  ИП4            64
        MUL             ; 30  ×              12
        RCL R3          ; 31  ИП3            63
        ADD             ; 32  +              10
        STO R3          ; 33  П3             43
        ROT             ; 34  F⟳             25
        RCL R5          ; 35  ИП5            65
        MUL             ; 36  ×              12
        RCL RD          ; 37  ИПd            6D
        ADD             ; 38  +              10
        STO RD          ; 39  Пd             4D
        3               ; 40  3              03
        HALT            ; 41  С/П            50
        ENTER           ; 42  В↑             0E
        RCL R1          ; 43  ИП1            61
        MUL             ; 44  ×              12
        RCL R3          ; 45  ИП3            63
        ADD             ; 46  +              10
        STO R3          ; 47  П3             43
        ROT             ; 48  F⟳             25
        RCL R2          ; 49  ИП2            62
        MUL             ; 50  ×              12
        RCL RD          ; 51  ИПd            6D
        ADD             ; 52  +              10
        STO RD          ; 53  Пd             4D
        4               ; 54  4              04
        HALT            ; 55  С/П            50
        ENTER           ; 56  В↑             0E
        RCL R0          ; 57  ИП0            60
        MUL             ; 58  ×              12
        RCL R3          ; 59  ИП3            63
        ADD             ; 60  +              10
        STO R3          ; 61  П3             43
        ROT             ; 62  F⟳             25
        RCL RA          ; 63  ИПa            6A
        MUL             ; 64  ×              12
        RCL RD          ; 65  ИПd            6D
        ADD             ; 66  +              10
        STO RD          ; 67  Пd             4D
        RTN             ; 68  В/О            52
