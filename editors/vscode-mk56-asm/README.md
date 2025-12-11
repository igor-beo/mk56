# MK-56 Assembly Language Extension

Syntax highlighting for MK-56 calculator assembly language.

## Features

- Syntax highlighting for:
  - **Opcodes**: Stack operations, arithmetic, math functions, control flow
  - **Registers**: R0-R9, RA-RD
  - **Numbers**: Integer, float, hex literals
  - **Labels**: Label definitions and references
  - **Comments**: Semicolon-prefixed comments
  - **Directives**: ORG, EQU, DB, DW, etc.

## Installation

### Manual Installation

1. Copy this folder to your VS Code extensions directory:
   - **macOS**: `~/.vscode/extensions/`
   - **Linux**: `~/.vscode/extensions/`
   - **Windows**: `%USERPROFILE%\.vscode\extensions\`

2. Restart VS Code

### Development

1. Open this folder in VS Code
2. Press `F5` to launch Extension Development Host
3. Open a `.asm` or `.mk56` file

## Supported Instructions

### Stack Operations
`NOP`, `ENTER`, `SWAP`, `CLX`, `PUSH`, `DUP`, `DROP`, `ROT`, `LASTX`

### Arithmetic
`ADD`, `SUB`, `MUL`, `DIV`, `NEG`, `ABS`, `CHS`

### Math Functions
`SQRT`, `SQR`, `INV`, `POW`, `EXP`, `EXP10`, `LN`, `LOG`, `SIN`, `COS`, `TAN`, `ASIN`, `ACOS`, `ATAN`, `PI`

### Memory
`STO Rx`, `RCL Rx` (where x is 0-9 or A-D)

### Control Flow
`JMP addr`, `JLT addr`, `JGE addr`, `JEQ addr`, `JNE addr`, `JSR addr`, `RTN`, `HALT`

## Example

```asm
; Calculate factorial
    PUSH 1       ; result = 1
    STO R0
loop:
    RCL R0       ; result *= n
    MUL
    STO R0
    PUSH 1       ; n -= 1
    SUB
    DUP
    JGE loop     ; if n > 0, continue
    DROP
    RCL R0       ; return result
    HALT
```
