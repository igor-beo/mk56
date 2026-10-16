# 6. Operation of the calculator in Programming mode

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

## 6. OPERATION OF THE CALCULATOR IN PROGRAMMING MODE (ПРГ)

*(p. 50)*

### 6.1. General information

*(p. 50)*

6.1.1. The calculator is put into Programming mode (ПРГ) after the keys [F] and [ПРГ] are pressed.

6.1.2. When keys are pressed in Programming mode, the two-digit code of the operations, commands and digits assigned to the given key, or to its combination with the keys [F], [К], [x→П] (store), [П→x] (recall) (see Table 4), is written into the special program memory.

6.1.3. The sequence of entered operations and commands needed to solve problems constitutes a program.

6.1.4. The special program memory consists of ninety-eight cells. The first cell is assigned the number 00, the last 97.

6.1.5. When a program is written into the calculator, a two-digit code (program step) occupies one cell in program memory.

*(p. 51)*

Table 4[^tn1]

OPERATION AND COMMAND CODES

| Keys pressed | Code |
|---|---|
| [0] | 00 |
| [1] | 01 |
| [2] | 02 |
| [3] | 03 |
| [4] | 04 |
| [5] | 05 |
| [6] | 06 |
| [7] | 07 |
| [8] | 08 |
| [9] | 09 |
| [+] | 10 |
| [−] | 11 |
| [×] | 12 |
| [÷] | 13 |
| [↔] (swap X and Y) | 14 |
| [В↑] (enter) | 0E |
| [.] | 0A |
| [/-/] (change sign) | 0B |
| [ВП] (enter exponent) | 0C |
| [Cx] (clear X) | 0D |
| [С/П] (stop/start) | 50 |
| [БП] (go to) | 51 |
| [В/О] (return; in automatic mode, reset to 00) | 52 |
| [ПП] (subroutine call; in automatic mode, single step) | 53 |
| [F] [10ˣ] | 15 |
| [F] [lg] | 17 |
| [F] [ln] | 18 |
| [F] [eˣ] | 16 |
| [F] [sin⁻¹] | 19 |
| [F] [cos⁻¹] | 1A |
| [F] [tg⁻¹] | 1B |
| [F] [sin] | 1C |
| [F] [cos] | 1D |
| [F] [tg] | 1E |
| [F] [π] | 20 |
| [F] [√] | 21 |
| [F] [x²] | 22 |
| [F] [1/x] | 23 |
| [F] [↔] | 24 |
| [F] [Cx] | |

*Table 4 continued (p. 52)*

| Keys pressed | Code |
|---|---|
| [F] [x<0] | 5C |
| [F] [x=0] | 5E |
| [F] [x≥0] | 59 |
| [F] [x≠0] | 57 |
| [F] [L0] | 5D |
| [F] [L1] | 5B |
| [F] [L2] | 58 |
| [F] [L3] | 5A |
| [x→П] [0] | 40 |
| [x→П] [1] | 41 |
| [x→П] [2] | 42 |
| [x→П] [3] | 43 |
| [x→П] [4] | 44 |
| [x→П] [5] | 45 |
| [x→П] [6] | 46 |
| [x→П] [7] | 47 |
| [x→П] [8] | 48 |
| [x→П] [9] | 49 |
| [x→П] [a] | 4A |
| [x→П] [в] | 4B |
| [x→П] [c] | 4C |
| [x→П] [d] | 4D |
| [П→x] [0] | 60 |
| [П→x] [1] | 61 |
| [П→x] [2] | 62 |
| [П→x] [3] | 63 |
| [П→x] [4] | 64 |
| [П→x] [5] | 65 |
| [П→x] [6] | 66 |
| [П→x] [7] | 67 |
| [П→x] [8] | 68 |
| [П→x] [9] | 69 |
| [П→x] [a] | 6A |
| [П→x] [в] | 6B |
| [П→x] [c] | 6C |
| [П→x] [d] | 6D |
| [К] [НОП] | 54 |
| [К] [БП] [0] | 80 |
| [К] [БП] [1] | 81 |
| [К] [БП] [2] | 82 |

*Table 4 continued (p. 53)*

