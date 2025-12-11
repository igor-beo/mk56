# 11. Electrical Schematic

## Overview

This document describes the principal electrical schematic of the MK-56 "Elektronika" microcalculator. The schematic shows the interconnections between major functional blocks and components.

## Schematic Diagram

The complete electrical schematic is shown in the diagram below (from pr2.bmp):

![MK-56 Electrical Schematic](../pr2_temp.png)

**Figure**: Principal Electrical Schematic of the Microcalculator

## Major Functional Blocks

The electrical schematic is organized into the following major functional blocks:

### 1. Memory Block (Left Section)

**Components**:
- Multiple integrated circuits (ICs) for data storage
- Memory registers organized in banks
- Address decoding circuitry

**Function**:
- Stores program instructions (105 steps)
- Stores data in 14 addressable registers (RG0-RG13)
- Provides temporary storage for stack operations (T, Z, Y, X registers)

**Key ICs**:
- Memory management ICs
- Register banks
- Address decoders

### 2. Control Unit (Center-Left Section)

**Components**:
- Control logic ICs
- Timing and synchronization circuits
- Instruction decoder

**Function**:
- Decodes and executes program instructions
- Manages program flow (jumps, subroutines)
- Coordinates operations between functional blocks
- Handles keyboard input processing

**Key Signals**:
- Clock signals for synchronization
- Control signals for memory access
- Instruction decode outputs

### 3. Arithmetic Logic Unit - ALU (Center Section)

**Components**:
- Arithmetic processing ICs
- Logic gates for operations
- Function generators for transcendental functions

**Function**:
- Performs arithmetic operations (+, −, ×, ÷)
- Executes mathematical functions (sin, cos, ln, lg, etc.)
- Handles number format conversions
- Manages decimal point positioning

**Operations Supported**:
- Basic arithmetic: addition, subtraction, multiplication, division
- Power functions: x², √x, xʸ, 10ˣ, eˣ
- Trigonometric: sin, cos, tan, arcsin, arccos, arctan
- Logarithmic: ln, lg
- Reciprocal: 1/x

### 4. Display Driver (Center-Right Section)

**Components**:
- Display driver ICs
- Segment decoders
- Digit multiplexing circuits

**Function**:
- Drives 12-digit LED/VFD display
- Manages digit multiplexing
- Controls decimal point and sign indicators
- Formats numbers for display (mantissa + exponent)

**Display Format**:
- 8 mantissa digits
- 2 exponent digits
- Mantissa sign indicator
- Exponent sign indicator

### 5. Keyboard Interface (Bottom Section)

**Components**:
- Key matrix scanning circuit
- Debounce logic
- Key code encoder

**Function**:
- Scans keyboard matrix
- Detects key presses
- Generates key codes for control unit
- Handles key debouncing

**Keyboard Layout**:
- Numeric keys (0-9)
- Function keys
- Operation keys
- Programming control keys

### 6. Power Supply (Right Section)

**Components**:
- Voltage regulators
- Power conditioning circuits
- Battery charging circuit (if applicable)

**Function**:
- Provides regulated power to all circuits
- Manages battery charging
- Power-on reset generation
- Voltage monitoring

**Power Specifications**:
- Operating voltage: Regulated DC
- Battery type: Rechargeable (specific type varies by model)
- Operating time: ~30 seconds continuous (extendable to 10 seconds minimum)

## Signal Flow

### Calculation Flow

1. **Input**: User presses key → Keyboard Interface
2. **Processing**: Keyboard code → Control Unit → Instruction decode
3. **Execution**: Control Unit → ALU (performs operation)
4. **Storage**: ALU result → Memory Block (registers)
5. **Output**: Memory → Display Driver → Display

### Program Execution Flow

1. **Fetch**: Control Unit reads instruction from Program Memory
2. **Decode**: Control Unit decodes instruction
3. **Execute**: Appropriate functional block executes operation
4. **Store**: Results stored in registers or stack
5. **Next**: Control Unit advances to next instruction (or jumps)

## Timing Diagrams

The schematic includes timing diagrams (top-right section) showing:

### Clock Signals
- Master clock frequency
- Derived timing signals
- Phase relationships

### Control Signals
- Memory read/write timing
- Display refresh timing
- Keyboard scan timing

### Data Signals
- Data bus timing
- Address bus timing
- Control bus timing

## Component Specifications

### Integrated Circuits

The schematic uses various Soviet-era integrated circuits:

**Memory ICs**:
- ЭМ (EM) series - Memory management
- Specific part numbers vary by production batch

**Logic ICs**:
- Standard TTL or CMOS logic families
- Custom calculator-specific ICs

**Display Drivers**:
- LED/VFD driver ICs
- Multiplexing controllers

### Passive Components

**Resistors**:
- Pull-up resistors for logic signals
- Current limiting for display segments
- Timing resistors

**Capacitors**:
- Power supply decoupling
- Timing capacitors
- Filter capacitors

**Other Components**:
- Diodes for protection and logic
- Transistors for switching
- Crystal oscillator for timing

## Circuit Analysis

### Memory Organization

The memory system uses a hierarchical structure:

```
Program Memory (105 steps)
├── Address 00-99 (primary)
└── Address 100-104 (extended)

Data Memory (14 registers)
├── RG0-RG9 (direct access)
└── RG10-RG13 (extended access)

Stack Memory (4 levels)
├── T (top)
├── Z
├── Y
└── X (display register)
```

### Data Path Width

- **Internal data bus**: Parallel BCD (Binary Coded Decimal)
- **Mantissa**: 8 BCD digits
- **Exponent**: 2 BCD digits
- **Signs**: Separate bits for mantissa and exponent signs

### Instruction Format

Program instructions are stored in a compact format:
- **Operation code**: Identifies the operation
- **Operand**: Register number or address (if applicable)
- **Modifiers**: Additional flags or parameters

## Power Consumption

The calculator is designed for low power consumption:

- **Active mode**: Moderate power draw during calculations
- **Display**: Significant power consumer (multiplexed to reduce consumption)
- **Idle mode**: Reduced power when not in use
- **Power-off**: Complete shutdown to preserve battery

## Circuit Protection

The schematic includes protection features:

- **Reverse polarity protection**: Prevents damage from incorrect battery insertion
- **Overvoltage protection**: Protects against excessive input voltage
- **ESD protection**: Electrostatic discharge protection on inputs
- **Thermal protection**: Prevents overheating damage

## Modifications and Variants

Different production runs and models may have variations:

- Component substitutions (equivalent parts)
- Layout optimizations
- Additional features in later models
- Regional variations

## Related Documents

- [Construction](09-construction.md) - Physical construction details
- [PCB Layouts](12-pcb-layouts.md) - Printed circuit board designs
- [Technical Specifications](10-specifications.md) - Performance specifications
- [Device Overview](02-device-overview.md) - Functional block descriptions

## Notes

1. The schematic represents the principal design; actual production units may vary
2. Component values and part numbers should be verified against actual hardware
3. Repair and modification should only be performed by qualified technicians
4. Original Soviet IC part numbers may have modern equivalents
