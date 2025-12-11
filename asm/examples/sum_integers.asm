; ============================================
; Program: Sum of Integers
; Purpose: Calculate S = 1 + 2 + 3 + ... + n
; Input:   n in X register
; Output:  sum in X register
; Registers Used: R0 (counter), R1 (sum)
; Source: Program 4.12 from Dyakonov
; ============================================
; Original: П0 0 ИП0 + FL0 02 С/П
; Test: n=10 → S=55, n=100 → S=5050
; Note: Also equals n(n+1)/2
; ============================================

.ORG 0

sum_n:
        STO R0          ; R0 = n (counter)
        0               ; initialize sum = 0
        STO R1          ; R1 = sum

loop:
        RCL R0          ; get counter
        JLT done        ; if counter < 0, done
        RCL R1          ; get sum
        RCL R0          ; get counter  
        ADD             ; sum + counter
        STO R1          ; store new sum
        RCL R0          ; get counter
        1
        SUB             ; counter - 1
        STO R0          ; store new counter
        JMP loop        ; repeat

done:
        RCL R1          ; result to X
        HALT

.END
