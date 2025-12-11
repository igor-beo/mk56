# 12. PCB Layouts

## Overview

This document describes the printed circuit board (PCB) layouts for the MK-56 "Elektronika" microcalculator. The calculator uses multiple PCB layers to implement its complex circuitry.

## PCB Structure

The MK-56 uses a multi-layer PCB design with:
- **Component side**: Top layer with IC sockets and components
- **Solder side**: Bottom layer with solder connections
- **Internal layers**: Power and ground planes (if multi-layer)

## PCB Layout Diagrams

### Main PCB - Component Side (Top Layer)

![PCB Layout - Component Side](../pr3_1_temp.png)

**Figure 1**: Main PCB Component Side Layout

This layout shows:
- **IC placement**: Locations of all integrated circuits
- **Component positions**: Resistors, capacitors, and other discrete components
- **Connector locations**: Keyboard connector, display connector, power connector
- **Mounting holes**: PCB mounting points

**Key Areas**:
- **Left section**: Memory and control ICs
- **Center section**: ALU and processing circuits
- **Right section**: Display drivers and power supply
- **Bottom section**: Keyboard interface

### Main PCB - Solder Side (Bottom Layer)

![PCB Layout - Solder Side](../pr3_2_temp.png)

**Figure 2**: Main PCB Solder Side Layout

This layout shows:
- **Trace routing**: Copper traces connecting components
- **Via locations**: Connections between layers
- **Ground plane**: Ground distribution
- **Power distribution**: Power supply routing

**Routing Characteristics**:
- **Trace width**: Varies by current requirements
- **Spacing**: Adequate clearance for voltage isolation
- **Via density**: Strategic placement for signal integrity
- **Ground plane**: Continuous ground for noise reduction

### Component Placement Diagram

![PCB Component Placement](../pr3_3_temp.png)

**Figure 3**: Component Placement and Identification

This diagram shows:
- **Component designators**: D1, D2, D3, etc. for ICs
- **Component values**: Resistor and capacitor values
- **Polarity markings**: For electrolytic capacitors and diodes
- **Pin 1 indicators**: IC orientation markers

## Component Layout Details

### Integrated Circuits

The PCB contains multiple ICs organized by function:

#### Memory Section (Left Area)
- **D1-D4**: Memory ICs for program and data storage
- **D5-D6**: Address decoding and memory control
- **Socket type**: DIP (Dual In-line Package)
- **Pin count**: Varies (14, 16, 20, 24, 28 pins)

#### Control Section (Center-Left)
- **D7-D10**: Control logic and instruction processing
- **Clock generation**: Timing circuits
- **Interconnections**: Dense routing to memory and ALU

#### ALU Section (Center)
- **D11-D14**: Arithmetic and logic processing
- **Function generators**: For transcendental functions
- **Data paths**: Wide buses for parallel processing

#### Display Section (Center-Right)
- **D15-D18**: Display drivers
- **Digit multiplexing**: Sequential digit activation
- **Segment drivers**: Individual segment control

#### Power Supply Section (Right)
- **Voltage regulators**: Power conditioning
- **Filter capacitors**: Power supply smoothing
- **Protection diodes**: Reverse polarity protection

### Discrete Components

#### Resistors
- **R1-R50**: Various resistor values
- **Pull-up resistors**: Logic level maintenance
- **Current limiting**: Display segment protection
- **Timing resistors**: Clock and delay circuits

#### Capacitors
- **C1-C30**: Various capacitor values
- **Decoupling capacitors**: Near each IC for noise reduction
- **Filter capacitors**: Power supply filtering
- **Timing capacitors**: Clock generation

#### Other Components
- **Diodes**: Protection and logic functions
- **Transistors**: Switching and amplification
- **Crystal**: Clock oscillator (if present)
- **Connectors**: Keyboard, display, power

## PCB Specifications

### Physical Dimensions
- **Length**: Approximately 150-180mm (varies by model)
- **Width**: Approximately 80-100mm
- **Thickness**: Standard PCB thickness (1.6mm typical)

### Material
- **Base material**: FR-4 epoxy fiberglass
- **Copper weight**: 1 oz (35 μm) typical
- **Surface finish**: Tin-lead or HASL (Hot Air Solder Leveling)

