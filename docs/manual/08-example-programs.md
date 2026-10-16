# 7. Examples of calculations by program

Translated from «Микрокалькулятор Электроника МК56. Техническое описание и инструкция по эксплуатации». Original scan: [references/MK-56 inst.pdf](../../references/MK-56%20inst.pdf).

*Transcription conventions: the calculator uses a decimal comma, and displayed values are given exactly as printed (e.g. `12,56637`). The typescript prints the digit 1 as «I»; it is given here as 1. The original prints operation codes in seven-segment glyphs (`-` = A, `L` = B, `С` = C, `Г` = D, `Е` = E, blank = F); they are given here in ordinary hexadecimal, e.g. `5D`. The ÷ symbol in the original closely resembles +; the two keys are identified by their codes (13 = ÷, 10 = +).*

## 7. EXAMPLES OF CALCULATIONS BY PROGRAM

*(p. 85)*

### 7.1. Finding compound interest

*(p. 85)*

It is required to find one of four interrelated parameters (n, i, H, K) from the three known ones using the following formulas:

n = ln(K/H) / ln(1+i/100),

i = [(K/H)^(1/n) − 1] × 100,

H = K(1+i/100)^(−n),

K = H(1+i/100)^n

where n — the number of time periods;
i — the interest rate per time period;
H — the initial amount of accumulation;
K — the final amount of accumulation.

*(p. 86)*

Let us distribute the initial data among the memory registers:

RG2 — n;
RG3 — i;
RG4 — H;
RG5 — K.

The calculation of the frequently occurring quantity /1+i/100/ we lay out as a subroutine, which we write from address 46.

The program for calculating the parameter n we write from address 00.

After the quantity (1 + i/100) has been calculated by the program, we find the natural logarithm of this quantity and store the result in memory register RG6, which is used for storing intermediate results.

From register RG5 we call the value of the parameter K, and from register RG4 the value of the parameter H, and after calculating ln(K/H) we call the value ln(1+i/100) from memory register RG6. After dividing these quantities we obtain the value of the parameter n.

The program for calculating the parameter i we write at addresses 12–28, the parameter H at addresses 29–37, and the parameter K at addresses 38–45. The instructions for working with the program are given in Table 15, the program in Table 16. Let us consider this problem for a specific case.

Suppose that 270 million roubles were initially invested in some branch of industry. 12% annual profit is planned, of which 7,5% will be allocated to the expansion of production.

It is required to find what the total amount invested in the branch will be after 6 years.

Here:

n = 6;
i = 7,5;
H = 270;
K = ?

*(p. 87)*

Table 15

INSTRUCTIONS FOR WORKING WITH THE PROGRAM

| Operations | Keys pressed |
|---|---|
| 1. Switch on the calculator | |
| 2. Go to Programming mode (ПРГ) | [F] [ПРГ] |
| 3. Enter the program | [ ] [ ] |
| 4. Go to Automatic mode (АВТ) | [F] [АВТ] |
| 5. Enter the initial data into the memory registers: n — into RG2 | [x→П] (store) [2] |
| i — into RG3 | [x→П] [3] |
| н — into RG4 | [x→П] [4] |
| к — into RG5 | [x→П] [5] |
| 6. From the three parameters entered into the memory registers as initial data, calculate the fourth, unknown one: n | [В/О] (return; in automatic mode, reset to 00) [С/П] (stop/start) |
| i | [БП] (go to) [1] [2] [С/П] |
| н | [БП] [2] [9] [С/П] |
| к | [БП] [3] [8] [С/П] |

Table 16

PROGRAM

