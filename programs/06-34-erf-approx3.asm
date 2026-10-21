; Program 6.34: Φ(x) = erf(x) = (2/sqrt(π))·∫[0..x] exp(−t²) dt for x > 0 by the
;   approximation (6.20), error < 2,5·10⁻⁵ (Abramowitz–Stegun 7.1.25):
;   Φ(x) = 1 − λ(a1 + λ(a2 + a3·λ))/exp(x²),  λ = 1/(1 + p·x)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.168-169 (book61.pdf pages 169-170)
; Input: p = 0,47047 in R0, a1 = 0,3480242 in R1, a2 = −0,0958798 in R2,
;   a3 = 0,7478556 in R3; x in X.  Output: Φ(x) in X.
; For x < 0 the book gives Φ(−x) = 1 − Φ(x) (sic; erf is odd: Φ(−x) = −Φ(x)).
;
; Book examples: Φ(0,1) = 0,1124832; Φ(0,5) = 0,5204876; Φ(1) = 0,8427168;
;   Φ(3) = 0,9999776 (about 10 s each)
; @reg R0=0.47047 R1=0.3480242 R2=-0.0958798 R3=0.7478556
; @input 0.1
; @expect X=0.1124832
; @input 0.5
; @expect X=0.5204876
; @input 1
; @expect X=0.8427168
; @input 3
; @expect X=0.9999776
;
; As printed:
;   00: В↑ ИП0 × 1 + F1/x П9 ИП3 × ИП2
;   10: + ИП9 × ИП1 + ИП9 × ↔ Fx² Feˣ
;   20: ÷ 1 ↔ − С/П БП 00
;
; Each line: instruction ; address, keys, codes

L00:
        ENTER           ; 00  В↑             0E
        RCL R0          ; 01  ИП0            60
        MUL             ; 02  ×              12
        1               ; 03  1              01
        ADD             ; 04  +              10
        INV             ; 05  F1/x           23
        STO R9          ; 06  П9             49
        RCL R3          ; 07  ИП3            63
        MUL             ; 08  ×              12
        RCL R2          ; 09  ИП2            62
        ADD             ; 10  +              10
        RCL R9          ; 11  ИП9            69
        MUL             ; 12  ×              12
        RCL R1          ; 13  ИП1            61
        ADD             ; 14  +              10
        RCL R9          ; 15  ИП9            69
        MUL             ; 16  ×              12
        SWAP            ; 17  ↔              14
        SQ              ; 18  Fx²            22
        EXP             ; 19  Feˣ            16
        DIV             ; 20  ÷              13
        1               ; 21  1              01
        SWAP            ; 22  ↔              14
        SUB             ; 23  −              11
        HALT            ; 24  С/П            50
        JMP L00         ; 25  БП 00          51 00
