# Purpose and Functional Capabilities

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

---

## Title page

*(cover, PDF page 1)*

**MICROCALCULATOR "ELEKTRONIKA MK 56"**

Technical Description and Operating Instructions

*The cover also carries handwritten owner's notes that are not part of the printed text.*

---

## Contents

*(p. 3–4)*

| Section | Page |
|---|---|
| 1. Purpose | 5 |
| 2. Design and principle of operation of the calculator | 5 |
| 2.1. Functional capabilities | 5 |
| 2.2. Principle of operation of the calculator | 8 |
| 2.3. Construction | 19 |
| 3. Safety instructions | 20 |
| 4. Preparing the calculator for operation | 20 |
| 5. Operating the calculator in automatic mode | 20 |
| 5.1. Calculation mode | 20 |
| 5.2. Representation of a number on the display | 21 |
| 5.3. Entering numbers | 21 |
| 5.4. Incorrect operations and overflow | 24 |
| 5.5. Performing one-place operations | 25 |
| 5.6. Performing two-place operations | 27 |
| 5.7. Using the stack memory | 34 |
| 5.8. Using the previous-result register | 43 |
| 5.9. Using the addressable registers | 48 |
| 5.10. Cancelling an erroneously pressed [F] key | 50 |
| 6. Operating the calculator in "Programming" mode | 50 |
| 6.1. General information | 50 |
| 6.2. Stages of calculation by programs | 57 |
| 6.3. Jump instructions | 64 |
| 7. Examples of calculations by programs | 85 |
| 7.1. Finding compound interest | 85 |
| 7.2. Calculating the sum (S) or product (P) of a number sequence | 89 |
| 7.3. Calculating the mathematical expectation of a statistical set of values | 89 |
| 7.4. The "ballistic" problem of a body thrown at an angle to the horizontal | 90 |
| 8. Maintenance of the calculator | 94 |
| 9. Transportation and storage | 95 |
| Appendix. Functional check test of the calculator | 96 |

Page 4 of the scan also carries a typed note added by the person who scanned the document in 2010 (ru-hpc.narod.ru). It is not part of the original manual and is not translated here.

---

## 1. PURPOSE

*(p. 5)*

1.1. The desktop calculator "Elektronika MK56" is intended for automating the solution of scientific, technical, statistical, engineering and other problems that require programming, and for use in various branches of the national economy.

---

## 2. DESIGN AND PRINCIPLE OF OPERATION

*(p. 5)*

### 2.1. Functional capabilities

*(p. 5)*

2.1.1. The number system for input and output of information is decimal.

2.1.2. Number of mantissa digits: eight.

2.1.3. Number of exponent digits: two.

2.1.4. Range of calculations: 1·10⁻⁹⁹ ≤ |x| ≤ 9,9999999·10⁹⁹.

2.1.5. Form of representation of the decimal point:

1) in the range 1 ≤ |x| ≤ 99999999: natural;
2) in the ranges 1·10⁻⁹⁹ ≤ |x| < 1 and 99999999 < |x| ≤ 9,9999999·10⁹⁹: floating.

2.1.6. Entered numbers and results of calculations are shown on a 12-digit luminescent display (eight mantissa digits, two exponent digits, two digits for the signs of the mantissa and the exponent).

2.1.7. The calculator works in two modes: in Automatic mode (АВТ) and in Programming mode (ПРГ).

2.1.8. In Automatic mode the calculator makes it possible:

1) to perform the four arithmetic operations "+", "−", "×", "÷";

*(p. 6)*

2) to calculate the direct trigonometric functions sin x, cos x, tg x. The argument x may be entered in radians, in degrees and in grads;
3) to calculate the inverse trigonometric functions arcsin x, arccos x, arctg x in radians, in degrees and in grads;
4) to calculate the functions xʸ, ln x, lg x, eˣ, 10ˣ, √x, x², 1/x;
5) to call the constant π into the operational register X;
6) to write information into 14 memory registers;
7) to call information into register X from the 14 memory registers;
8) to write information into the stack registers and to control its movement;
9) to change the sign of the number in register X;
10) to exchange information between the operational registers X and Y;
11) to clear the operational register X and the instruction of the prefix key;
12) to restore the previous result of calculations;
13) to perform calculations with a constant;
14) to perform chain calculations;
15) to perform calculations by program.

2.1.9. In Programming mode the calculator makes it possible:

1) to write a program using the keyboard;
2) to edit and correct the program.

2.1.10. Calculation time of the arithmetic operations and of the operations 1/x, √x, x²: not more than 0,5 s.

Calculation time of the function xʸ: not more than 3,5 s.

Average calculation time of the functions ln x, lg x, eˣ, 10ˣ, sin x, cos x, tg x, arcsin x, arccos x, arctg x: not more than 2 s.

*(p. 7)*

2.1.11. When calculating trigonometric, logarithmic and exponential functions, the permissible argument values and the relative error given in Table 1 must be taken into account.

**Table 1**

| Function | Permissible argument values | Maximum relative error |
|---|---|---|
| sin x | 1·10⁻⁴⁹ < \|x\| < 10¹⁰ | 3·10⁻⁷ |
| cos x | 1·10⁻⁴⁹ < \|x\| < 10¹⁰ | 3·10⁻⁷ |
| tg x | 1·10⁻⁴⁹ < \|x\| < 10¹⁰ | 3·10⁻⁷ |
| arcsin x | \|x\| ≤ 1 | 3·10⁻⁷ |
| arccos x | \|x\| ≤ 1 | 3·10⁻⁷ |
| arctg x | \|x\| ≤ 9,9999999·10⁹⁹; \|x\| ≥ 1·10⁻⁹⁹ | 3·10⁻⁷ |
| xʸ | 0 < x | 1·10⁻⁶ |
| eˣ | \|x\| < 100·ln 10 | 5·10⁻⁶ |
| x² | \|x\| < 10⁵⁰ | 1·10⁻⁷ |
| 10ˣ | \|x\| < 99,999999 | 4·10⁻⁷ |
| 1/x | x ≠ 0 | 1·10⁻⁷ |
| √x | 0 < x | 1·10⁻⁴ |
| ln x | 0 < x | 3·10⁻⁷ |
| lg x | 0 < x | 3·10⁻⁷ |

2.1.12. To extend the capabilities in the field of programming, and for convenience in checking and debugging programs, the calculator provides:

1) a special memory with a capacity of ninety-eight program steps;
2) instructions for direct and indirect jumps to a program and an instruction for return from a program;

*(p. 8)*

3) the possibility of calling a subroutine within a program. The depth of such calls is 5;
4) instructions for direct and indirect unconditional jump;
5) four types of instructions for direct and indirect conditional jump (on the conditions x=0, x≠0, x≥0, x<0);
6) instructions for organizing loops;
7) instructions for indirect writing of the contents of register X into the memory registers;
8) instructions for indirect display of the contents of the memory registers;
9) instructions for resetting the address counter to the zero state;
10) an instruction for start and stop during automatic calculation by program;
11) an instruction for step-by-step execution of the program in Automatic mode;
12) display of the codes of three consecutive program steps and of the current state of the address counter;
13) keys for stepping through the program in the direction of increasing or decreasing addresses during visual checking of the program.

2.1.13. The time for the calculator to become ready for operation after switching on is not more than 30 s. The calculator may be switched on again not less than 10 s after switching off.

2.1.14. Round-the-clock operation without switching off, and with switching off for any period, is permitted.
