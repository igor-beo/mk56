# 2. Device Structure and Operating Principles

## 2.1 Functional Capabilities

### 2.1.1 Calculation System

The calculator uses a **ten-digit decimal system** for input and output of information.

### 2.1.2 Number Representation

The MK-56 can represent numbers in multiple formats:

- **Mantissa digits**: 8 digits
- **Exponent range**: Two digits
- **Maximum positive value**: 1×10⁻⁹⁹ ≤ |x| < 9.9999999×10⁹⁹
- **Minimum positive value**: 1×10⁻⁹⁹ ≤ |x| < 9.9999999×10⁹⁹

Number formats supported:
1. **Fixed-point notation**: `±[x]×9999999` - constant display
2. **Scientific notation**: `±1×10⁻⁹⁹[±x]` and `9999999 ≤|x|≤ 9,9999999×10⁹⁹`

### 2.1.3 Decimal Place Handling

Numbers and calculation results are displayed with appropriate precision:
- **Mantissa**: Up to 8 significant digits
- **Exponent**: Displayed when the number is outside normal range
- **Decimal point**: 12-digit linear indicator (8 mantissa digits, 2 exponent digits, sign indicators)

### 2.1.4 Precision Specifications

| Function | Allowable Error Range | Maximum Relative Error |
|----------|----------------------|------------------------|
| sin x | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |
| cos x | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |
| tg x | 1×10⁻⁴⁹ < \|x\| < 1×10¹⁰ | 3×10⁻⁷ |
| arcsin x | \|x\| ≤ 1 | 3×10⁻⁷ |
| arccos x | \|x\| ≤ 1 | 3×10⁻⁷ |
| arctg x | \|x\| ⩽ 5.9999999×10⁹⁹ | 3×10⁻⁷ |
| xʸ | - | <cx |
| eˣ | \|x\| < 100·ln10 | 5×10⁻⁸ |
| xⁿ | \|x\| < 10⁵⁰ | 1×10⁻⁷ |
| 10ˣ | \|x\| < 99.999999 | 4×10⁻⁷ |
| 1/x | x ≠ 0 | 1×10⁻⁷ |
| √x | 0 < x | 1×10⁻⁴ |
| ln x | 0 < x | 3×10⁻⁷ |
| lg x | 0 < x | 3×10⁻⁷ |

### 2.1.5 Computation Time

Average execution times for various operations:

- **Basic arithmetic** (x², √x, 1/x, 10ˣ, sin x, cos x, tg x, arccos x, arcsin x, arctg x): ≤ 2 seconds
- **Functions** (ln x, lg x, eˣ, 10ˣ, sin x): ≤ 3.5 seconds

### 2.1.6 Display Capabilities

Results and intermediate calculations are displayed on a **12-digit linear indicator** with:
- 8 digits for mantissa
- 2 digits for exponent (power of 10)
- Sign indicators for mantissa and exponent

### 2.1.7 Operating Modes

The calculator operates in two modes:

1. **Automatic Mode**: Performs four arithmetic operations (+, -, ×, ÷) and allows execution of functions
2. **Programming Mode**: Enables program creation and execution

See:
- [Automatic Mode Operation](06-automatic-mode.md)
- [Programming Mode](07-programming-mode.md)

### 2.1.8 Memory Capacity

The MK-56 provides:
- **14 addressable registers** for data storage (RG0 ... RG13)
- **105 program steps** for storing calculation sequences

### 2.1.9 Programming Features

In Programming mode, the calculator allows:
1. Writing programs using the keyboard
2. Editing and correcting programs

### 2.1.10 Execution Time for Arithmetic Operations

Execution times for basic operations (1/x, √x, x², xʸ, 1/x):
- **x² function**: ≤ 3.5 seconds

Average execution times for functions (ln x, lg x, eˣ, 10ˣ, sin x, cos x, tg x, arccos x, arcsin x, arctg x): ≤ 2 seconds

### 2.1.11 Program Capabilities

The calculator can:
1. Store programs in memory up to 105 steps
2. Handle direct and indirect conditional jumps
3. Support subroutine calls and returns
4. Manage stack operations
5. Execute loops and iterations
6. Perform address calculations
7. Write information to memory registers and read from them
8. Organize cycles
9. Perform stack operations (address and number storage)
10. Execute commands for stopping and resuming program execution
11. Display the last three steps of the program and current address state
12. Restore previous calculation results
13. Perform constant calculations
14. Execute memory operations
15. Perform calculations with constants

### 2.1.12 Program Memory Expansion

For program memory expansion and program storage control, the calculator includes:
1. **Initial memory**: 8 program memory volumes
2. **Direct and indirect jump commands**: For program flow control
3. **Return commands**: For subroutine management

### 2.1.13 Ready Time

The calculator is ready for operation after power-on:
- **Initial ready time**: ≤ 30 seconds
- **Repeated power cycles**: Can reduce to ≤ 10 seconds minimum

### 2.1.14 Continuous Operation

The calculator can operate continuously without power-off for extended periods.

## 2.2 Operating Principles

### 2.2.1 Structural Diagram

The structural diagram of the microcalculator is shown in Figure 1 (see [Construction](09-construction.md) for detailed schematic).

The calculator consists of:
- **Memory blocks** (integrated circuits)
- **Control unit**
- **Arithmetic logic unit (ALU)**
- **Display unit**
- **Keyboard**
- **Power supply**

### 2.2.2 Memory System (RAM)

The calculator uses RAM (Random Access Memory) based on integrated circuits:
- **ЭМ 24** ... **ЭМ 27**: Series of memory ICs
- **ЭМ 25**: Controls the graphics microcalculator, receives information from keyboard ЭМ 24, and transmits it after processing to the indicator

The memory is organized hierarchically with registers numbered ЭМ 22 ... ЭМ 13, defined by ЭМ 24 and received in register memory ЭМ 1 ... ЭМ 8. Memory is accessed sequentially through a scanning process.

On the network, the indicator receives direction signals from ЭМ 35 B. When the network is de-energized, the indicator level drops and the network indicator lights up. The network indicator can be turned off through one of the memory registers.

### 2.2.3 Operational Block

The operational block of the microcalculator is organized as a sequential connection of memory registers ЭМ 24 ... 27 in a chain, forming a register memory structure with negative feedback. The synchronization of ЭМ 25 operations is achieved through a common memory access system, receiving signals for each functional block from ЭМ. Synchronous operation of ЭМ 25 is accomplished through a common memory system.

### 2.2.4 Control Unit (ЭМ)

The control unit ЭМ 24 controls the input of information from the keyboard, performs interrupt-driven internal information processing, and manages data flow to the indicator.

The unit also performs input of information into the "decision-making or not decision" mode. It also performs input of information related to the functioning system and functional capabilities of the microcalculator. Input of programs into OSU (Operational Storage Unit) is performed using the keyboard in programming mode, established by pressing the [П] key.

## Related Documents

- [Construction](09-construction.md) - Detailed internal structure
- [Electrical Schematic](11-electrical-schematic.md) - Circuit diagrams
- [Functional Capabilities](03-functional-capabilities.md) - Complete function listing
- [Key Functions Reference](15-key-reference.md) - Keyboard layout and functions
