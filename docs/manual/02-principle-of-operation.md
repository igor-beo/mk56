# Principle of Operation of the Calculator

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

---

## 2.2. Principle of operation of the calculator

*(p. 8)*

2.2.1. The block diagram of the calculator is shown in Fig. 1.

*Figure 1: block diagram of the calculator, drawn rotated on the page (see scan p.9)*

*(p. 9)*

Labels printed in Figure 1 (title: «СТРУКТУРНАЯ СХЕМА МИКРОКАЛЬКУЛЯТОРА», "Block diagram of the calculator"):

| Group | Block / label as printed | Translation |
|---|---|---|
| Устройство индикации | Сегментные ключи, D1 | Display unit: segment switches, D1 |
| Устройство индикации | Разрядные ключи, D2 | Display unit: digit switches, D2 |
| Устройство индикации | Разрядные ключи, D3 | Display unit: digit switches, D3 |
| Устройство индикации | Индикатор | Display unit: display |
| Устройство операционное | Регистровая часть БИС управления, D4 | Operational unit: register part, control LSI, D4 |
| Устройство операционное | Регистровая часть, Операционная БИС, D5 | Operational unit: register part, operational LSI, D5 |
| Устройство операционное | Динамический регистр, D6 | Operational unit: dynamic register, D6 |
| Устройство операционное | Динамический регистр, D7 | Operational unit: dynamic register, D7 |
| Электронный блок | Генератор фаз, D8; outputs Ф1, Ф2, Ф3, Ф4 | Electronic unit: phase generator, D8; outputs Ф1, Ф2, Ф3, Ф4 |
| Электронный блок | Преобразователь напряжения; outputs −15В, −27В, −35В, ~5В, ~5В; input 220В | Electronic unit: voltage converter; outputs −15 V, −27 V, −35 V, ~5 V, ~5 V; input 220 V |
| Устройство ввода | Блоки клавиатуры; outputs К1, К2, К3 | Input unit: keyboard blocks; outputs К1, К2, К3 |
| Signal labels | Э1…Э8; Д2…Д13; СИ | Э1…Э8; Д2…Д13; СИ |

*(p. 10)*

2.2.2. The system of base LSIs (large-scale integrated circuits) D4 … D7 is built on the К145 series. The central device of the calculator is the control LSI D4. It controls the operation of the calculator: it receives information from the keyboard and from the LSIs D5 … D7 and, after processing, passes it to the display in the form of the segment code Э1 … Э8. The display is driven sequentially, digit by digit, by the decimal-digit signals D2 … D13, which are produced by LSI D4 and fed to the digit switches (the inputs of microcircuits D2, D3) and from their outputs to the grids of the display, and by the segment-code signals Э1 … Э8, which are fed to the anode switches of the display (the inputs of microcircuit D1) and then to the anodes of the display. A voltage of minus 35 V is applied to the cathode of the display through a Zener diode. When zero-level signals coincide in time on the grid and on the anodes of the display, a digit lights up in the corresponding position of the display.

2.2.3. The operational unit of the calculator is organized by connecting the memory registers of LSIs D4 … D7 in series into a ring. This forms a random-access memory with a common memory field accessible to each functional LSI. The operation of LSI D5 is synchronized by the sync pulse (СИ) produced by D4.

2.2.4. The control LSI D4 monitors the input of information from the keyboard, interprets the entered information and, depending on its kind, "takes one decision or another". It also outputs information to the display and ensures the functioning of the system in the mode of executing operations defined by the language and functional capabilities of the calculator. A program is entered into the RAM from the keyboard in programming mode, which is set by pressing the keys [F] (prefix)

*(p. 11)*

and [ПРГ] (Programming mode). In addition, LSI D4 performs all programming operations and the exchange of data between the addressable memory registers and the automatic stack memory.

The operational LSI D5 performs all arithmetic, algebraic and trigonometric operations, and also the operations with the stack memory.

Two memory registers on microcircuits D6 and D7, each with a capacity of 1008 bits, make it possible to extend the memory of the calculator to 14 addressable registers and 4 stack registers, and also to organize one return register. Information can be entered into the RAM and output from it through one of the memory registers of the functional LSIs.

2.2.5. The calculator is controlled from the keyboard. With thirty keys the calculator automatically performs fifty-one operations. The keys have double and triple symbols. One symbol is shown directly on the key, the second on the key panel directly above the key to which it belongs, and the third directly below the key to which it belongs. The layout and symbols of the calculator keys are shown in Fig. 2.

The functions of the keys are given in Tables 2 and 3.

