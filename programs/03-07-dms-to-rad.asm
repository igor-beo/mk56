; Program 3.7: Angle in degrees, minutes, seconds -> radians
; phi = ((phi''/60 + phi')/60 + phi°) * pi/180
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.57 (book61.pdf page 58)
; Input: phi° in X, С/П; phi' in X, С/П; phi'' in X, С/П.  Output: phi (rad) in X;
; R0 = angle in decimal degrees.
;
; Book example: 114°, 35', 29,616'' -> phi = 2; R0 = 114,59156
; @input 114
; @input 35
; @input 29.616
; @expect X=2
; @expect R0=114.59156
;
; As printed:
;   00: П8 С/П П9 С/П В↑ 6 0 ÷ ИП9 +
;   10: 6 0 ÷ ИП8 + П0 1 8 0 ÷
;   20: Fπ × С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R8          ; 00  П8             48
        HALT            ; 01  С/П            50
        STO R9          ; 02  П9             49
        HALT            ; 03  С/П            50
        ENTER           ; 04  В↑             0E
        60              ; 05  6 0            06 00
        DIV             ; 07  ÷              13
        RCL R9          ; 08  ИП9            69
        ADD             ; 09  +              10
        60              ; 10  6 0            06 00
        DIV             ; 12  ÷              13
        RCL R8          ; 13  ИП8            68
        ADD             ; 14  +              10
        STO R0          ; 15  П0             40
        180             ; 16  1 8 0          01 08 00
        DIV             ; 19  ÷              13
        PI              ; 20  Fπ             20
        MUL             ; 21  ×              12
        HALT            ; 22  С/П            50
        JMP L00         ; 23  БП 00          51 00
