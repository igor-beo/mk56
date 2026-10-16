# 6.3. Jump commands and indirect addressing

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

## 6.3. Jump commands

*(p. 64)*

### 6.3.1.

*(p. 64)*

The unconditional jump command is implemented with the key [БП] (go to). This command interrupts the natural order of execution of the program's commands and transfers execution to the command given in the address (Table 6).

Table 6

| Address | Keys pressed | Code |
|---|---|---|
| … | … | … |
| 11 | [БП] | 51 |
| 12 | [4] [2] | 42 |

| Address | Keys pressed | Code |
|---|---|---|
| … | … | … |
| 42 | [+] | 10 |
| … | … | … |

*(p. 65)*

In this program fragment, address 11 holds an unconditional jump command (БП). Address 12 holds the jump address. When the program is executed in Automatic mode (АВТ), the jump is made to address 42, i.e. to execution of the addition operation.

### 6.3.2.

*(p. 65)*

Conditional jump commands (x≥0, x<0, x=0, x≠0) are implemented with the key [F] and a condition key [x≥0], [x<0], [x=0], [x≠0]. These commands check the contents of register X for the given condition. If the condition is not met, the next command executed in the program will be the command whose address is given immediately after the conditional jump command. If the condition is met, the next command executed will be the command written in the program after the jump address. In this case the jump address is not taken into account (Table 7).

Table 7

| Address | Keys pressed | Code |
|---|---|---|
| … | … | … |
| 14 | [F] [x²] | 22 |
| 15 | [F] [x=0] | 5E |
| 16 | [3] [8] | 38 |
| 17 | [+] | 10 |
| … | … | … |
| 38 | [4] | 04 |
| 39 | [−] | 11 |
| … | … | … |

*(p. 66)*

In this fragment, address 15 holds a jump command on the condition x=0. This command checks the contents of register X for the condition. If the contents of register X = 0, a jump is made to address 17 (execution of the addition operation); if not equal, execution transfers to the command written in the program at address 38.

### 6.3.3.

*(p. 66)*

The subroutine jump command is implemented with the key [ПП] (subroutine call; in automatic mode, single step). This command performs a jump to the subroutine at the address given immediately after the jump command, and the address of the next command is stored in the return stack (Table 8).

Table 8

| Address | Keys pressed | Code |
|---|---|---|
| … | … | … |
| 17 | [ПП] | 53 |
| 18 | [9] [0] | 90 |
| 19 | [В↑] (enter) | 0E |
| … | … | … |
| 89 | [−] | 11 |
| 90 | [2] | 02 |
| 91 | [В/О] (return; in automatic mode, reset to 00) | 52 |

In this fragment, address 17 holds the subroutine jump command. When this command is executed, execution transfers to the subroutine steps written from address 90, and the address of the main program, 19, is stored in the return stack.

### 6.3.4.

*(p. 66)*

The return-from-subroutine command is implemented with the key [В/О]. With this command the address stored by the subroutine jump command [ПП] is called (p. 67) from the return stack, and a jump is made to this address to execute the steps of the main program.

In the preceding fragment this command is written at address 91. This command calls address 19 from the return stack, and execution returns to the program steps written from this address.

### 6.3.5.

*(p. 67)*

The indirect unconditional jump command to a modified address is implemented with the keys [К], [БП] and the key of an addressable register ([0] or [1] … [9], [a], [в], [c], [d]). When this command is executed, the address stored in the addressable register whose index is part of the command is modified, and execution transfers to the command written at the new (modified) address. The address is modified according to the number of the register that is part of the command. If the command contains the number of one of the registers RG0, RG1, RG2, RG3, then when the command is executed one is subtracted from the contents of the register (the jump address); if it contains the number of one of the registers RG4, RG5, RG6, one is added to the contents of these registers; if it contains the number of one of the registers RG7, RG8, RG9, RGa, RGв, RGc, RGd, the contents of these registers do not change.

We shall show the modification of the address stored in the addressable registers when the commands [К], [БП], [3]; [К], [БП], [6][^tn1]; [К], [БП], [a] are executed.

Press the keys [В/О], [F], [ПРГ] and enter into the memory of the calculator the program given in Table 9.

*(p. 68)*

Table 9

