; ============================================
; Program: Quadratic Equation Solver
; Purpose: Solve ax² + bx + c = 0
;          x = (-b ± sqrt(b² - 4ac)) / 2a
; Input:   a=R0, b=R1, c=R2
; Output:  x1 in X (first root)
;          Run again for x2 (change ADD to SUB at discriminant)
; Registers Used: R0 (a), R1 (b), R2 (c), R3 (discriminant)
; ============================================
; Test: x² - 5x + 6 = 0 → x1=3, x2=2
;       (a=1, b=-5, c=6)
; ============================================

.ORG 0

; Pre-load: R0=a, R1=b, R2=c

quadratic:
        ; Calculate discriminant: b² - 4ac
        RCL R1          ; b
        SQ              ; b²
        4               ; 4
        RCL R0          ; a
        MUL             ; 4a
        RCL R2          ; c
        MUL             ; 4ac
        SUB             ; b² - 4ac
        STO R3          ; save discriminant
        
        ; Check discriminant
        JLT no_real     ; if < 0, no real roots
        
        ; Calculate sqrt(discriminant)
        SQRT            ; sqrt(b² - 4ac)
        
        ; Calculate -b + sqrt(disc)
        RCL R1          ; b
        CHS             ; -b
        ADD             ; -b + sqrt(b² - 4ac)
        
        ; Divide by 2a
        2
        RCL R0
        MUL             ; 2a
        DIV             ; (-b + sqrt(b² - 4ac)) / 2a
        
        HALT            ; x1 in X

no_real:
        ; Signal error for complex roots
        CLX
        HALT

.END

; ============================================
; To get x2, modify line with ADD to:
;        SUB             ; -b - sqrt(b² - 4ac)
; ============================================
