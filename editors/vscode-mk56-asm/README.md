# MK-56 Assembly Language Extension

Syntax highlighting for MK56-ASM (`.asm`) and for programs in the original
listing notation (`.mk56`, e.g. `00: ИП2 Fx² В↑ Fπ × 4 ÷ С/П`).

## Features

- MK56-ASM mnemonics, registers (`R0`–`RD`, `(R3)`), labels, number literals
- Original keys: `ИП3`, `КБП3`, `Fx≠0`, `FL0`, `В/О`, `С/П`, `В↑`, `↔`, `F√` …
- `NN:` address markers, directives (`.ORG`, `.LISTING`, `.STEP` …)
- Test directives in comments (`; @input 5`, `; @expect X=120`)

See [asm/MK56-ASM-SPEC.md](../../asm/MK56-ASM-SPEC.md) for the language.

## Installation

1. Copy this folder to your VS Code extensions directory:
   - **macOS / Linux**: `~/.vscode/extensions/`
   - **Windows**: `%USERPROFILE%\.vscode\extensions\`
2. Restart VS Code.

For development, open this folder in VS Code and press `F5`.

The extension claims every `.asm` file. If you also work with other
assembly languages, pick the language per file with "Change Language Mode",
or remove `.asm` from `package.json`.
