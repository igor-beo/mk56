# Operating the Calculator in Automatic Mode

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

---

## 5. OPERATING THE CALCULATOR IN AUTOMATIC MODE

*(p. 20)*

### 5.1. Calculation mode

*(p. 20)*

5.1.1. Calculations on the calculator are performed in Automatic mode (АВТ). This mode is set automatically after the calculator power is switched on, or after the keys [F] [АВТ] are pressed if the calculator was previously in Programming mode (ПРГ).

### 5.2. Representation of a number on the display

*(p. 21)*

5.2.1. Numbers in the range from 1 to 10⁸−1 are shown on the display in natural form, and in the ranges from 10⁻⁹⁹ to 0 and from 10⁸ to 9,9999999·10⁹⁹ in floating-point form.

For example, the number −494751,23 is shown on the display in natural form and looks as follows:

*Figure: display showing a number in natural form (see scan p.21)*

| Display | Labels in the figure |
|---|---|
| `-494751, 23` | "8 digits of the number" (brace over the digits); "Sign of the number" (arrow to the minus sign); "Decimal comma" (arrow to the comma) |

Since any number can be represented in the form m·10ⁿ, where m is the mantissa and n is the exponent of the number, the number −0,0123456 can be represented in the form −1,23456·10⁻².

On the display this number will be shown in floating-point form.

*Figure: display showing a number in floating-point form (see scan p.21)*

| Display | Labels in the figure |
|---|---|
| `-1,23456 -02` | "Mantissa of the number" (brace under 1,23456); "Sign of the mantissa of the number" (arrow to the first minus sign); "Exponent of the mantissa" and "Sign of the exponent of the mantissa" (brace and arrow at −02) |

### 5.3. Entering numbers

*(p. 21)*

5.3.1. For receiving, storing and outputting initial results, the calculator has special functional units: registers.

5.3.2. The calculator has two operational registers, X and Y.

*(p. 22)*

Register X serves to receive and store the number being entered and the result of calculations. Its contents are shown on the display.

Register Y serves to receive information from register X, which makes it possible, when necessary, to enter a second number into register X. A number is entered into register Y when the [В↑] (enter) key is pressed.

5.3.3. The calculator operates on positive and negative decimal numbers.

5.3.4. Enter a number by pressing the digit keys in the order of the digits. If the number is fractional, first enter the integer part, then press the [·] key and enter the fractional part. For example, to enter the number 148,12 press the keys [1] [4] [8] [·] [1] [2]. Check the number on the display: `148,12`

5.3.5. When entering a negative number, press the change-sign key [/-/] (change sign) after typing the last digit of the number. As an example, take the number 148,12 that is on the display. Press the [/-/] key. The display shows `-148,12`.

If the sign of the displayed number must be changed, press the [/-/] key. For example, the number −148,12 is displayed. Press the [/-/] key. The display will show `148,12`.

5.3.6. If an error was made when entering a number, press the register X clear key [Cx] (clear X) and type the number again. For example, the display shows the incorrectly typed number 148,12. We press the [Cx] key, and the display shows `0,`.

5.3.7. To enter a number with an exponent, first enter the mantissa of the number, then press the [ВП] (enter exponent) key and enter the digits of the

*(p. 23)*

exponent. If the exponent is negative, press the [/-/] key after entering it.

For example, the number −148,12·10¹⁵ is entered as follows:

| Keys pressed | Display |
|---|---|
| [1] [4] [8] [·] [1] [2] | `148,12` |
| [/-/] | `-148,12` |
| [ВП] | `-148,12 00` |
| [1] [5] | `-148,12 15` |
| [/-/] | `-148,12 -15` |

5.3.8. If an error was made in typing the exponent, repeat the entry of the exponent and its sign (if necessary). Each new digit is entered into the low-order digit of the exponent, and the previous information is shifted one position to the left, with loss of the high-order digit of the exponent.

If the [ВП] key is pressed when the mantissa is zero, the mantissa takes the value "1" and the calculator gets ready to receive the value of the exponent.

