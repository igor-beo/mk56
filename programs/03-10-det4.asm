; Program 3.10: Determinant of order 4 by expansion along the first row:
; det = a1*A1 - b1*B1 + c1*C1 - d1*D1 (A1..D1 are the 3x3 minors)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.58 (book61.pdf page 59)
; Input: rows 2-4 in registers:
;   a2=Ra b2=R7 c2=R8 d2=R9 / a3=Rb b3=R4 c3=R5 d3=R6 / a4=Rc b4=R1 c4=R2 d4=R3.
; С/П shows A1; enter a1, С/П shows B1; enter -b1 -> C1; enter c1 -> D1;
; enter -d1 -> det. Subroutine at 54 is the 3x3 determinant of program 3.9.
;
; Book example: |6 3 0 3; 4 4 2 1; 0 4 4 2; 7 7 8 5|
;   A1 = 8, B1 = 16, C1 = 52, D1 = 72; enter a1 = 6, -b1 = -3, c1 = 0, -d1 = -3;
;   det = -216
; @reg Ra=4 R7=4 R8=2 R9=1 Rb=0 R4=4 R5=4 R6=2 Rc=7 R1=7 R2=8 R3=5
; @run
; @expect X=8
; @input 6
; @expect X=16
; @input -3
; @expect X=52
; @input 0
; @expect X=72
; @input -3
; @expect X=-216
;
; As printed:
;   00: Cx П0 ПП 54 ИП7 Пa ↔ П7 ИПb ИП4
;   10: Пb ↔ П4 ИПc ИП1 Пc ↔ П1 ПП 54
;   20: ИП8 Пa ↔ П8 ИПb ИП5 Пb ↔ П5 ИПc
;   30: ИП2 Пc ↔ П2 ПП 54 ИП9 Пa ↔ П9
;   40: ИПb ИП6 Пb ↔ П6 ИПc ИП3 Пc ↔ П3
;   50: ПП 54 ИП0 С/П ИП4 ИП2 × ИП1 ИП5 ×
;   60: − ИП9 × ИП1 ИП8 × ИП7 ИП2 × −
;   70: ИП6 × + ИП7 ИП5 × ИП4 ИП8 × −
;   80: ИП3 × + С/П × ИП0 + П0 ИПa В/О
;
; Each line: instruction ; address, keys, codes

        CLX             ; 00  Cx             0D
        STO R0          ; 01  П0             40
        CALL sub54      ; 02  ПП 54          53 54
        RCL R7          ; 04  ИП7            67
        STO RA          ; 05  Пa             4A
        SWAP            ; 06  ↔              14
        STO R7          ; 07  П7             47
        RCL RB          ; 08  ИПb            6B
        RCL R4          ; 09  ИП4            64
        STO RB          ; 10  Пb             4B
        SWAP            ; 11  ↔              14
        STO R4          ; 12  П4             44
        RCL RC          ; 13  ИПc            6C
        RCL R1          ; 14  ИП1            61
        STO RC          ; 15  Пc             4C
        SWAP            ; 16  ↔              14
        STO R1          ; 17  П1             41
        CALL sub54      ; 18  ПП 54          53 54
        RCL R8          ; 20  ИП8            68
        STO RA          ; 21  Пa             4A
        SWAP            ; 22  ↔              14
        STO R8          ; 23  П8             48
        RCL RB          ; 24  ИПb            6B
        RCL R5          ; 25  ИП5            65
        STO RB          ; 26  Пb             4B
        SWAP            ; 27  ↔              14
        STO R5          ; 28  П5             45
        RCL RC          ; 29  ИПc            6C
        RCL R2          ; 30  ИП2            62
        STO RC          ; 31  Пc             4C
        SWAP            ; 32  ↔              14
        STO R2          ; 33  П2             42
        CALL sub54      ; 34  ПП 54          53 54
        RCL R9          ; 36  ИП9            69
        STO RA          ; 37  Пa             4A
        SWAP            ; 38  ↔              14
        STO R9          ; 39  П9             49
        RCL RB          ; 40  ИПb            6B
        RCL R6          ; 41  ИП6            66
        STO RB          ; 42  Пb             4B
        SWAP            ; 43  ↔              14
        STO R6          ; 44  П6             46
        RCL RC          ; 45  ИПc            6C
        RCL R3          ; 46  ИП3            63
        STO RC          ; 47  Пc             4C
        SWAP            ; 48  ↔              14
        STO R3          ; 49  П3             43
        CALL sub54      ; 50  ПП 54          53 54
        RCL R0          ; 52  ИП0            60
        HALT            ; 53  С/П            50

sub54:
        RCL R4          ; 54  ИП4            64
        RCL R2          ; 55  ИП2            62
        MUL             ; 56  ×              12
        RCL R1          ; 57  ИП1            61
        RCL R5          ; 58  ИП5            65
        MUL             ; 59  ×              12
        SUB             ; 60  −              11
        RCL R9          ; 61  ИП9            69
        MUL             ; 62  ×              12
        RCL R1          ; 63  ИП1            61
        RCL R8          ; 64  ИП8            68
        MUL             ; 65  ×              12
        RCL R7          ; 66  ИП7            67
        RCL R2          ; 67  ИП2            62
        MUL             ; 68  ×              12
        SUB             ; 69  −              11
        RCL R6          ; 70  ИП6            66
        MUL             ; 71  ×              12
        ADD             ; 72  +              10
        RCL R7          ; 73  ИП7            67
        RCL R5          ; 74  ИП5            65
        MUL             ; 75  ×              12
        RCL R4          ; 76  ИП4            64
        RCL R8          ; 77  ИП8            68
        MUL             ; 78  ×              12
        SUB             ; 79  −              11
        RCL R3          ; 80  ИП3            63
        MUL             ; 81  ×              12
        ADD             ; 82  +              10
        HALT            ; 83  С/П            50
        MUL             ; 84  ×              12
        RCL R0          ; 85  ИП0            60
        ADD             ; 86  +              10
        STO R0          ; 87  П0             40
        RCL RA          ; 88  ИПa            6A
        RTN             ; 89  В/О            52