| Address | Keys pressed | Code |
|---|---|---|
| 00 | [4] | 04 |
| 01 | [В↑] | 0E |
| 02 | [К] [БП] [3] | 83 |
| 03 | [F] [√] | 21 |
| 04 | [2] | 02 |
| 05 | [+] | 10 |
| 06 | [К] [БП] [4] | 84 |
| 07 | [+] | 10 |
| 08 | [3] | 03 |
| 09 | [×] | 12 |
| 10 | [К] [БП] [a] | 8A |
| 11 | [−] | 11 |
| 12 | [С/П] (stop/start) | 50 |

*Arrows to the left of Table 9: downward arrows at 00–01, 05 and 09, and brackets from 02 to 04, from 06 to 08 and from 10 to 12 (see scan p.68)*

Using the properties of the addressable registers that are part of the indirect ~~unconditional~~[^tn2] jump commands, different combinations of operations can be carried out depending on the numbers written in the addressable registers RG3, RG4, RGa and on the starting address of program execution.

To carry out the calculation (4 + 2)·3, the jumps must be made to the addresses shown by the arrows in Table 9; to do this, write the numbers 5, 7, 12 respectively into registers RG3, RG4, RGa, and start the program from address 00.

To do this, go to Automatic mode by pressing the keys [F], [АВТ] and carry out the following operations:

*(p. 69)*

1) press the keys:

| Keys pressed | |
|---|---|
| [5] [x→П] (store) [3] | write the number 5 into register RG3; |
| [7] [x→П] [4] | write the number 7 into register RG4; |
| [1] [2] [x→П] [a] | write the number 12 into register RGa; |
| [В/О] | prepare for calculation by program from address 00. |

2) check the contents of the addressable registers RG3, RG4, RGa before the program is run:

| Keys pressed | Display | |
|---|---|---|
| [П→x] (recall) [3] | `5,` | Contents of register RG3 |
| [П→x] [4] | `7,` | Contents of register RG4 |
| [П→x] [a] | `12,` | Contents of register RGa |

3) run the program in single-step mode by pressing the key [ПП]. One press of the key [ПП] corresponds to one executed program step;

4) check on the display the result of executing each program step;

5) if, after the next program step has been executed, it is necessary to check the address of the next command to be executed, go to Programming mode (ПРГ) by pressing the keys [F], [ПРГ], and read the reading of the next-command counter; then go to Automatic mode by pressing the keys [F], [АВТ] and run the program by pressing the key [ПП] (step-by-step execution of the program) or the key [С/П] (automatic execution of the calculations by program);

6) check the contents of the registers after the program has been executed:

*(p. 70)*

| Keys pressed | Display | |
|---|---|---|
| [П→x] [3] | `00000004,` | Modified address in register RG3 |
| [П→x] [4] | `00000008,` | Modified address in register RG4 |
| [П→x] [a] | `00000012,` | Modified address in register RGa |

7) the contents of the addressable registers can also be checked after a program step has been executed, but, so that the sequence of operations is not disturbed, restore the result of the step operation by entering it into register X.

### 6.3.6.

*(p. 70)*

Indirect conditional jump commands are implemented with the key [К], a condition key ([x=0] or [x≠0], [x≥0], [x<0]) and the key of an addressable register ([0] or [1] … [9], [a], [в], [c], [d]). With this command the contents of register X are checked for the given condition.

If the condition is not met, the address stored in the addressable register whose index is part of the command is modified (see 6.3.5), and execution transfers to the command written at the modified address.

If the condition is met, execution transfers to the next command. In this case the address written in the addressable register is not modified.

Let us compose a program for solving the equation y = −9x² + e^2x for x>0; if the calculation gives y>0, add sin x to its value, and if y<0, add tg x to its value (Table 10). To implement these conditions, the indirect conditional jump command [К] [x<0] [в] is entered (p. 72) in the program.

*(p. 71)*

Table 10