5.3.9. Pressing the [В↑] key automatically normalizes the number on the display and passes a copy of the number in register X to register Y.

For example, the display shows the number −148,12·10⁴.

After the [В↑] key is pressed the display will show `-1481200,`

Note. The calculator has an input lock once eight mantissa digits have been entered. In this case pressing digit keys causes no change on the display.

### 5.4. Incorrect operations and overflow

*(p. 24)*

5.4.1. Incorrect operations are:

- division by "0";
- raising the number x to the power y if x=0 and y≧0;
- extracting the square root if x<0;
- finding the reciprocal -1/x if x=0;
- calculating the decimal logarithm if x≤0;
- calculating the natural logarithm if x≤0;
- calculating the inverse trigonometric functions arcsin, arccos if the absolute value |x|>1.

5.4.2. When an incorrect operation is performed, the error signal "ЕГГОГ" (error) lights up on the display.

A similar signal appears if the calculations give a value that exceeds the capabilities of the calculator (a number greater than ±9,9999999·10⁹⁹ or less than 1,0000000·10⁻⁹⁹). In the latter case register X is set to zero.

After the "ЕГГОГ" signal appears, numbers can be entered and calculations performed.

For example, let us extract the square root of minus 4 and then enter the number 25 into register X.

| Keys pressed | Display |
|---|---|
| [4] [/-/] | `-4` |
| [F] [√] | `ЕГГОГ` |
| [2] [5] | `25` |

### 5.5. Performing one-place operations

*(p. 25)*

5.5.1. When calculating logarithmic (ln, lg), power (xʸ, eˣ, 10ˣ), direct and inverse trigonometric (sin, cos, tg, arcsin, arccos, arctg) functions, and also when calculating the square root, finding the reciprocal (1/x) and calling a number, one number is entered. Therefore the operations of calculating these functions are called one-place operations. These operations are performed on the number in register X. The result of a one-place operation is written into register X; the contents of the other registers do not change.

5.5.2. The argument for calculating direct trigonometric functions, and the calculated argument of inverse trigonometric functions, can be in radians, in degrees or in grads, depending on the position of the Г/Р/ГРД (degree-radian-grad) switch.

To calculate trigonometric and inverse trigonometric functions:

1) set the Г/Р/ГРД switch to the position corresponding to the given or calculated argument;
2) type the number (the argument) on the keyboard;
3) press the [F] key;
4) press the key of the function to be calculated.

| Examples of calculations | Position of Г/Р/ГРД switch | Keys pressed | Display |
|---|---|---|---|
| sin 32 | "Р" | [3] [2] | `32,` |
| | | [F] [sin] | `5,5142714 -01` |
| cos 18° | "Г" | [1] [8] | `18,` |
| | | [F] [cos] | `9,5105655 -01` |
| tg 48,5° | "Г" | [4] [8] [,] [5] | `48,5` |
| | | [F] [tg] | `1,1302944` |
| arcsin 0,975 | "Р" | [0] [·] [9] [7] [5] | `0,975` |
| | | [F] [sin⁻¹] | `1,346721` |
| arccos 0,2 | "Р" | [0] [·] [2] | `0,2` |
| | | [F] [cos⁻¹] | `1,3694383` |
| arctg 41 | "Г" | [4] [1] | `41,` |
| | | [F] [tg⁻¹] | `88,602819` |
| sin 32 | "ГРД" | [3] [2] | `32,` |
| | | [F] [sin] | `4,8175367 -01` |

*(p. 26)*

5.5.3. To calculate the functions ln, lg, eˣ, 10ˣ, x², to extract the square root of a number, to find the reciprocal and to call the number π, the order of pressing the keys is the same as for calculating trigonometric functions. The Г/Р/ГРД switch may be in any position.