### Layer Stack-up
- **Single-sided**: Early models (traces on one side only)
- **Double-sided**: Most common (traces on both sides)
- **Multi-layer**: Advanced models (internal power/ground planes)

### Trace Specifications
- **Minimum trace width**: 0.2-0.3mm
- **Minimum spacing**: 0.2-0.3mm
- **Via diameter**: 0.8-1.0mm
- **Pad diameter**: 1.5-2.0mm

## Assembly Notes

### IC Installation
1. **Orientation**: Align pin 1 with PCB marking
2. **Socket use**: ICs typically installed in sockets for serviceability
3. **Insertion**: Ensure all pins properly seated
4. **Soldering**: Clean solder joints, avoid bridges

### Component Polarity
- **Electrolytic capacitors**: Observe polarity markings
- **Diodes**: Cathode band alignment
- **ICs**: Pin 1 indicator (notch or dot)
- **Connectors**: Keyed for correct orientation

### Soldering Guidelines
1. **Temperature**: 300-350°C for lead-based solder
2. **Time**: 2-3 seconds per joint
3. **Inspection**: Visual check for cold joints and bridges
4. **Cleaning**: Remove flux residue if required

## Testing Points

The PCB includes test points for troubleshooting:

### Power Supply Test Points
- **+5V**: Main logic supply
- **GND**: Ground reference
- **Other voltages**: As required by design

### Signal Test Points
- **Clock signals**: Verify timing
- **Data bus**: Check data flow
- **Control signals**: Verify sequencing

### Critical Signals
- **Reset**: System initialization
- **Keyboard scan**: Input verification
- **Display refresh**: Output verification

## Common Issues and Repairs

### Typical Failures
1. **Cold solder joints**: Reflow affected joints
2. **Cracked traces**: Repair with wire jumpers
3. **Failed ICs**: Replace with equivalent parts
4. **Corroded contacts**: Clean and re-tin

### Repair Procedures
1. **Visual inspection**: Check for obvious damage
2. **Continuity testing**: Verify trace integrity
3. **Component testing**: Test ICs and discrete components
4. **Replacement**: Use equivalent or compatible parts

### Preventive Maintenance
- **Cleaning**: Remove dust and debris
- **Inspection**: Regular visual checks
- **Contact cleaning**: Maintain connector integrity
- **Storage**: Protect from moisture and temperature extremes

## Modifications

### Common Modifications
1. **Memory expansion**: Additional RAM ICs (if supported)
2. **Display upgrade**: LED to LCD conversion (complex)
3. **Power supply**: Modern battery compatibility
4. **Connector replacement**: Modern equivalents

### Modification Cautions
- **Compatibility**: Ensure component compatibility
- **Timing**: Maintain critical timing relationships
- **Power**: Verify power requirements
- **Testing**: Thorough testing after modifications

## PCB Manufacturing Data

### For Reproduction
If reproducing the PCB:
1. **Scan original**: High-resolution scans of both sides
2. **Trace recreation**: CAD software to recreate layout
3. **Component footprints**: Verify against original
4. **Drill file**: Accurate via and hole positions
5. **Silkscreen**: Component designators and markings

### Manufacturing Specifications
- **Copper thickness**: 1 oz (35 μm)
- **Solder mask**: Green (typical), other colors possible
- **Silkscreen**: White on green background
- **Surface finish**: HASL or ENIG for modern reproduction

## Related Documents

- [Electrical Schematic](11-electrical-schematic.md) - Circuit diagram
- [Construction](09-construction.md) - Physical assembly
- [Technical Maintenance](13-maintenance.md) - Service procedures
- [Technical Specifications](10-specifications.md) - Performance data

## Notes

1. **Original vs. Reproduction**: Modern PCB manufacturing may differ from original Soviet-era processes
2. **Component Availability**: Some original components may be obsolete; use equivalents
3. **Reverse Engineering**: PCB layouts derived from physical examination and schematics
4. **Accuracy**: Layouts represent typical design; variations exist between production runs
5. **Safety**: Handle PCBs with ESD precautions; avoid contact with powered circuits