| Address | Keys pressed | Code |
|---|---|---|
| 00 | [1] | 01 |
| 01 | [9] | 09 |
| 02 | [x→П] [в] | 4B |
| 03 | [9] | 09 |
| 04 | [П→x] [1] | 61 |
| 05 | [F] [x²] | 22 |
| 06 | [×] | 12 |
| 07 | [x→П] [2] | 42 |
| 08 | [П→x] [1] | 61 |
| 09 | [2] | 02 |
| 10 | [×] | 12 |
| 11 | [F] [eˣ] | 16 |
| 12 | [П→x] [2] | 62 |
| 13 | [−] | 11 |
| 14 | [К] [x<0] [в] | CB |
| 15 | [П→x] [1] | 61 |
| 16 | [F] [tg] | 1E |
| 17 | [+] | 10 |
| 18 | [С/П] | 50 |
| 19 | [П→x] [1] | 61 |
| 20 | [F] [sin] | 1C |
| 21 | [+] | 10 |
| 22 | [С/П] | 50 |

*Dashed arrows to the left of Table 10 lead from address 14 to address 15 and to address 19 (see scan p.71)*

*(p. 72)*

The initial data (the value of x) are to be written into register RG1 in Automatic mode. The calculation y = −9x² + e^2x is written in the program at addresses 03–13, the jump address that is part of the command [К] [x<0] [в] is written at addresses 00–02, and the calculation of tg x and sin x is written at addresses 15–16 and 19–20 respectively.

When the program is executed, the presence of the indirect jump command at address 14 causes the result of the calculation y = −9x² + e^2x to be analysed. If the analysis shows that y>0, a jump is made to address 19; if y<0, the sequence of commands written in the program from address 15 is executed. The jumps in the program are marked with arrows.

For example, it is necessary to find the value of the function y for x = 1, 2, 3, 4. To do this, carry out the following operations:

1) go to Programming mode by pressing the keys [В/О] [F], [ПРГ] and enter the program (Table 10);
2) go to Automatic mode by pressing the keys [F] [АВТ];
3) set the Г/Р/ГРД switch to position "Р";
4) enter the value x=1 into register RG1 by pressing the keys [1] [x→П] [Г][^tn3];
5) set the start of the program calculation at address 00 by pressing the key [В/О];
6) start the program by pressing the key [С/П]. The display should show `-5,35365-02` (the value of y at x=1).

Then carry out the following operations:

*(p. 73)*

| Keys pressed | Display | |
|---|---|---|
| [2] [x→П] [1] [В/О] [С/П] | `19,507444` | Value of y at x=2 |
| [3] [x→П] [1] [В/О] [С/П] | `322,56986` | Value of y at x=3 |
| [4] [x→П] [1] [В/О] [С/П] | `2836,2007` | Value of y at x=4 |

### 6.3.7.

*(p. 73)*

The indirect subroutine jump command is implemented with the keys [К], [ПП] and the key of an addressable register ([0] or [1] … [9], [a], [в], [c], [d]). This command modifies the address stored in the addressable register whose index is part of the command (see 6.3.5), writes the next command into the return stack, and transfers execution to the command written at the modified address.

Let us compose a program (Table 11) for solving the quadratic equation ax²+bx+c=0 with arbitrary values of the coefficients, in which the roots of the quadratic equation are determined by the formulas

X1 = (−b + √(b²−4ac)) / 2a ;   X2 = (−b − √(b²−4ac)) / 2a

The values of the coefficients are to be written: "a" into register RGa, "в" into register RGв, "c" into register RGc, in Automatic mode; and the result of calculating the root X1 into register RG1, and the root X2 into register RG2, while the program is being executed.

The calculation of the discriminant D = b²−4ac is laid out as a subroutine (addresses 19–27), which is called with the command [К] [ПП] [7]. Executing this command causes the address of the command (04 on the first execution and 11 on the second) to be stored (p. 75) in the return stack register, and a jump to be made to address 19, from which the calculation of the discriminant is written. The jump address is written in the program at addresses 00–02.

*(p. 74)*

Table 11