| Examples of calculations | Keys pressed | Display |
|---|---|---|
| ln 412 | [4] [1] [2] | `412,` |
| | [F] [ln] | `6,0210233` |
| lg 412 | [4] [1] [2] [F] [lg] | `2,6148971` |
| e¹² | [1] [2] [F] [eˣ] | `162754,78` |
| e^−0,48 | [0] [·] [4] [8] [/-/] [F] [eˣ] | `6,1878339 -01` |
| 10^4,75 | [4] [·] [7] [5] [F] [10ˣ] | `56234,135` |
| 10^−1,48 | [1] [·] [4] [8] [/-/] [F] [10ˣ] | `3,3113111 -02` |
| 0,745² | [0] [·] [7] [4] [5] [F] [x²] | `5,55025 -01` |
| 1/589 | [5] [8] [9] [F] [1/x] | `1,6977928 -03` |
| √563 | [5] [6] [3] [F] [√] | `23,727621` |
| π | [F] [π] | `3,1415926` |


### 5.6. Performing two-place operations

*(p. 27)*

5.6.1. When calculating arithmetic functions and the power function xʸ, two numbers are entered, so the operations for calculating them are called two-place operations. These operations are performed on the numbers in registers X and Y. The result of the operation is written into register X. The information that was stored in register Y before the operation is erased.

5.6.2. To perform two-place operations, at least two numbers must be entered into the calculator. Numbers are entered into the calculator in the usual way. To separate the first number from the second, press the [В↑] key.

5.6.3. The order of calculating arithmetic operations is as follows:

1) enter the first number;
2) press the enter key [В↑];
3) enter the second number;
4) press the operation key.

To calculate the example 12 + 3, press the keys:

| Keys pressed | |
|---|---|
| [1] [2] | First number |
| [В↑] | Separation of the first number from the second |
| [3] | Second number |
| [+] | Addition operation |

*(p. 28)*

The result of the addition, "15", is shown on the display.

| Examples of calculations | Keys pressed | Display |
|---|---|---|
| 12−3 | [1] [2] [В↑] [3] [−] | `9,` |
| 12×3 | [1] [2] [В↑] [3] [×] | `36,` |
| 12÷3 | [1] [2] [В↑] [3] [÷] | `4,` |

5.6.4. To raise the number x to the power y (xʸ):

1) enter the value of the exponent (the number y);
2) press the [В↑] key;
3) enter the value of the base (the number x);
4) press the [F] key, then [xʸ].

| Examples of calculations | Keys pressed | Display |
|---|---|---|
| 21,7^15,6 | [1] [5] [·] [6] | `15,6` |
| | [В↑] | `15,6` |
| | [2] [1] [·] [7] | `21,7` |
| | [F] [xʸ] | `7,0594552 20` |
| 4^−0,2 | [0] [·] [2] [/-/] | `-0,2` |
| | [В↑] | `-2, -01` |
| | [4] | `4,` |
| | [F] [xʸ] | `7,5785828 -01` |

5.6.5. If the display shows the result of previous calculations, typing a new number on the keyboard automatically moves the information from register X to register Y. Thus the result of calculating the previous

*(p. 29)*

operation can take part as the second number in subsequent calculations. Such calculations are usually called chain calculations.

5.6.6. When performing chain operations, the order of entering numbers and operations on them is the same as the order in which the calculations are written on paper.

**Problem 1.** Four resistances are connected in parallel in an electric circuit: R1=220 Ω, R2=4 kΩ, R3=560 Ω and R4=1,2 kΩ. The total resistance of the circuit must be determined. It is determined by the formula

R_общ. = 1 / (1/R1 + 1/R2 + 1/R3 + 1/R4) = 1 / (1/220 + 1/4000 + 1/560 + 1/1200);

With the calculator the total resistance of the circuit is calculated as follows.

| Keys pressed | Display | |
|---|---|---|
| [2] [2] [0] [F] [1/x] | `4,5454545 -03` | |
| [4] [0] [0] [0] [F] [1/x] | `2,5 -04` | |
| [+] | `4,7954545 -03` | |
| [5] [6] [0] [F] [1/x] | `1,7857142 -03` | |
| [+] | `6,5811687 -03` | |
| [1] [2] [0] [0] [F] [1/x] [+] | `7,414502 -03` | |
| [F] [1/x] | `134,87082` | Result of calculations |

*(p. 30)*

