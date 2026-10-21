# Checks against a real МК-56

The factory manual is the authority: where it shows a result, the emulator
must reproduce it, and nothing here re-checks it. Where the manual is
silent, the emulator follows Дьяконов's handbook or Б3-34 conventions
([machine-reference §8](machine-reference.md#8-inferred-not-stated-in-the-manual)).
These checks settle those guesses on a real calculator.

**How to run them**

- Switch the calculator off and on before each check. This clears the
  stack, X1 and the registers.
- Set the angle switch to **Р** (radians).
- Keys are written as printed on the calculator: `П` is x→П, `ИП` is П→x,
  `К ИП` is indirect recall.
- Write down exactly what the display shows, including leading zeros, the
  exponent and where the minus sign is.

## 1. Arithmetic precision

The manual shows 1/x truncating (1/560 gives `1,7857142 -03`). These
check whether √ and the arithmetic operations truncate too.

| # | Keys | Emulator | МК-56 |
|---|---|---|---|
| 1.1 | `2 F√` | `1,4142135` | |
| 1.2 | `1 В↑ 3 ÷ 3 ×` | `9,9999999 -01` | |

## 2. Function digits

The emulator computes functions in double precision and truncates. The chip
uses its own algorithms, so the last digit or two may differ. Every digit
you record here helps a future chip-accurate version.

| # | Keys | Emulator | МК-56 |
|---|---|---|---|
| 2.1 | `1 Fsin` | `8,4147098 -01` | |
| 2.2 | `1 Ftg` | `1,5574077` | |
| 2.3 | `0 , 5 Farcsin` | `5,2359877 -01` | |
| 2.4 | `0 , 5 Farctg` | `4,636476 -01` | |
| 2.5 | `1 Fe^x` | `2,7182818` | |
| 2.6 | `2 Fe^x` | `7,389056` | |
| 2.7 | `2 Fln` | `6,9314718 -01` | |
| 2.8 | `2 Flg` | `3,0102999 -01` | |
| 2.9 | `2 F10^x` | `100,` | |
| 2.10 | `1 , 1 7 1 2 2 9 7 Fsin` | `9,2122967 -01` | |
| 2.11 | `1 , 1 7 1 2 2 9 7 Fcos` | `3,8901914 -01` | |
| 2.12 | `1 , 1 7 1 2 2 9 6 Fsin` | `9,2122963 -01` | |

2.10–2.12 decide program 5.16. The book shows it stopping at `1,1712297`;
in the emulator it never stops, because its sine differs in the last digit.

## 3. Stack and X1

Each check shows which of two possible behaviours the calculator has.

| # | Keys | Question | Emulator | If the other way | МК-56 |
|---|---|---|---|---|---|
| 3.1 | `1 В↑ 2 + 5 В↑ 7 ↔ FBx` | Does ↔ copy X to X1? | `2,` (no) | `7,` | |
| 3.2 | `1 В↑ 2 + 9 В↑ FBx` | Does В↑ copy X to X1? | `2,` (no) | `9,` | |
| 3.3 | `1 В↑ 2 + 9 /-/ FBx` | Does /-/ copy X to X1? | `2,` (no) | `9,` or `-9,` | |
| 3.4 | `5 В↑ Fπ + +` | Does Fπ right after В↑ lift the stack? | `13,141592` (lifts) | `8,1415926` | |
| 3.5 | `3 П0 5 В↑ ИП0 + +` | Does ИП right after В↑ lift the stack? | `13,` (lifts) | `8,` | |
| 3.6 | `5 В↑ 7 ↔ 9 + +` | Does a digit typed after ↔ lift the stack? | `21,` (lifts) | `16,` | |
| 3.7 | `5 П4 К ИП4 ИП4 ↔ ↔` | Does a code keep its leading zeros through ↔? | `00000006,` | `6,` | |

## 4. Indirect addressing

| # | Keys | Question | Emulator | МК-56 |
|---|---|---|---|---|
| 4.1 | `4 2 1 , 7 5 6 П9 К ИП9 ИП9` | Is the fraction dropped? The handbook (for the Б3-34) shows `00000421` | `00000421,` | |
| 4.2 | `2 0 П7 К ИП7` | Register 20 does not exist: error, or some value? | `0,` (no error) | |

## 5. Errors

After each ЕГГОГ, press `↔ ↔` to see what X holds.

| # | Keys | Emulator: display, then X after `↔ ↔` | МК-56 |
|---|---|---|---|
| 5.1 | `1 ВП 9 9 Fx²` (overflow) | `ЕГГОГ`, then `1, 99` | |
| 5.2 | `2 /-/ F√` | `ЕГГОГ`, then `-2,` | |
| 5.3 | `0 Fln` | `ЕГГОГ`, then `0,` | |
| 5.4 | `2 В↑ 0 Fxʸ` (base 0; the manual's condition is misprinted) | `ЕГГОГ` | |

## 6. Program mode

| # | What to do | Emulator | МК-56 |
|---|---|---|---|
| 6.1 | `F ПРГ`, press `F⟳`, read the code at that step, `F АВТ` | code `25` | |
| 6.2 | `БП 9 7 F ПРГ 2 С/П F АВТ`, then `БП 9 7 С/П`. Does step 97 run on into step 00? | stops showing `2,` | |