| Keys pressed | Code |
|---|---|
| [К] [БП] [3] | 83 |
| [К] [БП] [4] | 84 |
| [К] [БП] [5] | 85 |
| [К] [БП] [6] | 86 |
| [К] [БП] [7] | 87 |
| [К] [БП] [8] | 88 |
| [К] [БП] [9] | 89 |
| [К] [БП] [a] | 8A |
| [К] [БП] [в] | 8B |
| [К] [БП] [c] | 8C |
| [К] [БП] [d] | 8D |
| [К] [ПП] [0] | A0 |
| [К] [ПП] [1] | A1 |
| [К] [ПП] [2] | A2 |
| [К] [ПП] [3] | A3 |
| [К] [ПП] [4] | A4 |
| [К] [ПП] [5] | A5 |
| [К] [ПП] [6] | A6 |
| [К] [ПП] [7] | A7 |
| [К] [ПП] [8] | A8 |
| [К] [ПП] [9] | A9 |
| [К] [ПП] [a] | AA |
| [К] [ПП] [в] | AB |
| [К] [ПП] [c] | AC |
| [К] [ПП] [d] | AD |
| [К] [x=0] [0] | E0 |
| [К] [x=0] [1] | E1 |
| [К] [x=0] [2] | E2 |
| [К] [x=0] [3] | E3 |
| [К] [x=0] [4] | E4 |
| [К] [x=0] [5] | E5 |
| [К] [x=0] [6] | E6 |
| [К] [x=0] [7] | E7 |
| [К] [x=0] [8] | E8 |
| [К] [x=0] [9] | E9 |
| [К] [x=0] [a] | EA |
| [К] [x=0] [в] | EB |
| [К] [x=0] [c] | EC |
| [К] [x=0] [d] | ED |
| [К] [x<0] [0] | C0 |

*Table 4 continued (p. 54)*

| Keys pressed | Code |
|---|---|
| [К] [x<0] [1] | C1 |
| [К] [x<0] [2] | C2 |
| [К] [x<0] [3] | C3 |
| [К] [x<0] [4] | C4 |
| [К] [x<0] [5] | C5 |
| [К] [x<0] [6] | C6 |
| [К] [x<0] [7] | C7 |
| [К] [x<0] [8] | C8 |
| [К] [x<0] [9] | C9 |
| [К] [x<0] [a] | CA |
| [К] [x<0] [в] | CB |
| [К] [x<0] [c] | CC |
| [К] [x<0] [d] | CD |
| [К] [x≥0] [0] | 90 |
| [К] [x≥0] [1] | 91 |
| [К] [x≥0] [2] | 92 |
| [К] [x≥0] [3] | 93 |
| [К] [x≥0] [4] | 94 |
| [К] [x≥0] [5] | 95 |
| [К] [x≥0] [6] | 96 |
| [К] [x≥0] [7] | 97 |
| [К] [x≥0] [8] | 98 |
| [К] [x≥0] [9] | 99 |
| [К] [x≥0] [a] | 9A |
| [К] [x≥0] [в] | 9B |
| [К] [x≥0] [c] | 9C |
| [К] [x≥0] [d] | 9D |
| [К] [x≠0] [0] | 70 |
| [К] [x≠0] [1] | 71 |
| [К] [x≠0] [2] | 72 |
| [К] [x≠0] [3] | 73 |
| [К] [x≠0] [4] | 74 |
| [К] [x≠0] [5] | 75 |
| [К] [x≠0] [6] | 76 |
| [К] [x≠0] [7] | 77 |
| [К] [x≠0] [8] | 78 |
| [К] [x≠0] [9] | 79 |
| [К] [x≠0] [a] | 7A |
| [К] [x≠0] [в] | 7B |
| [К] [x≠0] [c] | 7C |

*Table 4 continued (p. 55)*

| Keys | Code |
|---|---|
| [К] [x≠0] [d] | 7D |
| [К] [x→П] [0] | B0 |
| [К] [x→П] [1] | B1 |
| [К] [x→П] [2] | B2 |
| [К] [x→П] [3] | B3 |
| [К] [x→П] [4] | B4 |
| [К] [x→П] [5] | B5 |
| [К] [x→П] [6] | B6 |
| [К] [x→П] [7] | B7 |
| [К] [x→П] [8] | B8 |
| [К] [x→П] [9] | B9 |
| [К] [x→П] [a] | BA |
| [К] [x→П] [в] | BB |
| [К] [x→П] [c] | BC |
| [К] [x→П] [d] | BD |
| [К] [П→x] [0] | D0 |
| [К] [П→x] [1] | D1 |
| [К] [П→x] [2] | D2 |
| [К] [П→x] [3] | D3 |
| [К] [П→x] [4] | D4 |
| [К] [П→x] [5] | D5 |
| [К] [П→x] [6] | D6 |
| [К] [П→x] [7] | D7 |
| [К] [П→x] [8] | D8 |
| [К] [П→x] [9] | D9 |
| [К] [П→x] [a] | DA |
| [К] [П→x] [в] | DB |
| [К] [П→x] [c] | DC |
| [К] [П→x] [d] | DD |

*(p. 56)*

6.1.6. The location of a code in program memory is determined by its address (a two-digit number from 00 to 97).

6.1.7. To control the sequence in which commands are written and executed, the calculator has an address counter. This counter can be set to any starting address (from 00 to 97).