**Problem 2.** Determine the inductance of the oscillating circuit (Fig. 3) if the reactance of the circuit is X_L=12 kΩ, the source voltage is E=120 V, and the frequency is f=50 Hz. The inductance of this circuit is determined by the formula

L = X_L / (2πf) = 12000 / (2·π·50);

On the calculator the problem is solved as follows:

| Keys pressed | Display | |
|---|---|---|
| [1] [2] [0] [0] [0] [В↑] | `12000,` | |
| [2] [÷] | `6000,` | |
| [F] [π] [÷] | `1909,8593` | |
| [5] [0] [÷] | `38,197186` | Result of calculations, H |

**Problem 3.** Find the area of a segment (Fig. 4) if the radius of the circle is R=15,7 cm and the height (sagitta) of the segment is h=4,5 cm.

The area of the segment is determined by the formula

S_сегм. = ½ R²(α − sin α).

To use this formula, find the central angle α through the cosine of half the central angle:

cos (α/2) = (R−h)/R,

whence α = 2 arccos ((R−h)/R).

Thus the area of the segment is described by the formula

S_сегм. = ½ R² (2 arccos ((R−h)/R) − sin 2 arccos ((R−h)/R)) =

= ((15,7)²/2) (2 arccos ((15,7−4,5)/15,7) − sin 2 arccos ((15,7−4,5)/15,7))

*(p. 31)*

*Figure 3: circuit diagram with an AC source E, an inductor L and a resistor R in series (see scan p.31)*

*Figure 4: circle with centre O and chord AB; the hatched segment has height h and central angle α (see scan p.31)*

*(p. 32)*

Calculate S_сегм. with the calculator, setting the Г/Р/ГРД switch to the "Р" position:

| Keys pressed | Display | |
|---|---|---|
| [1] [5] [·] [7] [В↑] | `15,7` | |
| [4] [·] [5] [−] | `11,2` | |
| [1] [5] [·] [7] [÷] | `7,1337579 -01` | |
| [F] [cos⁻¹] | `7,764927 -01` | |
| [2] [×] | `1,5529854` | |
| [В↑] | `1,5529854` | |
| [F] [sin] | `9,998414 -01` | |
| [−] | `5,53144 -01` | |
| [В↑] | `5,53144 -01` | |
| [1] [5] [·] [7] [F] [x²] | `246,49` | |
| [×] | `136,34446` | |
| [2] [÷] | `68,17223` | Result of calculations, cm² |

**Problem 4.** Determine the maximum permissible operating frequency of the ferrite core К-132 with the overall dimensions: outer diameter D=4 mm, inner diameter d=2,5 mm, width h=1,5 mm, if the permissible overheating of the core is Δt=50° at a maximum temperature of +70°C.

*(p. 33)*

The maximum frequency of the core can be found by the formula

f_max = P / ( ΔΦl (H₀ + √(H₀² + P/(ΔΦl) · 4S)) )

where P is the power that the surface of the core can dissipate at the given temperature difference Δt.

The power P is determined by the formula

P = αt · S_охл · Δt

where αt is the heat-transfer coefficient (W/cm²·deg), which is taken on average to be 0,002 … 0,003;

S_охл is the cooling surface, which is determined in centimetres from the overall dimensions.

S_охл = (π/100)(D+d)[½(D−d)+h] = (π/100)·6,5·2,25

Substituting the values αt, S_охл, Δt into the formula, determine the dissipated power in watts

P = 0,0025 · (π/100) · 6,5·2,25·50

Determine the value of the magnetic flux of dissipation ΔΦ, taking into account the condition of remagnetization of the core from the state of negative magnetic induction −B_r to the state of positive magnetic induction +B

ΔΦ = 2 B_r q_c,

where q_c is the cross-section of the core.

Determine the mean length of the magnetic circuit l from the outer and inner diameters of the core: l = π·(D+d)/2

Determine the remagnetization constant S and the starting field strength

*(p. 34)*

H₀ from the magnetic characteristics of the ferrite core.

The values of S and H₀ for a temperature of +70°C are as follows:

