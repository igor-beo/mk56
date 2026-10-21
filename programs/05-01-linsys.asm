; Program 5.1: System of n <= 4 linear equations sum_j a_ij x_j = a_(i,n+1)
;   (b_i = a_(i,n+1)) by optimal elimination
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.79 (book61.pdf page 80)
; Input: n in R0; then, from address 00, every coefficient row by row
;   (a_i1 ... a_in, b_i), each keyed into X and followed by С/П (intermediate
;   displays are to be ignored).
; Output: x1 in X; x1 -> Rd, x2 -> Rc, x3 -> Rb, x4 -> Ra.
; Uses all 98 steps. "F," in the book is F⟳ (stack rotation).
;
; Book example (n = 3):
;   | 4     0,24  -0,08 |   | 8  |
;   | 0,09  3     -0,15 | x = | 9  |
;   | 0,04  -0,08  4    |   | 20 |
;   -> x1 = 1,9091983, x2 = 3,1949644, x3 = 5,0448073 (about 2 min)
; @reg R0=3
; @input 4
; @input 0.24
; @input -0.08
; @input 8
; @input 0.09
; @input 3
; @input -0.15
; @input 9
; @input 0.04
; @input -0.08
; @input 4
; @input 20
; @expect X=1.9091983
; @expect Rd=1.9091983
; @expect Rc=3.1949644
; @expect Rb=5.0448073
;
; As printed:
;   00: П4 1 4 П2 ИП0 П1 С/П ИП4 ÷ КП2
;   10: FL1 06 1 4 П3 ИП0 П1 FL1 23 КИП3
;   20: С/П БП 19 Cx КП2 FL1 24 КП2 ИП0 ИП2
;   30: + П1 П2 ИП3 − Fx≠0 42 С/П ПП 84
;   40: БП 28 КИП0 ИП0 П3 С/П КИП2 − П4 С/П
;   50: КИП2 − ИП4 ÷ КП1 FL3 49 ИП1 ИП0 +
;   60: П3 1 4 П1 П2 КИП1 /-/ ПП 84 ИП3
;   70: + П3 ИП1 − Fx=0 65 ИП0 П1 КИП3 КП2
;   80: FL1 78 БП 12 ИП0 ↔ В↑ КИП3 × КИП1
;   90: + КП2 F⟳ FL0 86 F⟳ П0 В/О
;
; Each line: instruction ; address, keys, codes

        STO R4          ; 00  П4             44
        14              ; 01  1 4            01 04
        STO R2          ; 03  П2             42
        RCL R0          ; 04  ИП0            60
        STO R1          ; 05  П1             41

L06:
        HALT            ; 06  С/П            50
        RCL R4          ; 07  ИП4            64
        DIV             ; 08  ÷              13
        STO (R2)        ; 09  КП2            B2
        LOOP1 L06       ; 10  FL1 06         5B 06

L12:
        14              ; 12  1 4            01 04
        STO R3          ; 14  П3             43
        RCL R0          ; 15  ИП0            60
        STO R1          ; 16  П1             41
        LOOP1 L23       ; 17  FL1 23         5B 23

L19:
        RCL (R3)        ; 19  КИП3           D3
        HALT            ; 20  С/П            50
        JMP L19         ; 21  БП 19          51 19

L23:
        CLX             ; 23  Cx             0D

L24:
        STO (R2)        ; 24  КП2            B2
        LOOP1 L24       ; 25  FL1 24         5B 24
        STO (R2)        ; 27  КП2            B2

L28:
        RCL R0          ; 28  ИП0            60
        RCL R2          ; 29  ИП2            62
        ADD             ; 30  +              10
        STO R1          ; 31  П1             41
        STO R2          ; 32  П2             42
        RCL R3          ; 33  ИП3            63
        SUB             ; 34  −              11
        JZ L42          ; 35  Fx≠0 42        57 42
        HALT            ; 37  С/П            50
        CALL sub84      ; 38  ПП 84          53 84
        JMP L28         ; 40  БП 28          51 28

L42:
        RCL (R0)        ; 42  КИП0           D0
        RCL R0          ; 43  ИП0            60
        STO R3          ; 44  П3             43
        HALT            ; 45  С/П            50
        RCL (R2)        ; 46  КИП2           D2
        SUB             ; 47  −              11
        STO R4          ; 48  П4             44

L49:
        HALT            ; 49  С/П            50
        RCL (R2)        ; 50  КИП2           D2
        SUB             ; 51  −              11
        RCL R4          ; 52  ИП4            64
        DIV             ; 53  ÷              13
        STO (R1)        ; 54  КП1            B1
        LOOP3 L49       ; 55  FL3 49         5A 49
        RCL R1          ; 57  ИП1            61
        RCL R0          ; 58  ИП0            60
        ADD             ; 59  +              10
        STO R3          ; 60  П3             43
        14              ; 61  1 4            01 04
        STO R1          ; 63  П1             41
        STO R2          ; 64  П2             42

L65:
        RCL (R1)        ; 65  КИП1           D1
        CHS             ; 66  /-/            0B
        CALL sub84      ; 67  ПП 84          53 84
        RCL R3          ; 69  ИП3            63
        ADD             ; 70  +              10
        STO R3          ; 71  П3             43
        RCL R1          ; 72  ИП1            61
        SUB             ; 73  −              11
        JNZ L65         ; 74  Fx=0 65        5E 65
        RCL R0          ; 76  ИП0            60
        STO R1          ; 77  П1             41

L78:
        RCL (R3)        ; 78  КИП3           D3
        STO (R2)        ; 79  КП2            B2
        LOOP1 L78       ; 80  FL1 78         5B 78
        JMP L12         ; 82  БП 12          51 12

sub84:
        RCL R0          ; 84  ИП0            60
        SWAP            ; 85  ↔              14

L86:
        ENTER           ; 86  В↑             0E
        RCL (R3)        ; 87  КИП3           D3
        MUL             ; 88  ×              12
        RCL (R1)        ; 89  КИП1           D1
        ADD             ; 90  +              10
        STO (R2)        ; 91  КП2            B2
        ROT             ; 92  F⟳             25
        LOOP0 L86       ; 93  FL0 86         5D 86
        ROT             ; 95  F⟳             25
        STO R0          ; 96  П0             40
        RTN             ; 97  В/О            52
