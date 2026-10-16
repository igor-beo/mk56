# Getting Started

## Build

You need a C compiler and ncurses.

```bash
xcode-select --install                              # macOS
sudo apt-get install build-essential libncurses-dev # Debian / Ubuntu

make          # builds assembler/mk56asm and emulator/mk56emu
make test     # runs the core tests and every program that has @expect lines
```

## Your first program

Save this as `square.asm`:

```asm
; Square the input
; @input 5
; @expect X=25
        SQ              ; X = X²
        HALT            ; С/П
```

Run it:

```bash
./emulator/mk56emu square.asm -c -i 5     # console: prints "Display: 25,"
./emulator/mk56emu square.asm             # TUI
./tests/mk56test square.asm               # checks the @expect lines
```

The emulator assembles `.asm` and `.mk56` files itself. To get a binary
(one byte per program step) and a listing, use
`./assembler/mk56asm square.asm -l square.lst`.

## Typing in a listing from a book

Programs printed in Soviet manuals and magazines can be typed in as they
appear. Save them as `.mk56`:

```
; Circle area, d in R2 (manual, table 5)
; @reg R2=5
; @run
; @expect X=19.634953
00: ИП2 Fx² В↑ Fπ × 4 ÷ С/П
```

The `00:` at the start of the line is an address check. If you skip or
double a step, the assembler reports where the addresses stop matching.
Cyrillic and Latin lookalikes are both accepted, and so are common
spellings such as `П→x 2` and `x²`. See
[the language spec](../asm/MK56-ASM-SPEC.md#3-listing-syntax-mk56-files).

## The TUI

| Key | Action |
|-----|--------|
| F7 / F8 | Step / run (С/П) |
| F5 | Key a number into X |
| F4 | Edit the program at the current step: `RCL R3` or `ИП3` |
| F6 | Breakpoint |
| F9 | Reset (clears the stack and registers, keeps the program) |
| G | Angle switch: radians, degrees, grads |
| F1 | Help |

The program window shows each step three ways: the code (`63`), the key as
printed in the manual (`ИП3`) and MK56-ASM (`RCL R3`).

## Things the МК-56 does differently

- **Conditional jumps jump when the condition fails.** `Fx<0 12` goes to 12
  when X ≥ 0. In MK56-ASM, `JGE 12` produces exactly that.
- **`xʸ` takes X as the base and Y as the exponent.**
- **Results keep 8 digits, truncated.** `1/560` gives `1,7857142 -03`.
- **`ВП` enters an exponent.** The Enter key is `В↑`.

The [manual translation](manual/README.md) has the full story. Chapter 7
covers jumps, indirect addressing and loops.