| Address | Keys pressed | Code | Address | Keys pressed | Code |
|---|---|---|---|---|---|
| 00 | [1] | 01 | 19 | [П→x] [a] | 6A |
| 01 | [9] | 09 | 20 | [П→x] [c] | 6C |
| 02 | [x→П] [7] | 47 | 21 | [×] | 12 |
| 03 | [К] [ПП] [7] | A7 | 22 | [4] | 04 |
| 04 | [+] | 10 | 23 | [×] | 12 |
| 05 | [П→x] [a] | 6A | 24 | [П→x] [в] | 6B |
| 06 | [÷] | 13 | 25 | [F] [x²] | 22 |
| 07 | [2] | 02 | 26 | [↔] (swap X and Y) | 14 |
| 08 | [÷] | 13 | 27 | [−] | 11 |
| 09 | [x→П] [1] | 41 | 28 | [F] [√] | 21 |
| 10 | [К] [ПП] [7] | A7 | 29 | [П→x] [в] | 6B |
| 11 | [↔] | 14 | 30 | [/-/] (change sign) | 0B |
| 12 | [−] | 11 | 31 | [В/О] | 52 |
| 13 | [П→x] [a] | 6A | | | |
| 14 | [÷] | 13 | | | |
| 15 | [2] | 02 | | | |
| 16 | [÷] | 13 | | | |
| 17 | [x→П] [2] | 42 | | | |
| 18 | [С/П] | 50 | | | |

*Lines between the two halves of Table 11 lead from address 03 (solid) and address 10 (dashed) to address 19, and from address 31 back to address 04 (solid) and address 11 (dashed) (see scan p.74)*

*(p. 75)*

Note. If the value of the discriminant when the equation is solved is less than 0, the roots X1 and X2 will be imaginary and the display of the calculator will show "ЕГГОГ" (error).

For example, it is necessary to determine the roots of the quadratic equation 3x² + 2x − 1 = 0.

To do this, carry out the following operations:

1) go to Programming mode by pressing the keys [В/О], [F], [ПРГ], and enter the program (Table 11), if the program has not been entered before;
2) go to Automatic mode by pressing the keys [F] [АВТ];
3) enter the values of the coefficients "a", "в" and "c" into the memory registers:

| Keys pressed | Display |
|---|---|
| [3] [x→П] [a] | `3,` |
| [2] [x→П] [в] | `2,` |
| [1] [/-/] [x→П] [c] | `-1,` |

4) set the start of the program calculation at address 00 by pressing the key [В/О];
5) start the program by pressing the key [С/П], and read the value X2 on the display: `-1,`. Press the keys [П→x], [1] and read the value X1 on the display: `3,3333333 -01`.

### 6.3.8.

*(p. 76)*

The indirect write-to-register command is implemented with the keys [К], [x→П] and the key of an addressable register ([0] – [d]). This command modifies the contents of the addressable register whose index is part of the command (see 6.3.5), and writes the contents of register X into the register that corresponds to the resulting modified code.

Table 12 gives the modified codes that can be obtained when the indirect write command is executed, and the numbers of the registers into which the information of register X is written according to the given modified code.

Table 12

| Modified code | Register corresponding to the code |
|---|---|
| `00000000,` | RG0 |
| `00000001,` | RG1 |
| `00000002,` | RG2 |
| `00000003,` | RG3 |
| `00000004,` | RG4 |
| `00000005,` | RG5 |
| `00000006,` | RG6 |
| `00000007,` | RG7 |
| `00000008,` | RG8 |
| `00000009,` | RG9 |
| `00000010,` | RGa |
| `00000011,` | RGв |
| `00000012,` | RGc |
| `00000013,` | RGd |

The actions of the indirect write command in Automatic mode (p. 77) can be illustrated by the following examples:

| Keys pressed | Display | |
|---|---|---|
| [1] [4] | `14,` | Number 14 written into register X |
| [x→П] [0] | `14,` | Number 14 written into register RG0 |
| [К] [x→П] [0] | `14,` | Code in register RG0 modified and number 14 written into register RGd |
| [П→x] [0] | `00000013,` | Check of the contents of register RG0 |
| [П→x] [d] | `14,` | Check of the contents of register RGd |
| [5] | `5,` | Number 5 written into register X |
| [К] [x→П] [0] | `5,` | Code in register RG0 modified and number 5 written into register RGc |
| [П→x] [0] | `00000012,` | Check of the contents of register RG0 |
| [П→x] [c] | `5,` | Check of the contents of register RGc |

### 6.3.9.

*(p. 77)*

The indirect recall indication command is implemented with the keys [К] [П→x] and the key of an addressable register.

This command modifies the contents of the addressable register (6.3.5) and calls into register X the contents of the register that corresponds to the modified code (Table 12).

