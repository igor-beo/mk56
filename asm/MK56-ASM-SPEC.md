# MK56-ASM Language Specification

**Version**: 2.0
**Target**: Электроника МК-56 programmable calculator (Б3-34 instruction set)

MK56-ASM gives the МК-56's instructions ASCII names, labels and number
literals. It assembles to the real machine codes, one byte per program step.
The assembler also reads programs in the **original listing notation** used
by Soviet manuals and magazines, so a listing can be typed in as printed.

See [INSTRUCTION-SET.md](INSTRUCTION-SET.md) for every code.

---

## 1. The machine

| Component | Specification | Manual |
|-----------|---------------|--------|
| Program memory | 98 steps, addresses 00–97 | p.7, p.50 |
| Registers | 14: R0–R9, Ra, Rb, Rc, Rd | p.48 |
| Stack | X, Y, Z, T, plus the previous-result register X1 | p.34, p.43 |
| Return stack | 5 levels | p.56 |
| Numbers | 8-digit mantissa (results truncated), exponent ±99 | p.5, p.29 |
| Angles | switch: radians, degrees, grads | p.25 |

Things that surprise people coming from other RPN machines:

- **Conditionals jump when the condition fails.** `Fx<0 12` continues with the
  next step if X < 0 and jumps to 12 otherwise (p.65). MK56-ASM names the case
  that jumps, so `JGE 12` assembles to `Fx<0 12`.
- **`xʸ` uses X as the base and Y as the exponent** (p.28).
- **Numbers are keystrokes.** `25` is two steps, `2` and `5`. Two numbers in a
  row merge into one unless something separates them, usually `ENTER`.
- **`ВП` is exponent entry**, not Enter. Enter is `В↑`.
- **Indirect addressing modifies the register first**: R0–R3 count down,
  R4–R6 count up, R7–Rd stay as they are (p.67).

---

## 2. MK56-ASM syntax

One instruction per line:

```
[label:] [instruction [operand]] [; comment]
```

```asm
; Sum 1..n, n in X
        STO R0          ; counter
        0
        STO R1          ; sum
loop:   RCL R1
        RCL R0
        ADD
        STO R1
        LOOP0 loop      ; R0 - 1, repeat while not zero
        RCL R1
        HALT
```

- Mnemonics and register names are case-insensitive. Labels are too.
- Comments start with `;` or `//`.
- `NN:` (a number instead of a label) asserts that the next step is at
  address NN, and assembly fails if it is not.
- Limits: a source line is at most 255 bytes (a Cyrillic letter takes 2),
  a label at most 63 characters, and a program at most 128 labels.
  Unknown directives are errors.

### 2.1 Operands

| Form | Meaning | Example |
|------|---------|---------|
| `Rn` | register R0–R9, RA–RD | `STO R3`, `RCL RA` |
| `(Rn)` | indirect through Rn | `RCL (R4)`, `JMP (R3)` |
| `nn` | address 00–97 | `JMP 12` |
| `label` | address of a label | `CALL sub` |

### 2.2 Number literals

A literal is assembled into the keystrokes that enter it:

| Literal | Steps |
|---------|-------|
| `25` | `2 5` |
| `9.81` | `9 , 8 1` |
| `-3` | `3 /-/` |
| `1.5e-3` | `1 , 5 ВП 3 /-/` |

The mantissa can have at most 8 digits and the exponent at most 2.

### 2.3 Instructions

| Group | Mnemonics |
|-------|-----------|
| Entry | `CHS`, `EEX`, `CLX`, `ENTER`, `LASTX`, `.` |
| Arithmetic | `ADD`, `SUB`, `MUL`, `DIV`, `SWAP`, `ROT` |
| Functions | `SQ`, `SQRT`, `INV`, `POW`, `EXP`, `EXP10`, `LN`, `LOG`, `SIN`, `COS`, `TAN`, `ASIN`, `ACOS`, `ATAN`, `PI` |
| Registers | `STO Rn`, `RCL Rn`, `STO (Rn)`, `RCL (Rn)` |
| Control | `JMP`, `CALL`, `RTN`, `HALT`, `NOP` |
| Conditional | `JZ`, `JNZ`, `JLT`, `JGE` (each also as `(Rn)`) |
| Loops | `LOOP0`–`LOOP3` |

