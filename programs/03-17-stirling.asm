; Program 3.17: Factorial of large n by Stirling's formula (first five digits are
; correct for n > 10):  n! = n^n sqrt(2 pi n) exp[-n + (1/(12n))(1 - 1/(30n))]
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.61-62 (book61.pdf pages 62-63)
; Input: n in X (maximum n = 56).  Output: n! in X.
; Fxʸ with base n in X and exponent n in Y gives n^n.
;
; Book examples: 10! = 3628711,6; 20! = 2,4328826*10^18; 56! = 7,1100172*10^74.
; The printed digits come from 8-digit arithmetic; the formula evaluated in double
; precision gives about 3628709,2 / 2,432886e18 / 7,109980e74, hence tol=1e-5.
; @input 10
; @expect X=3628711.6 tol=1e-5
; @input 20
; @expect X=2.4328826e18 tol=1e-5
; @input 56
; @expect X=7.1100172e74 tol=1e-5
;
; As printed:
;   00: П9 В↑ Fxʸ 1 ИП9 3 0 × F1/x −
;   10: 1 2 ÷ ИП9 ÷ ИП9 − Feˣ × 2
;   20: Fπ × ИП9 × F√ × С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        STO R9          ; 00  П9             49
        ENTER           ; 01  В↑             0E
        POW             ; 02  Fxʸ            24
        1               ; 03  1              01
        RCL R9          ; 04  ИП9            69
        30              ; 05  3 0            03 00
        MUL             ; 07  ×              12
        INV             ; 08  F1/x           23
        SUB             ; 09  −              11
        12              ; 10  1 2            01 02
        DIV             ; 12  ÷              13
        RCL R9          ; 13  ИП9            69
        DIV             ; 14  ÷              13
        RCL R9          ; 15  ИП9            69
        SUB             ; 16  −              11
        EXP             ; 17  Feˣ            16
        MUL             ; 18  ×              12
        2               ; 19  2              02
        PI              ; 20  Fπ             20
        MUL             ; 21  ×              12
        RCL R9          ; 22  ИП9            69
        MUL             ; 23  ×              12
        SQRT            ; 24  F√             21
        MUL             ; 25  ×              12
        HALT            ; 26  С/П            50
        JMP L00         ; 27  БП 00          51 00
