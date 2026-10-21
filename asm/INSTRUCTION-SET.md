# MK-56 Instruction Set

The real machine codes of the Электроника МК-56, as listed in Table 4 of the
original manual (p.51–55; see the [translation](../docs/manual/06-programming-mode.md)).
Every program step is one code; jumps, calls, conditionals and loops are
followed by a second step holding a two-digit address (`БП 42` = `51 42`).

This table matches [`common/mk56_isa.c`](../common/mk56_isa.c), the
single opcode table used by the assembler, the emulator and the TUI.

**Conventions.** *X1* is the previous-result register (recalled with F Bx).
One- and two-operand operations copy the old X into X1. Conditional jumps on
the МК-56 jump when the condition **fails** (manual p.65), so `Fx≥0 nn` jumps
when X < 0; the MK56-ASM mnemonic names the case in which the jump happens.

## Codes

| Code | Keys | MK56-ASM | Operation |
|------|------|----------|-----------|
| `00` | `0` | `0` | Digit (number entry) |
| `01` | `1` | `1` | Digit (number entry) |
| `02` | `2` | `2` | Digit (number entry) |
| `03` | `3` | `3` | Digit (number entry) |
| `04` | `4` | `4` | Digit (number entry) |
| `05` | `5` | `5` | Digit (number entry) |
| `06` | `6` | `6` | Digit (number entry) |
| `07` | `7` | `7` | Digit (number entry) |
| `08` | `8` | `8` | Digit (number entry) |
| `09` | `9` | `9` | Digit (number entry) |
| `0A` | `,` | `.` | Decimal point |
| `0B` | `/-/` | `CHS` | Change sign of the mantissa (or of the exponent after ВП) |
| `0C` | `ВП` | `EEX` | Start exponent entry (mantissa 0 becomes 1) |
| `0D` | `Cx` | `CLX` | X ← 0; the next digit does not lift the stack |
| `0E` | `В↑` | `ENTER` | Lift the stack, X stays; the next digit overwrites X |
| `0F` | `FBx` | `LASTX` | Lift the stack, X ← X1 (previous result) |
| `10` | `+` | `ADD` | X ← Y + X, stack drops |
| `11` | `−` | `SUB` | X ← Y − X, stack drops |
| `12` | `×` | `MUL` | X ← Y × X, stack drops |
| `13` | `÷` | `DIV` | X ← Y ÷ X, stack drops |
| `14` | `↔` | `SWAP` | Swap X and Y |
| `15` | `F10ˣ` | `EXP10` | X ← 10^X |
| `16` | `Feˣ` | `EXP` | X ← e^X |
| `17` | `Flg` | `LOG` | X ← log₁₀ X |
| `18` | `Fln` | `LN` | X ← ln X |
| `19` | `Fsin⁻¹` | `ASIN` | X ← arcsin X (angle switch) |
| `1A` | `Fcos⁻¹` | `ACOS` | X ← arccos X |
| `1B` | `Ftg⁻¹` | `ATAN` | X ← arctg X |
| `1C` | `Fsin` | `SIN` | X ← sin X |
| `1D` | `Fcos` | `COS` | X ← cos X |
| `1E` | `Ftg` | `TAN` | X ← tg X |
| `20` | `Fπ` | `PI` | Lift the stack, X ← 3,1415926 |
| `21` | `F√` | `SQRT` | X ← √X |
| `22` | `Fx²` | `SQ` | X ← X² |
| `23` | `F1/x` | `INV` | X ← 1/X |
| `24` | `Fxʸ` | `POW` | X ← X^Y — **base X, exponent Y**; stack drops |
| `25` | `F⟳` | `ROT` | Rotate: X→T, T→Z, Z→Y, Y→X; old X to X1 |
| `50` | `С/П` | `HALT` | Stop; С/П resumes at the next step |
| `51` | `БП nn` | `JMP nn` | Jump to nn |
| `52` | `В/О` | `RTN` | Return from subroutine |
| `53` | `ПП nn` | `CALL nn` | Call subroutine at nn (5-level return stack) |
| `54` | `КНОП` | `NOP` | No operation |
| `57` | `Fx≠0 nn` | `JZ nn` | Jump to nn if X = 0 (condition x≠0 fails) |
| `58` | `FL2 nn` | `LOOP2 nn` | Same with R2 |
| `59` | `Fx≥0 nn` | `JLT nn` | Jump to nn if X < 0 |
| `5A` | `FL3 nn` | `LOOP3 nn` | Same with R3 |
| `5B` | `FL1 nn` | `LOOP1 nn` | Same with R1 |
| `5C` | `Fx<0 nn` | `JGE nn` | Jump to nn if X ≥ 0 |
| `5D` | `FL0 nn` | `LOOP0 nn` | R0 − 1; jump to nn while not zero (R0 is left at 1) |
| `5E` | `Fx=0 nn` | `JNZ nn` | Jump to nn if X ≠ 0 |

## Register operations

Registers are numbered 0–9, a, b, c, d (MK56-ASM: `R0`–`R9`, `RA`–`RD`);
the last code digit is the register number (`ИПa` = `6A`).

| Codes | Keys | MK56-ASM | Operation |
|-------|------|----------|-----------|
| `40`–`4D` | `П0` … `Пd` (x→П) | `STO Rn` | Rn ← X |
| `60`–`6D` | `ИП0` … `ИПd` (П→x) | `RCL Rn` | Lift the stack, X ← Rn |

## Indirect (К) operations

`К` operations take the target from a register. The register is modified
first — **R0–R3 decrease by 1, R4–R6 increase by 1, R7–Rd are unchanged** —
and its new integer value is the address or register number (manual p.67).
Indirect conditionals modify the register only when they jump (p.70).

| Codes | Keys | MK56-ASM | Operation |
|-------|------|----------|-----------|
| `70`–`7D` | `Кx≠0 n` | `JZ (Rn)` | Jump to the address in Rn if X = 0 |
| `80`–`8D` | `КБП n` | `JMP (Rn)` | Jump to the address in Rn |
| `90`–`9D` | `Кx≥0 n` | `JLT (Rn)` | Jump to the address in Rn if X < 0 |
| `A0`–`AD` | `КПП n` | `CALL (Rn)` | Call the address in Rn |
| `B0`–`BD` | `КП n` (К x→П) | `STO (Rn)` | R[Rn] ← X |
| `C0`–`CD` | `Кx<0 n` | `JGE (Rn)` | Jump to the address in Rn if X ≥ 0 |
| `D0`–`DD` | `КИП n` (К П→x) | `RCL (Rn)` | Lift the stack, X ← R[Rn] |
| `E0`–`ED` | `Кx=0 n` | `JNZ (Rn)` | Jump to the address in Rn if X ≠ 0 |

Codes not listed (26–3F, 55, 56, 5F, and the unused register slots) are not
documented in the manual; the emulator stops with an error on them.

## Not in the manual

- `F⟳` (`25`) and `F Bx` (`0F`) are missing from the printed Table 4; `0F`
  appears in the functional test, `25` follows the Б3-34 family.
- A `В/О` with an empty return stack goes to address 01 (Б3-34 behaviour).
- Indirect operations use the integer part of the register (Дьяконов).

