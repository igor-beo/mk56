# Электроника МК-56 Development Environment

<p align="center">
  <img src="docs/images/mk56-keyboard.png" alt="МК-56 keyboard layout, Fig. 2 of the original manual" width="640">
</p>

Tools and documentation for the **Электроника МК-56**, a Soviet desktop
programmable RPN calculator from the 1980s that is command-compatible with
the Б3-34. The project includes:

- an **emulator** that follows the original manual: real machine codes,
  8-digit truncating arithmetic, indirect addressing, loops and the
  jump-on-fail conditionals, in a Turbo C–style ncurses TUI;
- an **assembler** that reads both MK56-ASM and listings typed **exactly as
  printed** in Soviet books (`00: ИП2 Fx² В↑ Fπ × 4 ÷ С/П`), and converts
  one into the other;
- the **first English translation** of the factory operating manual;
- a **program library** of 72 programs from Дьяконов's 1985 handbook in
  readable MK56-ASM, each with the book's listing as printed and a test.

```
.asm / .mk56  ──▶  mk56asm  ──▶  .bin (one byte per step)  ──▶  mk56emu
```

## Quick start

```bash
make            # assembler/mk56asm and emulator/mk56emu (needs a C11 compiler and ncurses)
make test       # core tests plus every program with @expect lines

./emulator/mk56emu asm/examples/factorial.asm -c -i 5      # Display: 120,
./emulator/mk56emu programs/04-01-sinh.asm                  # TUI
```

The [getting started guide](docs/getting-started.md) covers the first
program, typing in listings and the TUI.

## Contents

| Directory | Contents |
|-----------|----------|
| [assembler/](assembler/) | MK56-ASM and listing assembler (C) |
| [emulator/](emulator/) | Emulator core and ncurses TUI (C) |
| [common/](common/) | The opcode table shared by assembler, emulator and TUI |
| [tests/](tests/) | Core tests from the manual's tables, program test runner |
| [asm/](asm/) | [Language spec](asm/MK56-ASM-SPEC.md), [instruction set](asm/INSTRUCTION-SET.md), examples |
| [docs/](docs/) | [Manual translation](docs/manual/README.md), [getting started](docs/getting-started.md) |
| [programs/](programs/) | Program library from Дьяконов's handbook |
| [references/](references/) | Scans of the original manual, schematic and handbook |
| [editors/](editors/) | VSCode syntax highlighting for `.asm` and `.mk56` |

## The calculator

| Feature | Value | Manual |
|---------|-------|--------|
| Program memory | 98 steps (00–97) | p.7 |
| Registers | 14 (R0–R9, a, b, c, d) | p.48 |
| Stack | X, Y, Z, T and the previous-result register X1 | p.34, p.43 |
| Return stack | 5 levels | p.56 |
| Numbers | 8-digit mantissa, exponent ±99 | p.5 |
| Angles | radians, degrees, grads | p.25 |
| Display | 12-position vacuum-fluorescent (ИЛЦ1-13/8Л) | p.5 |
| Power | 220 V mains | p.18 |

Where the manual is silent, the emulator follows the Б3-34 family, and each
such case is marked in the source. Transcendental functions are computed in
IEEE double and then truncated to 8 digits. They can differ from the real
chip in the last digit or two, which is within the manual's stated accuracy.

## Future work

**Chip-level emulation.** The schematic ([`pr2.bmp`](references/pr2.bmp))
shows К145ИК1302 and К145ИК1303 processors with КР145ИР2 registers. These
appear to be the same chips as in the Б3-34, and other projects have emulated
those chips at microcode level. If the identification holds, running the
chips' own microcode would reproduce the real machine's digits exactly,
including the transcendental functions. That would turn program 5.16, which
now loops forever (see [programs/AUDIT.md](programs/AUDIT.md)), into a
passing test. This needs a new arithmetic core, so it is a separate project.
The chip identification and the availability of ROM dumps are not yet
verified.

## License

MIT License with a mandatory attribution requirement. See [LICENSE](LICENSE).

**Attribution is required.** If you use, modify or distribute this
software, credit the author in your README, documentation or credits:
> Igor Berezhnoi - MK-56 Development Environment

## Contributing

Contributions are welcome, especially corrections to the translation and
to the program library. Please cite the page of the scan. See
[CONTRIBUTING.md](CONTRIBUTING.md).

## Acknowledgments

- The factory manual «Микрокалькулятор Электроника МК56. Техническое
  описание и инструкция по эксплуатации», digitised by ru-hpc.narod.ru
- В. П. Дьяконов, «Справочник по расчётам на микрокалькуляторах», Наука, 1985