H₀ = 0,28/(0,4π) A/cm; S = 0,33·10⁻⁶/(0,4π) A/cm·s; B_r = 0,125 T,

ΔΦ = 2·1250((4−2,5)/2)·1,5·10⁻⁸ Wb; l = π·(D+d)/(2·10) = π·6,5/20 cm,

whence

f_max = (25·2,25·50·20·10²·0,4π) / (1250·(1,5)²(0,28 + √((0,28)² + (0,4π·25·2,25·50·20)/(1250·(15)²)·4·0,33·10⁻⁴)))[^tn1]

The value of f_max is determined with the calculator as follows:

| Keys pressed | Display | |
|---|---|---|
| 0,4 [В↑] [F] [π] [×] 25 [×] 2,25 [×] | `70,685831` | |
| 50 [×] 20 [×] 1250 [÷] | `56,548665` | |
| 1,5 [F] [x²] [÷] 4 [×] | `100,53096` | |
| 0,33 [БП] (go to)[^tn2] 4 [/-/] [×] | `3,3175216 -03` | |
| 0,28 [F] [x²] [+] [F] [√] | `2,8586276 -01` | |
| 0,28 [+] 1,5 [F] [x²] [×] 1250 [×] | `1591,489` | |
| [F] [1/x] 25 [×] 2,25 [×] 50 [×] | `1,767213` | |
| 20 [ВП] 2 [×] 0,4 [×] [F] [π] [×] | `4441,4906` | Result of calculations in kHz |

### 5.7. Using the stack memory

*(p. 34)*

5.7.1. The stack memory consists of four registers X, Y, Z and T, which are organized on the principle of a magazine (push-down) memory, in which

*(p. 35)*

information written in sequence can be read only in the reverse order of writing (the last number written is the first).

5.7.2. After the calculator is switched on, the stack registers are in the zero state:

| Name of register | State of registers | |
|---|---|---|
| T | `0,` | |
| Z | `0,` | |
| Y | `0,` | |
| X | `0,` | Always displayed |

5.7.3. Numbers are always entered into register X. The information in the stack registers is shifted upward.

*Diagram (see scan p.35):*

| From | To |
|---|---|
| T | (arrow leads out of the diagram) |
| Z | T |
| Y | Z |
| X | Y |
| — | X |

5.7.4. Pressing the [В↑] key passes a copy of the number from register X to register Y, and also the contents of register Y to register Z and the contents of register Z to register T. The contents of register X are retained, and those of register T disappear. This movement (raising) of information can be shown as:

*Diagram (see scan p.35):*

| From | To |
|---|---|
| T | (arrow leads out of the diagram) |
| Z | T |
| Y | Z |
| X | Y |
| X | X |

5.7.5. Pressing the keys [F] [⟳] and [↔] (swap X and Y) leads to the following movement of information:

*Diagram for [F] [⟳] (see scan p.35):*

| From | To |
|---|---|
| T | Z |
| Z | Y |
| Y | X |
| X | T |

*(p. 36)*

*Diagram for [↔] (see scan p.36):*

| From | To |
|---|---|
| T | T |
| Z | Z |
| Y | X |
| X | Y |

We shall show the movement of information in the stack with examples.

Press the following keys in order:

[4] [В↑] [3] [В↑] [2] [В↑] [1]

The information in the stack registers is distributed as follows:

| Register | Contents | |
|---|---|---|
| T | `4,` | |
| Z | `3,` | |
| Y | `2,` | |
| X | `1,` | Display |

Press the [В↑] key

| Register | Contents | |
|---|---|---|
| T | `3,` | |
| Z | `2,` | |
| Y | `1,` | |
| X | `1,` | Display |

Press the keys [F] [⟳]

| Register | Contents | |
|---|---|---|
| T | `1,` | |
| Z | `3,` | |
| Y | `2,` | |
| X | `1,` | Display |

*(p. 37)*

Press the keys [F] [⟳]

| Register | Contents | |
|---|---|---|
| T | `1,` | |
| Z | `1,` | |
| Y | `3,` | |
| X | `2,` | Display |

Press the [↔] key

