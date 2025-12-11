# Getting Started

## Prerequisites

- **C Compiler**: GCC or Clang (for C assembler and emulator)
- **Python 3.6+**: (for Python assembler)
- **ncurses**: Required for emulator TUI

### macOS

```bash
# ncurses is included with Xcode Command Line Tools
xcode-select --install
```

### Linux (Ubuntu/Debian)

```bash
sudo apt-get install build-essential libncurses5-dev
```

## Building the Tools

### 1. Clone the Repository

```bash
git clone https://github.com/scobi84/mk56.git
cd mk56
```

### 2. Build the C Assembler

```bash
cd asm/assembler-c
make
cd ../..
```

### 3. Build the Emulator

```bash
cd asm/emulator
make
cd ../..
```

## Your First Program

### 1. Create a Source File

Create `hello.asm`:

```asm
; hello.asm - Square the input
        SQ              ; X = X²
        HALT            ; Stop
.END
```

### 2. Assemble

```bash
./asm/assembler-c/mk56asm hello.asm
```

This creates `hello.bin`.

### 3. Run

```bash
# Console mode with input value 5
./asm/emulator/mk56emu hello.bin -c -i 5
```

Output: `X = 25.000000`

### 4. Interactive Mode

```bash
./asm/emulator/mk56emu hello.bin
```

This opens the ncurses TUI where you can:
- Step through instructions
- View stack and registers
- Set breakpoints

## Next Steps

- Read the [[Assembly Language Reference]]
- Explore [[Example Programs]]
- Check the [full specification](../asm/MK56-ASM-SPEC.md)
