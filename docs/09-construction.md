# 9. Construction

## 2.3 Construction

### 2.3.1 Overview

The MK-56 "Elektronika" microcalculator consists of several major components integrated into a compact handheld unit. This section describes the physical construction and internal organization of the device.

## Major Components

### 2.3.2 Electrical Circuit Board

The calculator is built around a printed circuit board (PCB) that houses all electronic components. See [PCB Layouts](12-pcb-layouts.md) for detailed layout information.

**Key features**:
- Single or double-sided PCB (varies by model)
- Integrated circuits mounted in sockets or soldered directly
- Discrete components (resistors, capacitors, diodes)
- Interconnections via copper traces

### 2.3.3 Housing and Case

The calculator is enclosed in a plastic housing consisting of:

#### Top Case
- Contains keyboard assembly
- Provides access to keys
- Houses display window
- May include labeling and legends

#### Bottom Case
- Protects PCB and components
- Contains battery compartment (if applicable)
- Provides structural support
- May include rubber feet or stands

#### Case Material
- Typically ABS or similar plastic
- Color: Beige, cream, or dark colors
- Finish: Matte or slightly textured

### 2.3.4 Keyboard Assembly

The keyboard is a critical interface component:

#### Key Structure
- **Keycaps**: Plastic caps with printed legends
- **Key switches**: Mechanical tactile switches
- **Contact method**: Conductive rubber or mechanical contacts
- **Mounting**: Keys mounted in keyboard matrix

#### Key Matrix
- Organized in rows and columns
- Scanned sequentially by control circuit
- Debouncing implemented in hardware or software

#### Key Layout
See [Key Functions Reference](15-key-reference.md) for complete keyboard layout.

### 2.3.5 Display Assembly

The display unit shows calculation results and program addresses:

#### Display Type
- **LED** (Light Emitting Diode) - Common in many models
  - Red color typical
  - High brightness
  - Higher power consumption
  
- **VFD** (Vacuum Fluorescent Display) - Some models
  - Blue-green color
  - Excellent visibility
  - Moderate power consumption

#### Display Structure
- **Digits**: 12 total positions
  - 8 mantissa digits
  - 2 exponent digits
  - Sign indicators (mantissa and exponent)
- **Segments**: 7-segment display per digit
- **Decimal points**: Between digits
- **Multiplexing**: Sequential digit activation to reduce power

#### Display Driver
- Dedicated driver ICs
- Converts BCD data to segment patterns
- Controls digit multiplexing
- Manages brightness (if adjustable)

### 2.3.6 Power Supply System

The power supply provides regulated voltage to all circuits:

#### Power Input
- **Battery power**: Rechargeable battery pack (some models)
- **External power**: DC adapter connection (some models)
- **Voltage regulation**: Converts input to required voltages

#### Power Distribution
- **Main voltage**: Typically +5V for logic circuits
- **Display voltage**: May differ from logic voltage
- **Ground**: Common ground plane

#### Battery System (if applicable)
- **Battery type**: NiCd or similar rechargeable cells
- **Capacity**: Varies by model
- **Charging circuit**: Built-in charger (some models)
- **Protection**: Reverse polarity protection

### 2.3.7 Integrated Circuits

The calculator uses multiple ICs for different functions:

#### Memory ICs
- **Program memory**: Stores program instructions
- **Data memory**: Stores register contents
- **Part numbers**: ЭМ series (Soviet designation)
- **Technology**: MOS or CMOS

#### Control and Processing ICs
- **Control unit**: Instruction decoding and sequencing
- **ALU**: Arithmetic and logic operations
- **Function generators**: Transcendental functions
- **Part numbers**: Various Soviet-era ICs

#### Support ICs
- **Display drivers**: Segment and digit drivers
- **Keyboard scanner**: Key matrix scanning
- **Clock generator**: Timing signals
- **Voltage regulators**: Power conditioning

### 2.3.8 Discrete Components

In addition to ICs, the calculator contains:

#### Resistors
- **Pull-up resistors**: Logic level maintenance
- **Current limiting**: Display segment protection
- **Timing resistors**: Clock and delay circuits
- **Values**: Various, typically 100Ω to 100kΩ