| Register | Before pressing the key | After pressing the key | |
|---|---|---|---|
| T | `1,` | `1,` | |
| Z | `1,` | `1,` | |
| Y | `3,` | `2,` | |
| X | `2,` | `3,` | Display |

*(In the scan, crossed arrows run from Y before to X after and from X before to Y after.)*

If information has been entered into register X incorrectly, clear register X by pressing the [Cx] key. The information in the other registers does not change.

| Register | Before pressing the key | After pressing the key | |
|---|---|---|---|
| T | `1,` | `1,` | |
| Z | `1,` | `1,` | |
| Y | `2,` | `2,` | |
| X | `3,` (Display) | `0,` | Display |

After clearing register X, enter a new number, for example 375.

| Register | Before entering the number | After entering the number | |
|---|---|---|---|
| T | `1,` | `1,` | |
| Z | `1,` | `1,` | |
| Y | `2,` | `2,` | |
| X | `0,` (Display) | `375,` | Display |

*(p. 38)*

5.7.6. When performing one-place operations, the calculator operates on the number in register X. The contents of registers Y, Z and T are retained, and the number that was in register X before the operation is passed to the previous-result register (register X1). The result of the one-place operation is passed to register X.

For example, it is necessary to calculate the square root of the number in register X by pressing the keys [F] [√].

| Register | Before pressing the keys | After pressing the keys | |
|---|---|---|---|
| T | `1,` | `1,` | |
| Z | `1,` | `1,` | |
| Y | `2,` | `2,` | |
| X | `375,` (Displayed) | `19,364916` | The number 375 is in register X1 |

5.7.7. All stack registers are cleared by pressing the keys [Cx] [В↑] [В↑] [В↑].

| Register | Before pressing the keys | After pressing the keys | |
|---|---|---|---|
| T | `1,` | `0,` | |
| Z | `1,` | `0,` | |
| Y | `2,` | `0,` | |
| X | `19,364916` (Display) | `0,` | Display |

5.7.8. When performing two-place operations, the calculator operates on the numbers in registers X and Y. The information in the stack registers moves (drops) as follows:

*(p. 39)*

*Diagram (see scan p.39):*

| From | To |
|---|---|
| T | T |
| T | Z |
| Z | Y |
| Y and X (through ✱) | X |
| X | X1 |

where ✱ denotes the result of the operation.

We shall explain the rewriting of information in the stack with the example of calculating 34 + 12. For greater clarity, we first clear all the stack registers, then enter the numbers and perform the addition operation.

| Keys pressed | Display | |
|---|---|---|
| [Cx] | `0,` | |
| [В↑] | `0,` | |
| [В↑] | `0,` | |
| [В↑] | `0,` | |
| [3] [4] | `34,` | The number 34 is in register X |
| [В↑] | `34,` | The number 34 is in registers X and Y |
| [1] [2] | `12,` | The number 12 is in register X |

After the numbers 34 and 12 are entered, the information in the stack registers will be arranged as follows:

| Register | Contents |
|---|---|
| T | `0,` |
| Z | `0,` |
| Y | `34,` |
| X | `12,` |

| Press the key | Display | |
|---|---|---|
| [+] | `46,` | Result of the operation in register X, and the number 12 in register X1 |

*(p. 40)*

The automatic movement of information in the stack can be used when calculating expressions containing a constant, and also when performing a complex sequence of arithmetic operations (usually in calculations with brackets).

For example, it is necessary to calculate 16 · 4 = ; 23 · 4 =

Write the constant (the number 4) into the stack registers by pressing the keys [4] [В↑] [В↑] [В↑], then press the keys:

| Keys pressed | T | Z | Y | X | |
|---|---|---|---|---|---|
| [1] [6] | `4,` | `4,` | `4,` | `16` | The number 16 is in register X |
| [×] | `4,` | `4,` | `4,` | `64,` | Result of multiplying 16·4 |
| [F] [⟳] | `64,` | `4,` | `4,` | `4,` | |
| [2] [3] | `4,` | `4,` | `4,` | `23,` | |
| [×] *(p. 41)* | `4,` | `4,` | `4,` | `92,` | Result of multiplying 23·4 |