We illustrate the action of this command as follows:

*(p. 78)*

| Keys pressed | Display | |
|---|---|---|
| [4] [x→П] [4] | `4,` | Number 4 written into register RG4 |
| [1] [0] [x→П] [5] | `10,` | Number 10 written into register RG5 |
| [2] [0] [x→П] [6] | `20,` | Number 20 written into register RG6 |
| [3] [0] [x→П] [7] | `30,` | Number 30 written into register RG7 |
| [К] [П→x] [4] | `10,` | Modification of the number in register RG4 (4+1=00000005) and call of the contents of register RG5 into register X |
| [П→x] [4] | `00000005,` | Call of the modified number from register RG4 into register X |
| [К] [П→x] [4] | `20,` | Modification of the number in register RG4 (00000005 + 1 = 00000006) and call of the contents of register RG6 into register X |
| [П→x] [4] | `00000006,` | Call of the modified code from register RG4 into register X |

For example, to solve the expression Σ_{i=1}^{4} (2tg(xi/3) + 4) for xi = 1, 2, 3, 4, the indirect recall indication command can be used.

In this expression the number of calculation cycles i and the maximum value of X are equal to 4. To write these values we use register RG3. We organise the calculation cycles with the keys [К] [П→x] [3]. On each execution of this command, 1 is subtracted from the contents of register RG3, then the contents of this (p. 79) register are called into register X, where they are checked for zero with the conditional jump command on x=0. If the contents of register X≠0, a jump is made to the calculation 2tg(xi/3)+4 and to the accumulation of the calculation results in register RG5. If the contents of register X are equal to zero, a jump is made to the command that calls the contents of register RG5 into register X and stops the calculations.

The program for calculating the expression Σ_{i=1}^{4} (2tg(xi/3) + 4) is given in Table 13.

In the program the command [К] [П→x] [3] comes before the command that calls the value xi, so the initial data must be entered into register RG3 in the form Xi + 1. The calculations by program are shown schematically in Fig. 5.

To calculate the expression Σ_{i=1}^{4} (2tg(xi/3) + 4), carry out the following operations:

1) clear register RG5 by pressing the keys [Cx] (clear X), [x→П], [5], if register RG5 was used before;
2) go to Programming mode by pressing the keys [В/О], [F], [ПРГ];
3) enter the program (Table 13);
4) go to Automatic mode by pressing the keys [F], [АВТ];
5) prepare the program calculation from address zero by pressing the key [В/О];
6) enter the initial data by pressing the key [5];
7) set the Г/Р/ГРД switch to position "Р";
8) start the program by pressing the key [С/П].

The display should show `29,644467`.

If the calculation needs to be repeated, clear register (p. 82) RG5 by pressing the keys [Cx] [x→П] [5], enter the initial data Xi=5, then press the keys [В/О], [С/П].

*(p. 80)*

PROGRAM FLOWCHART

*Figure 5: program flowchart — write the value Xi+1 into register RG3 (address 00); calculation loop: subtract 1 from the contents of register RG3 (address 01), call the number Xi from register RG3 into register X (address 02), analyse the contents of register X for zero (addresses 03–04); if X≠0, calculate 2tg(Xi/3)+4, where Xi = 4,3,2,1 (addresses 07–13), and accumulate the results in register RG5, (2tg(4/3)+4)+(2tg(3/3)+4)+(2tg(2/3)+4)+(2tg(1/3)+4) (addresses 14–16), returning via addresses 17–18; if X=0, display the contents of register RG5 and stop the calculations (addresses 05–06) (see scan p.80)*

*(p. 81)*

Table 13

| Address | Keys | Code |
|---|---|---|
| 00 | [x→П] [3] | 43 |
| 01 | [К] [П→x] [3] | D3 |
| 02 | [П→x] [3] | 63 |
| 03 | [F] [x=0] | 5E |
| 04 | [0] [7] | 07 |
| 05 | [П→x] [5] | 65 |
| 06 | [С/П] | 50 |
| 07 | [3] | 03 |
| 08 | [÷] | 13 |
| 09 | [F] [tg] | 1E |
| 10 | [2] | 02 |
| 11 | [×] | 12 |
| 12 | [4] | 04 |
| 13 | [+] | 10 |
| 14 | [П→x] [5] | 65 |
| 15 | [+] | 10 |
| 16 | [x→П] [5] | 45 |
| 17 | [БП] | 51 |
| 18 | [0] [1] | 01 |