Information about the entered numbers and the operations on them is issued in the form of the signals К1, К2, К3, obtained by switching the digit signals Д through the keyboard. Signal К1 carries information about the entered digits, signal К2 about operations and the decimal point, and signal К3 about the transition to operations of the second and third symbols and to operations with the program.

*(p. 12)*

*Figure 2: layout and symbols of the calculator keys, drawn rotated on the page (see scan p.12)*

Figure 2 («РАСПОЛОЖЕНИЕ И СИМВОЛИКА КЛАВИШ МИКРОКАЛЬКУЛЯТОРА») shows three key blocks. Each cell gives the symbol above the key / the symbol on the key / the symbol below the key; "—" means nothing is printed.

Left block:

| | Column 1 | Column 2 | Column 3 |
|---|---|---|---|
| Row 1 | x<0 / ШГ (with arrow) / — | L3 / ПП / — | — / F / — |
| Row 2 | x=0 / ШГ (with arrow) / — | L2 / БП / — | — / К / — |
| Row 3 | x≥0 / В/О / — | L1 / x→П / — | |
| Row 4 | x≠0 / С/П / — | L0 / П→x / — | |

Middle block:

| | Column 1 | Column 2 | Column 3 |
|---|---|---|---|
| Row 1 | sin / 7 / — | cos / 8 / — | tg / 9 / — |
| Row 2 | sin⁻¹ / 4 / — | cos⁻¹ / 5 / — | tg⁻¹ / 6 / — |
| Row 3 | eˣ / 1 / — | lg / 2 / — | ln / 3 / — |
| Row 4 | 10ˣ / 0 / НОП | ⟳ / · / a | АВТ / /-/ / в |

Right block:

| | Column 1 | Column 2 |
|---|---|---|
| Row 1 | √ / − / — | 1/x / ÷ / — |
| Row 2 | π / + / — | x² / × / — |
| Row 3 | Bx / В↑ / — | xʸ / ↔ / — |
| Row 4 | ПРГ / ВП / c | CF / Cx / d |

*(p. 13)*

**Table 2. Functions of the function keys**

| Keys | Function of the keys |
|---|---|
| [0] … [9] | Digit keys, which enter the digits 0 to 9 into register X |
| [·] | Key for entering the decimal point |
| [В↑] (enter) | Key for transferring the contents of register X to register Y and moving the information in the stack |
| [Cx] (clear X) | Key for clearing the contents of register X |
| [+] | Addition key |
| [−] | Subtraction key |
| [÷] | Division key |
| [×] | Multiplication key |
| [↔] (swap X and Y) | Key for exchanging the contents of registers X and Y |
| [/-/] (change sign) | Key for changing the sign of the number or of the exponent |
| [ВП] (enter exponent) | Preparatory key for entering the exponent of a number |
| [F] | Prefix key. Used when performing operations with the keys of the second symbol, printed on the front panel |
| [F] [10ˣ] | Calculation of the power function 10ˣ |
| [F] [eˣ] | Calculation of the exponential function eˣ |
| [F] [lg] | Calculation of the decimal logarithm |
| [F] [ln] | Calculation of the natural logarithm |
| [F] [sin] | Calculation of the sine function |
| [F] [cos] | Calculation of the cosine function |

*(p. 14)*

*Continuation of Table 2*

| Keys | Function of the keys |
|---|---|
| [F] [tg] | Calculation of the tangent function |
| [F] [sin⁻¹] | Calculation of the inverse sine function |
| [F] [cos⁻¹] | Calculation of the inverse cosine function |
| [F] [tg⁻¹] | Calculation of the inverse tangent function |
| [F] [√] | Calculation of the square root |
| [F] [1/x] | Calculation of the reciprocal of x |
| [F] [x²] | Squaring the number x |
| [F] [xʸ] | Raising the number x to the power y |
| [F] [π] | Calling the constant π=3,1415926 |
| [F] [⟳] | Circular movement of information in the stack |
| [F] [Bx] (recall previous result) | Restoring the previous result |
| [F] [CF] | Cancelling the action of the prefix key |
| [x→П] (store) | Writing the contents of register X into a memory register |
| [x→П] [0] … [x→П] [9] | Writing the contents of register X into registers 0 … 9 respectively |
| [a]; [в]; [c]; [d] | Keys for addressing memory registers a, в, c, d |
| [x→П] [a] … [x→П] [d] | Writing the contents of register X into registers a … d respectively |
| [П→x] (recall) | Calling the contents of a memory register into register X |
| [П→x] [0] … [П→x] [9] | Calling the contents of register 0 … 9 respectively into register X |