*(p. 41)*

For example, it is necessary to calculate

(12 + 3) × 7 : 3.

The order of calculation on paper is as follows:

12 + 3 = 15

15 × 7 = 105

105 : 3 = 35

With the calculator these calculations are performed as follows:

| Keys pressed | Display | |
|---|---|---|
| [1] [2] | `12,` | |
| [В↑] | `12,` | |
| [3] | `3,` | |
| [+] | `15,` | |
| [7] | `7,` | |
| [×] | `105,` | |
| [3] | `3,` | |
| [÷] | `35,` | Result of calculations |

This expression can be calculated in another way: first four numbers are entered into the stack registers, then they are dropped and the operations are performed on them.

| Keys pressed | T | Z | Y | X | |
|---|---|---|---|---|---|
| [3] *(p. 41–42)* | `0,` | `0,` | `35,` | `3,` | Y: Previous result. X: The number 3 is in register X |
| [В↑] *(p. 42)* | `0,` | `35,` | `3,` | `3,` | The number 3 is in registers X and Y |
| [7] | `0,` | `35,` | `3,` | `7,` | The number 7 is in register X |
| [В↑] | `35,` | `3,` | `7,` | `7,` | |
| [3] | `35,` | `3,` | `7,` | `3,` | |
| [В↑] | `3,` | `7,` | `3,` | `3,` | |
| [1] [2] *(p. 43)* | `3,` | `7,` | `3,` | `12,` | |
| [+] | `3,` | `3,` | `7,` | `15,` | |
| [×] | `3,` | `3,` | `3,` | `105,` | |
| [↔] | `3,` | `3,` | `105,` | `3,` | |
| [÷] | `3,` | `3,` | `3,` | `35,` | |

### 5.8. Using the previous-result register

*(p. 43)*

5.8.1. In addition to the four stack registers, the calculator has one more register, called the previous-result register X1. This register keeps the value

*(p. 44)*

of the number that was in the display register X before the operation was performed. To check this number, press the keys [F] and [Bx] (recall previous result). The following movement of information in the stack then takes place:

*Diagram (see scan p.44):*

| From | To |
|---|---|
| T | (arrow leads out of the diagram) |
| Z | T |
| Y | Z |
| X | Y |
| X1 | X |
| X1 | X1 |

5.8.2. If the result of the operation obtained before checking the number is needed in further calculations, press the keys [F] and [⟳] to restore it. The following movement of information in the stack then takes place:

*Diagram (see scan p.44):*

| From | To |
|---|---|
| T | Z |
| Z | Y |
| Y | X |
| X | T |
| X | X1 |

5.8.3. To clear the previous-result register, "0" must be written into it; to do this, press the [Cx] key and any operation key (+, −, × etc.).

5.8.4. The presence of the stack registers and the previous-result register makes it easier to calculate complex expressions containing a constant. We shall show the use of these registers in calculating the expression (14·sin 2°)−4 :4.

As a result of the previous calculations, the information in the stack registers and in register X1 is distributed as follows:

*(p. 45)*

| Register | Contents | |
|---|---|---|
| T | `3,` | |
| Z | `3,` | |
| Y | `3,` | |
| X | `35,` | Display |
| X1 | `3,` | |

When the given example is solved, the following distribution of information in the stack registers takes place, depending on the keys pressed:

| Keys pressed | T | Z | Y | X | X1 | |
|---|---|---|---|---|---|---|
| [1] [4] | `3,` | `3,` | `35,` | `14,` | `3,` | The number 14 is in register X |
| [В↑] | `3,` | `35,` | `14,` | `14,` | `3,` | The number 14 is in registers X and Y |
| [2] | `3,` | `35,` | `14,` | `2` | `3,` | The number 2 is in register X |

*(p. 46)*

Set the Г/Р/ГРД switch to the "Г" position.

Press the keys.

