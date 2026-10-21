; Program 5.67: Response u(t) of an integrating RC circuit to an input e(t),
; combined (explicit + implicit) Euler method (5.39), du/dt = (e(t) - u)/tau:
;   u(i+1) = (u(i) + [e(t(i)) - u(i)]Ah/tau + (1 - A)e(t(i+1))h/tau) / (1 + (1 - A)h/tau)
; Source: Дьяконов, «Справочник по расчётам на микрокалькуляторах», 1985, p.118 (book61.pdf page 119)
; Input: A in Ra, t0 in Rb, u0 in Rc, h in Rd, tau = RC in R9. The subroutine at 42
; must compute e(t) from t in Rb (the book's "..." before П6 В/О).
; Each С/П: one step; output t(i) in X, u(i) in Y = Rc, e(t(i)) in R6.
; This instance uses the book's example (p.119): double-exponential pulse
; e(t) = U0 (exp(-t/tau1) - exp(-t/tau2)), tau1 in R1, tau2 in R2, U0 in R0:
; "ИПВ /−/ ИП1 ÷ Fe^x ИПВ /−/ ИП2 ÷ Fe^x − ИП0 ×".
;
; (A jump and its address stay on one line, so line breaks differ from the book.)
; Book example: A = 0,5, t0 = 0, u0 = 0, h = 0,2, U0 = 10, tau = 1, tau1 = 1,
; tau2 = 0,5 -> t1 = 0,2, u(t1) = 0,1349188; t2 = 0,4, u(t2) = 0,44620789;
; t3 = 0,6, u(t3) = 0,7910869.
; @reg Ra=0.5 Rb=0 Rc=0 Rd=0.2 R9=1 R0=10 R1=1 R2=0.5
; @run
; @expect X=0.2
; @expect Y=0.1349188
; @run
; @expect X=0.4
; @expect Y=0.44620789
; @run
; @expect X=0.6
; @expect Y=0.7910869
; @expect Rc=0.7910869
;
; As printed:
;   00: ИПВ ПП 42 ИПС − ИПА × ИПД ИП9 ÷
;   10: П8 × ИПС + П7 ИПВ ИПД + ПВ ПП 42
;   21: ИП8 × 1 ИПА − × ИП7 + 1 ИПА
;   31: − ИП8 × 1 + ÷ ПС ИПВ С/П БП 00
;   42: ИПВ /−/ ИП1 ÷ Fe^x ИПВ /−/ ИП2 ÷ Fe^x
;   52: − ИП0 × П6 В/О
;
; Each line: instruction ; address, keys, codes

L00:
        RCL RB          ; 00  ИПb            6B
        CALL sub42      ; 01  ПП 42          53 42
        RCL RC          ; 03  ИПc            6C
        SUB             ; 04  −              11
        RCL RA          ; 05  ИПa            6A
        MUL             ; 06  ×              12
        RCL RD          ; 07  ИПd            6D
        RCL R9          ; 08  ИП9            69
        DIV             ; 09  ÷              13
        STO R8          ; 10  П8             48
        MUL             ; 11  ×              12
        RCL RC          ; 12  ИПc            6C
        ADD             ; 13  +              10
        STO R7          ; 14  П7             47
        RCL RB          ; 15  ИПb            6B
        RCL RD          ; 16  ИПd            6D
        ADD             ; 17  +              10
        STO RB          ; 18  Пb             4B
        CALL sub42      ; 19  ПП 42          53 42
        RCL R8          ; 21  ИП8            68
        MUL             ; 22  ×              12
        1               ; 23  1              01
        RCL RA          ; 24  ИПa            6A
        SUB             ; 25  −              11
        MUL             ; 26  ×              12
        RCL R7          ; 27  ИП7            67
        ADD             ; 28  +              10
        1               ; 29  1              01
        RCL RA          ; 30  ИПa            6A
        SUB             ; 31  −              11
        RCL R8          ; 32  ИП8            68
        MUL             ; 33  ×              12
        1               ; 34  1              01
        ADD             ; 35  +              10
        DIV             ; 36  ÷              13
        STO RC          ; 37  Пc             4C
        RCL RB          ; 38  ИПb            6B
        HALT            ; 39  С/П            50
        JMP L00         ; 40  БП 00          51 00

sub42:
        RCL RB          ; 42  ИПb            6B
        CHS             ; 43  /-/            0B
        RCL R1          ; 44  ИП1            61
        DIV             ; 45  ÷              13
        EXP             ; 46  Feˣ            16
        RCL RB          ; 47  ИПb            6B
        CHS             ; 48  /-/            0B
        RCL R2          ; 49  ИП2            62
        DIV             ; 50  ÷              13
        EXP             ; 51  Feˣ            16
        SUB             ; 52  −              11
        RCL R0          ; 53  ИП0            60
        MUL             ; 54  ×              12
        STO R6          ; 55  П6             46
        RTN             ; 56  В/О            52
