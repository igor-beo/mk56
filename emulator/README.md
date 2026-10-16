# MK-56 Emulator

Emulates the Электроника МК-56 as its manual describes it, either in a
Turbo C–style ncurses TUI or from the console.

## Building

```bash
make                   # needs a C11 compiler and ncurses
make test              # runs ../tests
```

## Usage

```bash
./mk56emu program.asm                       # TUI; .asm and .mk56 are assembled on load
./mk56emu program.bin -c -i 5               # console: key 5 into X, then С/П
./mk56emu program.mk56 -c -r R0=10 -r Ra=12 # set registers first
./mk56emu program.asm -c -a deg -i 30       # angle switch: rad (default), deg, grad
./mk56emu program.asm -d                    # disassemble
```

```
$ ./mk56emu ../asm/examples/factorial.asm -c -i 5
...
State: HALTED
Steps executed: 79
Display: 120,
```

```
$ ./mk56emu ../asm/examples/sinh.asm -d
ADDR  CODES  KEYS          MK56-ASM
00    16     Feˣ           EXP
01    0E     В↑            ENTER
02    23     F1/x          INV
...
```

## TUI

| Key | Action |
|-----|--------|
| F7 / F8 | Step one program step / run until С/П |
| F5 | Key a number into X |
| F4 | Edit at the current step (`RCL R3`, `ИП3`, `БП 42`). Enter stores the step, Esc leaves |
| F6 | Toggle breakpoint |
| F9 | Reset: stack and registers cleared, program kept |
| G | Angle switch Р / Г / ГРД |
| F1, F10, Q | Help, menu, quit |

The display shows X the way the calculator does: `12,56637`,
`3,3333333 -01`, or ЕГГОГ on an error. The program window shows each step
as its code, as the key printed in the manual (`ИП3`) and in MK56-ASM
(`RCL R3`).

## What is emulated

From the manual (page numbers in [`mk56emu.c`](mk56emu.c)):

- the real machine codes, 98 steps, 14 registers, a 5-level return stack
- number entry: digits, `,`, `/-/`, `ВП` with an exponent, and when digit
  entry lifts the stack
- the previous-result register X1 and `F Bx`; stack rotation `F⟳`
- 8-digit truncating arithmetic with π = 3,1415926 (`1/560` gives
  `1,7857142 -03`)
- conditionals that jump when the condition fails; `FL0`–`FL3` loops
- indirect operations with pre-decrement (R0–R3) and pre-increment (R4–R6)
- radians, degrees and grads; ЕГГОГ for invalid operations, overflow and
  underflow

The manual does not cover the following, so the emulator follows the Б3-34
family:
- the `F⟳` code (`25`)
- `В/О` with an empty return stack, which goes to 01
- indirect operations using only the integer part of a register
- stopping on an error inside a program

Transcendental functions use IEEE double and are then truncated. Their last
digit or two can differ from the real chip. A program that never stops is
halted after 10 million steps.

## API

```c
#include "mk56emu.h"

MK56VM vm;
vm_init(&vm);
vm_load_file(&vm, "program.bin");   // or vm_load(&vm, bytes, n)
vm.regs[2] = 5;
vm_input(&vm, 1.0);                 // key a number into X
vm_run(&vm);                        // С/П
char shown[32];
vm_format_display(&vm, shown, sizeof shown);
```

`vm_step()` executes one program step; a jump and its address count as one
step. `vm_disasm()` disassembles in MK56-ASM; for the original notation,
call `mk56_disasm()` from `common/mk56_isa.h`.
