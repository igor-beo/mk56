# MK-56 Elektronika Development Environment

<p align="center">
  <img src="docs/images/mk56-calculator.png" alt="MK-56 Calculator" width="300">
</p>

A complete development toolkit for the **MK-56 "Elektronika"** Soviet programmable calculator, featuring an assembly language, cross-platform assemblers, and an interactive emulator.

## 🎯 Overview

The MK-56 was a Soviet programmable RPN calculator produced in the 1980s. This project provides modern tools to:

- Write programs in human-readable **MK56-ASM** assembly language
- Assemble programs using C or Python assemblers
- Run and debug programs in an interactive emulator with TUI

```
.asm source  ──▶  assembler  ──▶  .bin binary  ──▶  emulator  ──▶  result
```

## 📦 Components

| Component | Language | Description |
|-----------|----------|-------------|
| [asm/assembler-c/](asm/assembler-c/) | C | High-performance assembler |
| [asm/assembler-python/](asm/assembler-python/) | Python | Cross-platform assembler |
| [asm/emulator/](asm/emulator/) | C | Interactive emulator with ncurses TUI |
| [asm/examples/](asm/examples/) | MK56-ASM | Example programs |
| [docs/](docs/) | Markdown | Complete device documentation |
| [programs/](programs/) | - | Mathematical program library |
| [editors/](editors/) | - | IDE extensions (VSCode) |

## 🚀 Quick Start

### Build

```bash
# Build C assembler
cd asm/assembler-c && make && cd ../..

# Build emulator
cd asm/emulator && make && cd ../..
```

### Write a Program

```asm
; square.asm - Calculate x²
        SQ              ; Square X register
        HALT            ; Stop and display result
.END
```

### Assemble & Run

```bash
# Assemble
./asm/assembler-c/mk56asm square.asm

# Run with input value 5
./asm/emulator/mk56emu square.bin -c -i 5
# Result: X = 25
```

## 📐 MK56-ASM Language

### Instruction Categories

| Category | Instructions |
|----------|--------------|
| **Stack** | `ENTER`, `SWAP`, `CLX`, `ROLLDOWN`, `ROLLUP` |
| **Arithmetic** | `ADD`, `SUB`, `MUL`, `DIV`, `CHS` |
| **Math** | `SQ`, `SQRT`, `INV`, `POW`, `EXP`, `LN`, `LOG`, `SIN`, `COS`, `PI` |
| **Memory** | `STO Rn`, `RCL Rn`, `STO+ Rn`, `STO- Rn` |
| **Flow** | `JMP`, `JGE`, `JLT`, `CALL`, `RTN`, `HALT` |

See [MK56-ASM-SPEC.md](asm/MK56-ASM-SPEC.md) for complete specification.

## 📖 Documentation

- **[asm/MK56-ASM-SPEC.md](asm/MK56-ASM-SPEC.md)** - Assembly language specification
- **[asm/INSTRUCTION-SET.md](asm/INSTRUCTION-SET.md)** - Quick reference card
- **[docs/](docs/)** - Complete MK-56 device documentation (translated from Russian)
- **[programs/](programs/)** - Mathematical program library from Dyakonov's reference

## 🔧 Calculator Specifications

| Feature | Value |
|---------|-------|
| Program steps | 105 max |
| Registers | 14 (R0-R9, RA-RD) |
| Stack levels | 4 (X, Y, Z, T) |
| Number range | ±10⁻⁹⁹ to ±10⁹⁹ |
| Precision | 8 significant digits |

## 🛠️ IDE Support

- **[VSCode Extension](editors/vscode-mk56-asm/)** - Syntax highlighting for `.asm` files

## 📚 References

Original documentation and source materials are preserved in the [references/](references/) folder.

## 📜 License

MIT License - See [LICENSE](LICENSE)

**Attribution Required**: When using this software, please credit:
> Igor Scobi (scobi84) - MK-56 Development Environment

## 🤝 Contributing

Contributions welcome! Please read [CONTRIBUTING.md](CONTRIBUTING.md) before submitting PRs.

## 🙏 Acknowledgments

- Original MK-56 documentation from Soviet technical manuals
- V.P. Dyakonov's "Reference Manual for Calculations on Microcalculators" (1985)