| Keys pressed | T | Z | Y | X | X1 | |
|---|---|---|---|---|---|---|
| [F] [sin] | `3,` | `35,` | `14,` | `3,4899495 -02` | `2,` | X: Value of sin 2°. X1: Value of the argument |
| [×] | `3,` | `3,` | `35,` | `4,8859293 -01` | `3,4899495 -02` | X: Product 14·sin 2°. X1: Value of sin 2° |
| [F] [Bx] | `3,` | `35,` | `4,8859293 -01` | `3,4899495 -02` | `3,4899495 -02` | X: Check of the value of sin 2°. X1: Value of sin 2° |
| [F] [⟳] *(p. 47)* | `3,4899495 -02` | `3,` | `35,` | `4,8859293 -01` | `3,4899495 -02` | X: Restoring the result of the products 14·sin 2°. X1: sin 2° |
| [4] | `3,` | `35,` | `4,8859293 -01` | `4,` | `3,4899495 -02` | X: The number 4 is in register X. X1: Value of sin 2° |
| [−] | `3,` | `3,` | `35,` | `-3,5114071` | `4,` | X: Result (14·sin 2)−4. X1: The number 4 is in register X1 |
| [F] [Bx] | `3,` | `35,` | `-3,5114071` | `4,` | `4,` | Transfer of the number 4 from register X1 to register X. X1: The number 4 is in register X1 |
| [÷] *(p. 48)* | `3,` | `3,` | `35,` | `-8,7785177 -01` | `4,` | X: Result [(14·sin 2°)−4]:4. X1: The number 4 is in register X1 |

### 5.9. Using the addressable registers

*(p. 48)*

5.9.1. For storing initial data and intermediate results, the calculators have a register memory consisting of 14 addressable registers RG0, RG1 … RG9, RGa, RGв, RGc, RGd.

5.9.2. A number is written into the addressable registers from register X after pressing the [x→П] (store) key and one of the keys [0] … [9], [a], [в], [c], [d] that matches the index of the addressable register. The number passed to the addressable register is retained in register X.

For example, Avogadro's number (approximately 6,02·10²³) is passed for storage to register RG1 as follows:

| Keys pressed | Display | |
|---|---|---|
| [6] [·] [0] [2] [ВП] [2] [3] | `6,02 23` | Avogadro's number is in register X |
| [x→П] [1] | `6,02 23` | A copy of Avogadro's number is in register RG1 |

*(p. 49)*

5.9.3. Further calculations can be performed with the number remaining in register X. For example, squaring Avogadro's number.

| Keys pressed | Display |
|---|---|
| [F] [x²] | `3,62404 47` |

5.9.4. To call a number stored in an addressable register, press the [П→x] (recall) key and the key corresponding to the number of the register being called: [0], [1] … [9], [a], [в], [c], [d]. The number is called only into register X, and the contents of the register being called do not change.

For example, it is necessary to call Avogadro's number, which is in register RG1.

| Keys pressed | Display | |
|---|---|---|
| [П→x] [1] | `6,02 23` | Avogadro's number is in registers X and RG1 |

5.9.5. To clear an addressable register, write the digit 0 into the register that must be cleared.

To do this, perform the following operations:

1) press the [Cx] key;
2) press the [x→П] key;
3) press the key corresponding to the number of the register being cleared ([0], [1] … [9], [a], [в], [c], [d]).

For example, it is necessary to clear register RG1.

*(p. 50)*

| Keys pressed | Display | |
|---|---|---|
| [Cx] | `0,` | |
| [x→П] [1] | `0,` | Writing 0 to register RG1 |

5.9.6. All memory registers can be cleared by switching off the calculator.

### 5.10. Cancelling an erroneously pressed [F] key

*(p. 50)*

5.10.1. To cancel an erroneously pressed [F] key, press the [CF] key.

[^tn1]: Translator's note: in the handwritten formula the first denominator reads «(1,5)²» but the second reads «(15)²»; the keystroke sequence below uses 1,5.
[^tn2]: Translator's note: the key after «0,33» is printed as [БП]; the parallel entry in the last row («20 [ВП] 2») and the displayed result (3,3175216 −03) correspond to [ВП] (enter exponent).