| Address | Keys pressed | Code | Address | Keys pressed | Code |
|---|---|---|---|---|---|
| 00 | [ПП] (subroutine call; in automatic mode, single step) | 53 | 29 | [ПП] | 53 |
| 01 | [4] [6] | 46 | 30 | [4] [6] | 46 |
| 02 | [F] [ln] | 18 | 31 | [F] [xʸ] | 24 |
| 03 | [x→П] [6] | 46 | 32 | [F] [1/x] | 23 |
| 04 | [П→x] (recall) [5] | 65 | 33 | [В↑] (enter) | 0E |
| 05 | [П→x] [4] | 64 | 34 | [П→x] [5] | 65 |
| 06 | [÷] | 13 | 35 | [×] | 12 |
| 07 | [F] [ln] | 18 | 36 | [x→П] [4] | 44 |
| 08 | [П→x] [6] | 66 | 37 | [С/П] | 50 |
| 09 | [÷] | 13 | 38 | [ПП] | 53 |
| 10 | [x→П] [2] | 42 | 39 | [4] [6] | 46 |
| 11 | [С/П] | 50 | 40 | [F] [xʸ] | 24 |
| 12 | [П→x] [5] | 65 | 41 | [В↑] | 0E |
| 13 | [В↑] | 0E | 42 | [П→x] [4] | 64 |
| 14 | [П→x] [4] | 64 | 43 | [×] | 12 |
| 15 | [÷] | 13 | 44 | [x→П] [5] | 45 |
| 16 | [В↑] | 0E | 45 | [С/П] | 50 |
| 17 | [П→x] [2] | 62 | 46 | [П→x] [3] | 63 |
| 18 | [F] [1/x] | 23 | 47 | [1] | 01 |
| 19 | [↔] (swap X and Y) | 14 | 48 | [0] | 00 |
| 20 | [F] [xʸ] | 24 | 49 | [0] | 00 |
| 21 | [1] | 01 | 50 | [÷] | 13 |
| 22 | [−] | 11 | 51 | [1] | 01 |
| 23 | [1] | 01 | 52 | [+] | 10 |
| 24 | [0] | 00 | 53 | [В↑] | 0E |
| 25 | [0] | 00 | 54 | [П→x] [2] | 62 |
| 26 | [×] | 12 | 55 | [↔] | 14 |
| 27 | [x→П] [3] | 43 | 56 | [В/О] | 52 |
| 28 | [С/П] | 50 | | | |

*Table 16 begins on p. 87 (addresses 00–08) and continues on p. 88 (addresses 09–56).*

*(p. 89)*

In accordance with the instructions for working with the program, we carry out the operations given in items 1–4 of Table 15. Then we enter the known quantities n, i, H into memory registers RG2, RG3 and RG4 respectively.

To go to the address from which the calculation of the parameter K begins, we carry out the unconditional jump operation by pressing the keys [БП], [3], [8], and start the program by pressing the key [С/П].

We read the result on the display: 416,6914 million roubles.

### 7.2. Calculating the sum /S/ or the product /P/ of a number sequence

*(p. 89)*

The calculations are carried out using the following formulas:

S = Σ_{i=1}^{n} i ;   P = Π_{i=1}^{n} i

The instructions for working with the program are given in Table 18, the program in Table 19.

### 7.3. Calculating the mathematical expectation of a statistical set of values

*(p. 89)*

The calculations are carried out using the formula

X̄ = (1/n) Σ_{i=1}^{n} xi

The instructions for working with the program are given in Table 17, the program in Table 20.

*(p. 90)*

Table 17

INSTRUCTIONS FOR WORKING WITH THE PROGRAM

| Operations | Keys pressed |
|---|---|
| 1. Switch on the calculator | |
| 2. Go to Programming mode | [F] [ПРГ] |
| 3. Enter the program | [ ]…[ ] |
| 4. Clear the program counter | [F] [АВТ] [В/О] |
| 5. Type the number Xi | [ ]…[ ] |
| 6. Calculate the mean number X | [С/П] |
| 7. Repeat the operations given in items 5, 6 when working with the next member of the sequence | |
| 8. Check Σ_{i=1}^{n} Xi | [П→x] [2] |
| 9. Check — n | [П→x] [3] |

### 7.4. The "ballistic" problem of a body thrown at an angle to the horizon

*(p. 90)*

The distance travelled by the body is calculated by the formula

S = υ²·sin α / g,