#### Capacitors
- **Decoupling**: Near each IC (0.1µF typical)
- **Power filtering**: Larger values (10µF to 100µF)
- **Timing**: Clock generation
- **Types**: Ceramic, electrolytic

#### Other Components
- **Diodes**: Protection, logic functions
- **Transistors**: Switching, amplification (if present)
- **Crystal**: Clock oscillator (if present)
- **Connectors**: Power, external connections

## Internal Organization

### 2.3.9 Functional Block Diagram

The calculator's internal organization follows this structure:

```
┌─────────────────────────────────────────────────┐
│                  Power Supply                    │
└──────────────────┬──────────────────────────────┘
                   │ (Power Distribution)
        ┌──────────┴──────────┬──────────────┐
        │                     │              │
┌───────▼────────┐   ┌────────▼──────┐   ┌──▼────────┐
│   Keyboard     │   │   Control     │   │  Display  │
│   Interface    │──▶│     Unit      │──▶│  Driver   │
└────────────────┘   └───────┬───────┘   └───────────┘
                             │
                    ┌────────┴────────┐
                    │                 │
            ┌───────▼──────┐   ┌──────▼──────┐
            │   Memory     │   │     ALU     │
            │   System     │◀─▶│  (Arithmetic│
            │              │   │    Logic)   │
            └──────────────┘   └─────────────┘
```

### 2.3.10 Signal Flow

#### Input Path
1. User presses key
2. Keyboard scanner detects key press
3. Key code sent to control unit
4. Control unit processes input

#### Processing Path
1. Control unit fetches instruction
2. Instruction decoded
3. ALU performs operation
4. Result stored in memory

#### Output Path
1. Memory contents read
2. Data formatted for display
3. Display driver activates segments
4. User sees result

## Physical Assembly

### 2.3.11 Assembly Structure

The calculator is assembled in layers:

1. **Bottom case**: Base structure
2. **PCB**: Mounted on standoffs or clips
3. **Display**: Mounted above PCB, visible through top case
4. **Keyboard**: Mounted in top case, contacts PCB
5. **Top case**: Snaps or screws to bottom case

### 2.3.12 Mounting and Fasteners

- **Screws**: Phillips or flat head (typically 2-6 screws)
- **Clips**: Plastic snap-fit clips
- **Standoffs**: Separate PCB from case
- **Adhesive**: May be used for display or labels

### 2.3.13 Sealing and Protection

- **Not waterproof**: No sealing against moisture
- **Dust protection**: Limited (case gaps present)
- **Impact protection**: Plastic case provides basic protection
- **ESD protection**: Limited (handle with care)

## Serviceability

### 2.3.14 User-Serviceable Parts

- **Battery**: Can be replaced by user (if removable)
- **Case**: Can be opened with screwdriver
- **Cleaning**: External cleaning possible

### 2.3.15 Service-Level Access

Requires qualified technician:
- **IC replacement**: Requires desoldering/resoldering
- **PCB repair**: Requires electronics skills
- **Display replacement**: Requires disassembly
- **Keyboard repair**: May require replacement parts

### 2.3.16 Non-Serviceable Components

- **Sealed ICs**: Cannot be repaired internally
- **PCB traces**: Difficult to repair if damaged
- **Display elements**: Individual segments not replaceable

## Variations Between Models

### 2.3.17 Production Variations

Different production runs may have:
- Different IC manufacturers or part numbers
- Component value variations (within tolerance)
- PCB layout differences
- Case color or style variations
- Display type differences (LED vs VFD)

### 2.3.18 Regional Variations

Models for different markets may differ in:
- Power supply voltage
- Keyboard legends (language)
- Documentation
- Accessories

## Related Documents

- [Electrical Schematic](11-electrical-schematic.md) - Circuit diagram
- [PCB Layouts](12-pcb-layouts.md) - PCB design details
- [Technical Specifications](10-specifications.md) - Component specifications
- [Technical Maintenance](13-maintenance.md) - Service procedures
- [Device Overview](02-device-overview.md) - Functional description