### 6.3.10.

*(p. 82)*

Loop commands are implemented with the keys [F], [L0] (or [L1], [L2], [L3]). When the key [L0] ([L1], [L2], [L3]) is pressed, register RG0 (RG1, RG2, RG3) is accessed. On each access to the register, one is subtracted from its contents and its contents are analysed for zero. If the contents of the register are not equal to zero, execution transfers to the command written at the jump address that follows the loop command; if they are equal to zero, the command written in the program after the jump address is executed.

Let us compose a program for solving the example Σ_{i=1}^{4} (2tg(xi/3) + 4) for Xi = 1, 2, 3, 4, using the keys [F] [L0]. The initial data (the number of cycles i and the maximum number xi) we write into register RG0. To accumulate the results of the calculations 2tg(xi/3)+4 we use register RG5. The program for calculating the example is given in Table 14; the calculation scheme is shown in Fig. 6.

When the last calculation cycle is executed, when the command [F] [L0] is executed, one is subtracted from the contents of register RG0 (the digit 1) and the result of the subtraction is analysed for zero. Since the result of the subtraction 1−1 is equal to zero, execution transfers to the stop command. However, if the user wishes to check the contents of register RG0 by pressing the keys [П→x] [L0][^tn4], he will see `00000001,` on the display.

To calculate the example, carry out the following operations:

1) go to Programming mode at address 00 by pressing the keys [В/О], [F], [ПРГ];
2) enter the program (Table 14);

*(p. 83)*

PROGRAM FLOWCHART

*Figure 6: program flowchart — write the value Xi into register RG0 (address 00); call the contents of register RG0 into register X (address 01); calculate 2tg(Xi/3)+4, where Xi = 4,3,2,1 (addresses 02–08); accumulate the results of the calculations (2tg(4/3)+4)+(2tg(3/3)+4)+(2tg(2/3)+4)+(2tg(1/3)+4) in register RG5 (addresses 09–11); subtract 1 from the contents of register RG0 and analyse the result of the subtraction for 0 (address 12); if RG0≠0 (address 13), return to address 01; if RG0=0, display the contents of register RG5 and stop the calculations (address 14) (see scan p.83)*

*(p. 84)*

Table 14

| Address | Keys pressed | Code |
|---|---|---|
| 00 | [x→П] [0] | 40 |
| 01 | [П→x] [0] | 60 |
| 02 | [3] | 03 |
| 03 | [÷] | 13 |
| 04 | [F] [tg] | 1E |
| 05 | [2] | 02 |
| 06 | [×] | 12 |
| 07 | [4] | 04 |
| 08 | [+] | 10 |
| 09 | [П→x] [5] | 65 |
| 10 | [+] | 10 |
| 11 | [x→П] [5] | 45 |
| 12 | [F] [L0] | 5D |
| 13 | [0] [1] | 01 |
| 14 | [С/П] | 50 |

*An arrow to the left of Table 14 leads from address 13 back to address 01 (see scan p.84)*

*(p. 85)*

3) go to Automatic mode by pressing the keys [F] [АВТ];
4) clear register RG5 by pressing the keys [Cx], [x→П], [5];
5) enter the initial data (the number 4) by pressing the key [4];
6) set the Г/Р/ГРД switch to position "Р";
7) prepare the calculation by program from address 00 by pressing the key [В/О];
8) start the program by pressing the key [С/П];
9) read the result on the display: `29,644467`.

[^tn1]: Translator's note: Printed as [6]. The program in Table 9 uses [К] [БП] [4] (address 06), and the register check on p.69–70 uses RG3, RG4 and RGa.
[^tn2]: Translator's note: The word «безусловных» ("unconditional") is struck through in the original.
[^tn3]: Translator's note: The third key is printed as [Г]. The program (Table 10) reads x from register RG1, and the repeated calculations on p.73 use [x→П] [1].
[^tn4]: Translator's note: Printed as [L0]. Elsewhere in the manual the contents of RG0 are called with [П→x] [0].
