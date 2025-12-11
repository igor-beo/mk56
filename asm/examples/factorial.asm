; ============================================
; Program: Factorial
; Purpose: Calculate n! = 1 × 2 × 3 × ... × n
; Input:   n in X register (n >= 0)
; Output:  n! in X register
; Registers Used: R0 (counter), R1 (result)
; ============================================
; Test: 5! = 120, 10! = 3628800
; ============================================

.ORG 0

        STO R0          ; R0 = n (counter)
        1
        STO R1          ; R1 = 1 (result)

loop:
        RCL R0          ; get counter
        1
        SUB             ; counter - 1
        JLT done        ; if < 0, done (handles n=0 case too)
        1
        ADD             ; restore counter value
        RCL R1          ; get result
        MUL             ; result * counter
        STO R1          ; save result
        RCL R0          ; get counter
        1
        SUB             ; counter - 1
        STO R0          ; save counter
        JMP loop

done:
        RCL R1          ; result to X
        HALT

.END
