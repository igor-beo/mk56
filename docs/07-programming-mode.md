# 7. Programming Mode

## Overview

Programming mode enables you to create, store, and execute sequences of operations (programs) on the MK-56 calculator. Programs can contain up to 105 steps and utilize conditional jumps, subroutines, and loops.

## 6. Working in "Programming-50" Mode

### 6.1 General Information

The MK-56 operates in two modes:
1. **Automatic Mode** - Direct calculation execution
2. **Programming Mode** - Program creation and execution

To enter Programming mode:
- Press [ПРГ] key

The display will show the current program address (00 to 104).

To exit Programming mode and return to Automatic mode:
- Press [ПРГ] key again

### 6.2 Program Entry Steps

When entering a program, each keystroke is recorded as a program step at the current address. The address automatically increments after each entry.

#### Program Entry Process

1. Press [ПРГ] to enter Programming mode
2. Display shows current address (e.g., `00`)
3. Enter commands by pressing keys
4. Each key press records one program step
5. Address increments automatically
6. Press [ПРГ] to exit when complete

#### Example: Simple Program Entry

To create a program that calculates x² + 5:

| Step | Key Press | Address | Command Stored |
|------|-----------|---------|----------------|
| 1 | [ПРГ] | 00 | (Enter programming mode) |
| 2 | [x²] | 00 | Square function |
| 3 | [5] | 01 | Constant 5 |
| 4 | [+] | 02 | Addition |
| 5 | [С/П] | 03 | Stop |
| 6 | [ПРГ] | 04 | (Exit programming mode) |

### 6.3 Jump Commands

Jump commands allow program flow control, enabling loops and conditional execution.

#### Unconditional Jump [БП]

**Command**: [БП] [nn]

Jumps program execution to address nn unconditionally.

**Usage**:
1. Press [БП]
2. Enter two-digit address (00-99)
3. Program will jump to that address when executed

**Example**: Jump to address 20
- Press: [БП] [2] [0]

#### Conditional Jump [x≥0]

**Command**: [x≥0] [nn]

Jumps to address nn if the value in register X is greater than or equal to zero.

**Usage**:
1. Press [x≥0]
2. Enter two-digit address
3. If X ≥ 0, jump to address; otherwise continue to next step

**Example**: Jump to address 50 if X ≥ 0
- Press: [x≥0] [5] [0]

#### Conditional Jump [x<0]

**Command**: [x<0] [nn]

Jumps to address nn if the value in register X is less than zero.

### 6.4 Subroutine Commands

Subroutines allow modular programming by calling reusable code sections.

#### Call Subroutine [В/О]

**Command**: [В/О] [nn]

Calls a subroutine starting at address nn. The return address is automatically saved.

**Usage**:
1. Press [В/О]
2. Enter subroutine start address
3. Program jumps to subroutine
4. Subroutine must end with [В/О] to return

#### Return from Subroutine [В/О]

**Command**: [В/О]

Returns from subroutine to the instruction following the call.

**Usage**:
- Place [В/О] at end of subroutine
- Program returns to saved address

**Example Subroutine Structure**:

```
Main Program:
00: [В/О] [2] [0]  ; Call subroutine at address 20
01: [С/П]          ; Stop

...

Subroutine:
20: [x²]           ; Square X
21: [5]            ; Enter 5
22: [+]            ; Add
23: [В/О]          ; Return to main program
```

### 6.5 Program Execution Control

#### Stop/Pause [С/П]

**Command**: [С/П]

- **During program entry**: Records a stop command
- **During program execution**: Stops the program and displays result
- **When stopped**: Pressing [С/П] resumes execution

**Usage**:
- Place [С/П] where you want program to pause
- Useful for viewing intermediate results
- Press [С/П] to continue after stop

#### Program Start

To run a program:

1. Exit Programming mode (press [ПРГ] if in programming mode)
2. Enter input value(s) if needed
3. Press [В/О] to start program from address 00
4. Or press [БП] [nn] [С/П] to start from address nn

### 6.6 Address Display and Navigation

#### Viewing Current Address

In Programming mode:
- Display shows current program address
- Format: two digits (00-99 or 00-104 for extended memory)

#### Moving to Specific Address

To jump to a specific address for editing:

1. Enter Programming mode [ПРГ]
2. Press [БП]
3. Enter desired address
4. Press [С/П]
5. Calculator moves to that address

**Example**: Go to address 25
- Press: [ПРГ] [БП] [2] [5] [С/П]

### 6.7 Program Editing

#### Inserting Steps

To insert a step at current address:
1. Navigate to desired address
2. Enter new command
3. Subsequent commands shift to higher addresses

#### Deleting Steps

To delete a step:
1. Navigate to the step
2. Press [←] (backspace)
3. Subsequent commands shift to lower addresses

#### Overwriting Steps

To replace a step:
1. Navigate to the step
2. Enter new command
3. Old command is overwritten

### 6.8 Memory Register Operations in Programs

Programs can store and recall values from the 14 addressable registers.

#### Store to Register

**Command**: [x→П] [n]

Stores value from X to register n (0-13).

**In program**:
- Records as one or two program steps
- Executes during program run

#### Recall from Register

**Command**: [П→x] [n]

Recalls value from register n to X.

**In program**:
- Records as one or two program steps
- Executes during program run

#### Register Operations

**Add to register**: [П] [+] [n]
**Subtract from register**: [П] [−] [n]

These operations modify register contents without affecting X.

### 6.9 Loop Construction

Loops are created using counters in registers and conditional jumps.

#### Basic Loop Structure

```
00: [1] [0]        ; Initialize counter (10 iterations)
01: [x→П] [0]      ; Store counter in RG0
02: ...            ; Loop body starts
...
10: [П→x] [0]      ; Recall counter
11: [1]            ; Enter 1
12: [−]            ; Subtract 1
13: [x→П] [0]      ; Store decremented counter
14: [x≥0] [0] [2]  ; If counter ≥ 0, jump to address 02
15: [С/П]          ; Stop (loop complete)
```

### 6.10 Program Memory Organization

The MK-56 provides 105 program steps (addresses 00-104).

#### Memory Layout

- **Addresses 00-99**: Primary program memory
- **Addresses 100-104**: Extended memory (accessed with special addressing)

#### Address Format

- **Two-digit addresses**: 00-99 (standard)
- **Three-digit addresses**: 100-104 (extended, requires special entry)

### 6.11 Program Examples

See [Calculation Examples](08-examples.md) for detailed programming examples including:
- Percentage calculations
- Sum and product calculations
- Numerical sequences
- Mathematical expectation
- "Radiological" problem solving
- Equation solving

## Related Documents

- [Calculation Examples](08-examples.md) - Complete program examples
- [Programming Commands](16-programming-commands.md) - Command reference
- [Key Functions Reference](15-key-reference.md) - Key descriptions
- [Automatic Mode Operation](06-automatic-mode.md) - Basic operations