*(p. 15)*

*Continuation of Table 2*

| Keys | Function of the keys |
|---|---|
| [П→x] [a] … [П→x] [d] | Calling the contents of registers a … d respectively into register X |

Note. In the table and in the following sections only those key symbols are shown that are needed to perform the given operation.

**Table 3. Functions of the keys used in programming**

| Keys | Function of the keys |
|---|---|
| [F] [ПРГ] | Switching to Programming mode (ПРГ) |
| [F] [АВТ] | Switching to Automatic mode (АВТ) |
| [БП] (go to) | Key for unconditional jump to an address |
| [F] [x<0]; [F] [x=0]; [F] [x≥0]; [x≠0] [^tn1] | Execution of the conditional jump instructions on the conditions x<0, x=0, x≥0, x≠0 respectively |
| [ПП] (subroutine call; step in automatic mode) | Key for jump to a subroutine. Performs: 1. Jump to a subroutine in Programming mode; 2. Step-by-step execution of the program in Automatic mode. |
| [В/О] (return; reset to 00) | "Return/zeroing" key. Performs: 1. Return from a subroutine in Programming mode; 2. Jump to the zero address in Automatic mode |

*(p. 16)*

*Continuation of Table 3*

| Keys | Function of the keys |
|---|---|
| [С/П] (stop/start) | "Stop/start" key. Performs: 1. Stopping the program in Programming mode and holding the contents of register X on the display; 2. Starting calculation by program in Automatic mode, and also stopping the calculation in the case of an endless loop |
| [F] [L0]; [F] [L1]; [F] [L2]; [F] [L3] | Execution of the loop-organizing instruction with registers 0, 1, 2, 3 respectively |
| [К] | Prefix key for indirect jumps and indirect access to the addressable registers |
| [К] [БП] [0] … [К] [БП] [d] | Execution of the indirect unconditional jump instruction to a modified address stored in the addressable register whose index is part of the instruction |
| [К] [x=0] [0] … [К] [x=0] [d]; [К] [x≠0] [0] … [К] [x≠0] [d]; [К] [x≥0] [0] … [К] [x≥0] [d]; [К] [x<0] [0] … [К] [x<0] [d] | Execution of the indirect jump instructions on the conditions x=0, x≠0, x≥0, x<0 respectively; when they are executed, a jump is made to a modified address stored in the addressable register whose index is part of the instruction |

*(p. 17)*

*Continuation of Table 3*

| Keys | Function of the keys |
|---|---|
| [К] [ПП] [0] … [К] [ПП] [d] | Execution of an indirect jump to a subroutine at a modified address stored in the addressable register whose index is part of the instruction |
| [К] [x→П] [0] … [К] [x→П] [d] | Execution of indirect writing of the contents of register X into a register by a modified code stored in the address register whose index is part of the instruction |
| [К] [П→x] [0] … [К] [П→x] [d] | Execution of indirect display of the call into register X of the contents of an addressable register by the modernized [^tn2] code stored in the addressable register whose index is part of the instruction |
| [К] [НОП] | Execution of the "No operation" instruction, used when editing a program |
| [ШГ] (with arrow) | "Step forward" key. Provides, in Programming mode, step-by-step passage through the program in order of increasing addresses |

*(p. 18)*

*Continuation of Table 3*

| Keys | Function of the keys |
|---|---|
| [ШГ] (with arrow) | "Step back" key. Provides, in Programming mode, step-by-step passage through the program in order of decreasing addresses |

Notes: 1. The functions of the programmable keys are given in the most general form. The functions of the keys will be considered in more detail in the section "Programming".

2. In the table and in the following sections only those key symbols are shown that are needed to perform the given operation or instruction.

2.2.6. The phase generator (microcircuit D8) provides pulse power to the LSIs. The phase generator produces four series of phase pulses of negative polarity. The repetition frequency of the phase pulses is 95 ± 5 kHz.

2.2.7. The voltage converter (ПН) converts the voltage supplied from the mains into the stabilized voltage of minus 15 V needed to power all the LSIs, the voltage of minus 27 V for powering the anode and grid switches of the display (microcircuits D1 … D3), and the unstabilized voltage of minus 35 V needed to power the anode and grid circuits of the display. The ПН produces an alternating voltage of 5 V needed to power the filament circuit of the display.

[^tn1]: Translator's note: the scan prints the last key of this group as [x≠0] without a preceding [F].
[^tn2]: Translator's note: printed «модернизированному» ("modernized"); the parallel rows of this table use «модифицированному» ("modified").