where υ — the velocity of the body, m/s;
α — the angle of throw in degrees;
g — the acceleration of free fall (9,81 m/s²);
S — the distance, m.

The instructions for working with the program are given in Table 21, the program in Table 22.

*(p. 91)*

Table 18

INSTRUCTIONS FOR WORKING WITH THE PROGRAM

| Operation | Keys pressed |
|---|---|
| 1. Switch on the calculator | |
| 2. Go to Programming mode | [F] [ПРГ] |
| 3. Enter the program | [ ]…[ ] |
| 4. Clear the program counter | [F] [АВТ] [В/О] |
| 5. Type the value n on the keyboard | [ ]…[ ] |
| 6. Calculate the quantities S or P | [С/П] |
| 7. To calculate the sum with a new value n, carry out the operations given in items 5, 6 | |

Table 19

PROGRAM

| Address | Keys pressed | Code | Address | Keys pressed | Code |
|---|---|---|---|---|---|
| 00 | [x→П] [2] | 42 | 09 | [x→П] [2] | 42 |
| 01 | [1] | 01 | 10 | [П→x] [3] | 63 |
| 02 | [−] | 11 | 11 | [БП] | 51 |
| 03 | [x→П] [3] | 43 | 12 | [0] [1] | 01 |
| 04 | [F] [x≠0] | 57 | 13 | [П→x] [2] | 62 |
| 05 | [1] [3] | 13 | 14 | [С/П] | 50 |
| 06 | [В↑] | 0E | 15 | [БП] | 51 |
| 07 | [П→x] [2] | 62 | 16 | [0] [0] | 00 |
| 08 | [+] or [×] | 10 (12) | 17 | | |

*(p. 92)*

Table 20

PROGRAM

| Address | Keys pressed | Code |
|---|---|---|
| 00 | [x→П] [2] | 42 |
| 01 | [1] | 01 |
| 02 | [x→П] [3] | 43 |
| 03 | [П→x] [2] | 62 |
| 04 | [С/П] | 50 |
| 05 | [В↑] | 0E |
| 06 | [П→x] [2] | 62 |
| 07 | [+] | 10 |
| 08 | [x→П] [2] | 42 |
| 09 | [П→x] [3] | 63 |
| 10 | [1] | 01 |
| 11 | [+] | 10 |
| 12 | [x→П] [3] | 43 |
| 13 | [В↑] | 0E |
| 14 | [П→x] [2] | 62 |
| 15 | [↔] | 14 |
| 16 | [÷] | 13 |
| 17 | [С/П] | 50 |
| 18 | [БП] | 51 |
| 19 | [0] [5] | 05 |

*(p. 93)*

Table 21

INSTRUCTIONS FOR WORKING WITH THE PROGRAM

| Operations | Keys pressed |
|---|---|
| 1. Switch on the calculator | |
| 2. Go to Programming mode | [F] [ПРГ] |
| 3. Enter the program | [ ]…[ ] |
| 4. Clear the program counter | [F] [АВТ] [В/О] |
| 5. Set the Г/Р/ГРД switch to position "Г", and type the value α on the keyboard | [ ]…[ ] |
| 6. Carry out the entry operation | [В↑] |
| 7. Type the value of the velocity in m/s on the keyboard | [ ]…[ ] |
| 8. Calculate the distance S in metres | [С/П] |
| 9. To calculate the distance with new values α and υ, follow the instructions starting from item 5 | |

*(p. 94)*

Table 22

PROGRAM

| Address | Keys | Code |
|---|---|---|
| 00 | [F] [x²] | 22 |
| 01 | [↔] | 14 |
| 02 | [F] [sin] | 1C |
| 03 | [×] | 12 |
| 04 | [9] | 09 |
| 05 | [.] | 0A |
| 06 | [8] | 08 |
| 07 | [1] | 01 |
| 08 | [÷] | 13 |
| 09 | [С/П] | 50 |
| 10 | [БП] | 51 |
| 11 | [0] [0] | 00 |