6.1.8. When a command is entered into program memory, the contents of the counter increase by one. Thus the sequence in which the program's commands are executed corresponds to the sequence of key presses during programming. However, this method is acceptable only for solving problems that are not very complex.

6.1.9. So that the sequence in which commands are executed can differ from the sequence in which they are written in the program, so that individual parts are repeated, and so that the sequence of execution changes depending on intermediate results of the calculations, the calculator has commands that change the contents of the address counter. These commands are called jump commands.

6.1.10. The contents of the address counter are changed according to a jump address written either in program memory, or in the addressable registers, or in the five-place return stack, a special memory area (see subsection 6.3).

6.1.11. If the jump address is written in an addressable register, this addressing is called indirect. Indirect addressing is also used when the addressable registers are accessed. In this case, instead of a direct indication of the number of the addressable register, the program contains an indirect number, i.e. the number of the addressable register in which the number of the register being called is stored. The number of the addressable register is not simply (p. 57) stored but is changed in a definite way (see 6.3.5).

6.1.12. In Programming mode the display is used to show the codes of three consecutive commands from program memory and the current state of the command counter, i.e. the address at which the next command will be written.

For example, the display shows

`02  01  0E  06`

In this case the two-digit operation commands on the display mean:

1) code 06 — the current state of the address counter;
2) codes 0E, 01, 02 — three consecutive commands, located at addresses 03, 04, 05 respectively.

### 6.2. Stages of calculation by program

*(p. 57)*

Calculations by program are carried out in the following order:

1) programming the problem;
2) entering the program into memory and editing the program;
3) debugging the program;
4) entering the initial data and executing the program.

6.2.1.1. We shall consider the programming of simple problems using the example of the area of a circle. The programming of complex problems will be considered in subsection 6.3.

To calculate the area of a circle we use the formula

S = πd²/4,

where d is the diameter of the circle.

*(p. 58)*

When composing the program, we assume that the given value of the diameter d has been written beforehand into addressable register RG2. To calculate the area of the circle, the value of the diameter d must be called into register X by pressing the keys [П→x] and [2], and then the following keys must be pressed in sequence:

[F] [x²] [В↑] [F] [π] [×] [4] [÷]

This sequence of key presses constitutes the program for solving the given problem.

This problem can be solved manually, by pressing the necessary keys in sequence, or automatically, by writing the program into memory in Programming mode.

For convenience in working with a program, it is usually laid out as a table, which gives the address of the command in program memory, the keys that must be pressed, and the operation codes that correspond to these keys.

The program for calculating the area of a circle S is given in Table 5.

Table 5

| Command address | Key pressed | Operation code | Content of the operation |
|---|---|---|---|
| 00 | [П→x] [2] | 62 | Recall of the value of the diameter d from register RG2 |
| 01 | [F] [x²] | 22 | Calculation of the value d² |
| 02 | [В↑] | 0E | Sending the value d² to register Y |
| 03 | [F] [π] | 20 | Recall of the constant π |
| 04 | [×] | 12 | Calculation of πd² |
| 05 | [4] | 04 | Entry of the number 4 into register X |
| 06 | [÷] | 13 | Calculation of S = πd²/4 |
| 07 | [С/П] | 50 | Stop to display the result |

*(p. 59)*

Note. At address 07 the program contains a stop command for displaying the contents of the register when the area of the circle S is calculated automatically by the program. If this command is not in the program, all 98 program steps are executed.

6.2.1.2. To compose branching programs and repeated passes through individual parts of programs (subroutines), jump commands (direct and indirect) and loop commands are used. In the program being composed, the jump address must follow jump commands (direct) and loop commands. The jump address for an indirect command is contained in the command itself (see subsection 6.3).

6.2.1.3. When a program is composed, the jump address is written with two digits. Moreover, if the jump address is part of an indirect jump command, it must be written into the addressable register whose index will be part of the indirect jump command (see subsection 6.3).

6.2.1.4. The presence of a return stack in the calculator allows subroutines to be created inside programs. The depth of subroutines is determined by the capacity of the stack and is equal to five. The stack register works on the principle "first in, last out" (see 6.3.3, 6.3.4, 6.3.7).

6.2.1.5. For automatic stopping and display of the result of the calculations, the program must contain the stop command [С/П].

#### 6.2.2. Entering the program into memory and editing the program

*(p. 60)*

6.2.2.1. The program for solving a problem may start at address 00 or at any arbitrary address.

To enter a program from address zero, in Automatic mode (АВТ) press the program counter clear key [В/О] and go to Programming mode by pressing the keys [F], [ПРГ]. The display then shows counter address 00, from which the program will be entered. The program is entered by pressing the keys written in the program. The operation entered with the keys is checked on the display:

| Keys pressed | Display | |
|---|---|---|
| [В/О] | | Contents of register X before the key was pressed |
| [F] [ПРГ] | `00` | Counter address set to 00 |
| [П→x] [2] | `62  01` | Code written for calling information from register RG2 into register X |
| [F] [x²] | `22  62  02` | Code written for squaring the number in register X |
| [В↑] | `0E  22  62  03` | Code written for transferring information from register X to register Y |

To enter a program from an arbitrary address, this address must be set on the command address counter. To do this, (p. 61) in Automatic mode press the key [БП], and then the digit keys that provide the jump to the required address. After switching to Programming mode, the command address counter will be set to the address from which the program is to be entered. The program is entered into program memory by pressing the corresponding keys.

| Keys pressed | Display | |
|---|---|---|
| [БП] [0] [2] | | Contents of register X before the keys were pressed |
| [F] [ПРГ] | `22  62  02` | The counter will be set to address 02, and the display will show the information written at the preceding addresses |

6.2.2.2. If an error was made when the program was entered, to correct it you must go to the address at which the erroneous command is written. For this you can use the keys [ШГ→] or [ШГ←] if the address of the erroneous command is not far from the current one. Each press of these keys increases or decreases, respectively, the contents of the command address counter by one. Moreover, if the error was made in a jump address, to correct it the information must be shifted by two steps and the command and the jump address following it must be entered again. When the difference between the addresses of the erroneous and current commands is large, the unconditional jump command must be used. To do this, go to Automatic mode, press the key [БП], and then the digit keys that provide the jump to the needed address. After Programming mode is set, the display will show the address of the erroneous command. Correct the error (p. 62) by pressing the key of the required operation or command.

6.2.2.3. If any command needs to be removed from the program, go to the address of the command to be removed, and then press the keys [К] and [НОП]. The command "No operation" is written into program memory; during calculation it does nothing.

#### 6.2.3. Debugging the program

*(p. 62)*

6.2.3.1. The program is debugged in Automatic mode. To switch to this mode, press the keys [F] and [АВТ]. Type the initial data for the program on the keyboard and, if necessary, store them in a memory register. Press the key [В/О] if the program starts at address 00, or the key [БП] if the program starts at an arbitrary address. Then press the digit keys that start the program from the required address.

6.2.3.2. When the key [ПП] is pressed in Automatic mode, the program for solving the problem is executed one command at a time. Press the key [ПП] and analyse the execution of each program step. Correct any errors found as described in 6.2.2.2, 6.2.2.3. When viewing program execution step by step, keep in mind that the execution of a jump command and the setting of the jump address are carried out in one program step.

#### 6.2.4. Entering the initial data and executing the program

*(p. 63)*

6.2.4.1. Type the initial data for solving the problem on the keyboard and, if necessary, store them in the memory registers. Press the key [В/О] if the program starts at address 00, or the key [БП] if the program starts at an arbitrary address. Then press the keys that start the program from the required address.

6.2.4.2. Press the program start key [С/П]. Illumination of the display indicates that the program is running. The execution time of the program depends on its length and on the nature of the calculations.

After the program has finished, read the result on the display.

6.2.4.3. In the event of looping, i.e. endless repetition of some part of the program, the program must be stopped by pressing the key [С/П], and then the program must be checked and the cause of the looping removed.

6.2.4.4. To carry out repeated calculations with a debugged program, write new initial data into memory and restart the program from the required address.

ATTENTION! When the power is switched off, all registers of the calculator, including those that make up the program memory, are cleared. Therefore, to keep a program for a certain time, the power of the calculator must not be switched off. Otherwise the program will have to be entered again.

For example, calculate the area of a circle if its diameter D equals 4; 5; 1,8 cm.

To calculate the area of the circle by program, carry out the following operations:

*(p. 64)*

1) go to Programming mode at address 00 by pressing the keys [В/О], [F], [ПРГ];
2) enter the program (Table 5);
3) go to Automatic mode by pressing the keys [F], [АВТ];
4) enter the number 4 into register RG2 by pressing the keys [4] [x→П] [2];
5) start the program from address 00 by pressing the keys [В/О], [С/П];
6) read the result on the display: `12,56637` cm².

To calculate the area of a circle with a diameter of 5 and 1,8 cm, do the following:

| Keys pressed | Display |
|---|---|
| [5] [x→П] [2] [В/О] [С/П] | `19,634953` |
| [1] [.] [8] [x→П] [2] [В/О] [С/П] | `2,54469` |

[^tn1]: Translator's note: Table 4 contains no rows for [F] [⟳] or [F] [Bx]. The code 0F for [F] [Bx] appears only in the functional test (Appendix, test 82).