Aliases: `GOTO` = `JMP`, `STOP` = `HALT`, `RETURN` = `RTN`,
`ROLLDOWN` = `ROT`. A line may also use original notation, for example
`Fx²` or `БП 12`.

---

## 3. Listing syntax (`.mk56` files)

Files ending in `.mk56`, or any source after a `.LISTING` directive, use the
notation of printed listings: many steps per line, separated by spaces.

```
; Manual table 5: circle area, d in R2
00: ИП2 Fx² В↑ Fπ × 4 ÷ С/П
```

- Each token is one step. The token after `БП`, `ПП`, a conditional or a
  loop is its two-digit address: `Fx≠0 13`, `FL0 02`.
- A number token outside that position is entered digit by digit: `100` is
  `1 0 0`, and `9,81` is `9 , 8 1`.
- `NN:` asserts the address of the next step. Start every line with one, so
  that a skipped or doubled step stops the assembly.
- Cyrillic and Latin lookalikes are interchangeable (`С/П`, `C/П`), and so
  are the common spellings of each key:

| Key | Accepted spellings |
|-----|--------------------|
| x→П n | `П3`, `x→П 3`, `x->П3` |
| П→x n | `ИП3`, `ИП 3`, `П→x 3` |
| В↑ | `В↑`, `↑` |
| ↔ | `↔`, `XY` |
| F-functions | `Fx²`, `F x²`, `x²`, `Fx^2`; `F√`, `Fsqrt`; `Fxʸ`, `Fx^y` |
| F⟳ | `F⟳`, `F,` |
| conditionals | `Fx≠0`, `x≠0`, `Fx!=0`; `Fx≥0`, `Fx>=0` |
| indirect | `КИП3`, `К ИП 3`, `КП→x 3`; `КБП3`; `Кx≠03` |
| registers a–d | Latin `a b c d` or Cyrillic `а в с д` |

---

## 4. Directives

| Directive | Meaning |
|-----------|---------|
| `.ORG nn` | Continue at address nn |
| `.LISTING` / `.ASM` | Switch syntax |
| `.STEP 5F` | Emit a raw code (hex) |
| `.END` | Ignore the rest of the file |

`.EQU`, `.ASSERT`, `.TRACE` and `.BREAK` are accepted and ignored.

### 4.1 Test directives

Test directives sit in comments. `mk56test` runs them (see
[tests/](../tests/)):

```asm
; @input 1
; @expect X=1.1752012
```

| Directive | Meaning |
|-----------|---------|
| `@angle rad\|deg\|grad` | Angle switch |
| `@reg R0=5 Ra=12` | Set registers |
| `@stack X=10 Y=30` | Set stack registers |
| `@start nn` | Set the program counter |
| `@input v` | Key v into X, press С/П, run until stop |
| `@run` | Press С/П without input |
| `@expect X=v [tol=1e-5]` | Check X, Y, Z, T or a register. The tolerance defaults to 1e-6; it is relative for &#124;v&#124; > 1 and absolute below, so give a tighter `tol=` for small values |
| `@expect error` | Expect ЕГГОГ |
| `@reset` | Clear stack and registers, PC = 00 |

---

## 5. Output

The assembler writes a raw binary of one byte per step (up to 98 bytes).
`-l file` adds a listing with addresses, codes, original notation and source:

```
ADDR  CODES             KEYS                      SOURCE
==============================================================================
00    62 22 0E 20 12 04 13 50  ИП2 Fx² В↑ Fπ × 4 ÷ С/П   00: ИП2 Fx² В↑ Fπ × 4 ÷ С/П
```

The emulator loads `.bin`, `.asm` and `.mk56` files directly.
