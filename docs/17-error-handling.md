# 17. Error Handling and Troubleshooting

## Overview

This document describes error conditions, error messages, and troubleshooting procedures for the MK-56 calculator.

## Error Conditions

### 1. Arithmetic Errors

#### 1.1 Division by Zero

**Cause**: Attempting to divide any number by zero

**Example**:
```
[5] [ВП] [0] [÷]
```

**Error Indication**: Display shows error state

**Recovery**:
1. Press [СХ] to clear error
2. Re-enter calculation with non-zero divisor

**Prevention**: Always verify divisor is non-zero before division

#### 1.2 Overflow

**Cause**: Result exceeds maximum representable value (> 9.9999999×10⁹⁹)

**Example**:
```
[9][•][9][9][9][9][9][9][9][ВП][1][0][0][Г][10ˣ][×]
```

**Error Indication**: Display shows error or maximum value

**Recovery**:
1. Press [СХ] to clear
2. Break calculation into smaller steps
3. Use logarithms for very large numbers

**Prevention**: 
- Monitor intermediate results
- Use scientific notation appropriately
- Scale calculations when possible

#### 1.3 Underflow

**Cause**: Result smaller than minimum representable value (< 1×10⁻⁹⁹)

**Example**: Very small number divided by very large number

**Error Indication**: May display as zero or error

**Recovery**:
1. Press [СХ] to clear
2. Rescale calculation
3. Use different approach

**Prevention**: Be aware of number magnitude in calculations

### 2. Domain Errors

#### 2.1 Square Root of Negative Number

**Cause**: Attempting √x where x < 0

**Example**:
```
[5] [/~/] [√x]  ; √(-5)
```

**Error Indication**: Error displayed

**Recovery**:
1. Press [СХ] to clear
2. Verify input is positive
3. Re-enter calculation

**Prevention**: Check sign before square root operation

#### 2.2 Logarithm of Zero or Negative

**Cause**: Attempting ln(x) or lg(x) where x ≤ 0

**Examples**:
```
[0] [Г] [ln]     ; ln(0)
[5] [/~/] [Г] [lg]  ; lg(-5)
```

**Error Indication**: Error displayed

**Recovery**:
1. Press [СХ] to clear
2. Verify input is positive
3. Re-enter calculation

**Prevention**: Ensure argument is positive before logarithm

#### 2.3 Invalid Trigonometric Input

**Cause**: Input outside valid range for inverse trig functions

**Examples**:
```
[2] [Г] [arcsin]  ; arcsin(2), valid range is [-1, 1]
```

**Error Indication**: Error displayed

**Recovery**:
1. Press [СХ] to clear
2. Verify input is in valid range
3. Re-enter calculation

**Prevention**: Know domain restrictions:
- arcsin, arccos: |x| ≤ 1
- arctan: all real numbers

### 3. Memory Errors

#### 3.1 Memory Corruption

**Cause**: 
- Power interruption
- Low battery
- Hardware malfunction

**Symptoms**:
- Unexpected values in registers
- Program execution errors
- Random calculation errors

**Recovery**:
1. Clear all memory registers
2. Re-enter programs
3. Test with known calculations
4. If persists, see [Technical Maintenance](13-maintenance.md)

**Prevention**:
- Maintain adequate battery charge
- Avoid power interruptions during programming
- Regularly backup important programs (on paper)

#### 3.2 Program Memory Full

**Cause**: Program exceeds 105 steps

**Symptoms**: Cannot enter more program steps

**Recovery**:
1. Optimize program to use fewer steps
2. Use subroutines to reuse code
3. Split into multiple programs if possible

**Prevention**: Plan program structure before entry

### 4. Display Errors

#### 4.1 Blank Display

**Possible Causes**:
- Power off
- Dead batteries
- Display failure
- Power supply failure

**Troubleshooting**:
1. Check power switch
2. Replace batteries
3. Verify external power (if applicable)
4. See [Technical Maintenance](13-maintenance.md)

#### 4.2 Dim Display

**Possible Causes**:
- Low battery
- Brightness setting (if adjustable)
- Aging display
- Power supply issue

**Troubleshooting**:
1. Replace batteries
2. Adjust brightness
3. Check power supply voltage
4. May require service

#### 4.3 Missing Segments

**Possible Causes**:
- Display failure
- Driver IC failure
- Broken connections

**Troubleshooting**:
1. Note which segments are missing
2. Test with different numbers
3. Requires professional repair

#### 4.4 Flickering Display

**Possible Causes**:
- Low battery
- Loose connections
- Power supply instability

**Troubleshooting**:
1. Replace batteries
2. Check connections
3. Verify stable power
4. May require service

### 5. Keyboard Errors

#### 5.1 Key Not Responding

**Possible Causes**:
- Dirt under key
- Worn contact
- Broken switch

**Troubleshooting**:
1. Clean keyboard with compressed air
2. Test key repeatedly
3. Try alternate key if available
4. May require service

#### 5.2 Sticky Key

**Possible Causes**:
- Spilled liquid
- Dirt accumulation
- Worn mechanism

**Troubleshooting**:
1. Clean around key
2. Use compressed air
3. May require disassembly and cleaning

#### 5.3 Wrong Key Registering

**Possible Causes**:
- Keyboard matrix short
- Multiple keys stuck
- Scanner malfunction

**Troubleshooting**:
1. Check for physically stuck keys
2. Clean keyboard thoroughly
3. May require internal repair

### 6. Calculation Errors

#### 6.1 Incorrect Results

**Possible Causes**:
- User error in operation sequence
- Incorrect mode (degrees vs radians)
- Accumulated rounding errors
- Hardware malfunction

**Troubleshooting**:
1. Verify operation sequence
2. Check angle mode for trig functions
3. Clear memory and retry
4. Test with known calculations
5. Compare with manual calculation or second calculator

**Example - Common User Error**:
```
Incorrect: [5] [+] [3] [×] [2]  ; Results in 16, not 11
Correct: [5] [ВП] [3] [ВП] [2] [×] [+]  ; Results in 11
```

#### 6.2 Precision Issues

**Cause**: Accumulated rounding errors in long calculations

**Example**:
```
Many operations: ((((a + b) × c) ÷ d) - e) ...
```

**Mitigation**:
1. Store intermediate results
2. Round appropriately
3. Minimize number of operations
4. Use algebraic simplification

#### 6.3 Angle Mode Confusion

**Issue**: MK-56 uses radians, not degrees

**Common Error**:
```
[30] [Г] [sin]  ; Gives sin(30 radians), not sin(30°)
```

**Correct Approach**:
```
; Convert 30° to radians: 30 × π/180 ≈ 0.5236
[0][•][5][2][3][6] [Г] [sin]  ; Gives sin(30°) ≈ 0.5
```

**Conversion Formula**:
- Degrees to radians: degrees × π/180
- Radians to degrees: radians × 180/π

### 7. Programming Errors

#### 7.1 Infinite Loop

**Cause**: Loop condition never becomes false

**Example**:
```
00: [1] [0]        ; Counter = 10
01: [x→П] [0]
02: ...            ; Loop body
10: [П→x] [0]
11: [1]
12: [+]            ; ERROR: Should be [-] to decrement
13: [x→П] [0]
14: [x≥0] [0] [2]  ; Always true, infinite loop
```

**Symptoms**: Program never stops

**Recovery**:
1. Power off calculator
2. Correct program logic
3. Re-enter program

**Prevention**: Carefully verify loop conditions

#### 7.2 Wrong Jump Address

**Cause**: Incorrect address in jump command

**Example**:
```
00: [БП] [9] [9]   ; Jump to address 99
...
; But program only goes to address 50
```

**Symptoms**: 
- Program jumps to wrong location
- Executes unintended code
- Unexpected results

**Recovery**:
1. Review program listing
2. Verify all jump addresses
3. Correct and re-enter

**Prevention**: Document program structure and addresses

#### 7.3 Stack Overflow

**Cause**: Too many nested subroutine calls

**Symptoms**: 
- Return addresses lost
- Program doesn't return correctly
- Unexpected behavior

**Recovery**:
1. Reduce nesting depth
2. Restructure program
3. Use iterative instead of recursive approach

**Prevention**: Limit subroutine nesting (typically 2-3 levels max)

#### 7.4 Register Conflicts

**Cause**: Using same register for different purposes

**Example**:
```
; Main program uses RG0 for counter
; Subroutine also uses RG0, overwriting counter
```

**Symptoms**: Unexpected values, incorrect results

**Recovery**:
1. Document register usage
2. Assign registers to specific purposes
3. Save/restore registers in subroutines if needed

**Prevention**: Plan register allocation before programming

## Error Recovery Procedures

### General Error Recovery

1. **Immediate Action**:
   - Press [СХ] to clear error
   - Note what caused error
   - Verify calculator still responsive

2. **If Error Persists**:
   - Power off calculator
   - Wait 10 seconds
   - Power on
   - Test basic functions

3. **If Still Not Working**:
   - Remove and reinstall batteries
   - Clear all memory
   - Perform basic tests
   - Consult [Technical Maintenance](13-maintenance.md)

### Memory Clear Procedure

**Full Memory Clear**:
1. Clear stack: [СХ] [ВП] [СХ] [ВП] [СХ] [ВП] [СХ]
2. Clear registers: For each register 0-13:
   - [СХ] [x→П] [n]
3. Clear program: Enter programming mode, overwrite with [С/П] commands

### Factory Reset (if available)

Some models may have a reset procedure:
1. Power off
2. Hold specific key combination
3. Power on
4. Release keys
5. Verify reset complete

**Note**: Consult specific model documentation for reset procedure.

## Troubleshooting Flowchart

```
Calculator Issue
       |
       v
   Display OK?
   /         \
  No         Yes
  |           |
  v           v
Power?    Keys Work?
  |       /        \
Battery  No        Yes
Replace  |          |
         v          v
      Clean     Calc Error?
      Keys      /         \
               No         Yes
               |           |
               v           v
           Working    Check Input
                      Clear Memory
                      Retry
```

## Common User Mistakes

### 1. Forgetting [ВП] Key

**Mistake**: [5] [+] [3] instead of [5] [ВП] [3] [+]

**Result**: Incorrect operation sequence

**Solution**: Always use [ВП] to separate operands

### 2. Incorrect Order of Operations

**Mistake**: Entering formula left-to-right without considering precedence

**Solution**: Use RPN (Reverse Polish Notation) correctly

### 3. Angle Mode Confusion

**Mistake**: Using degrees instead of radians

**Solution**: Convert degrees to radians before trig functions

### 4. Not Clearing Memory

**Mistake**: Assuming registers are zero

**Solution**: Always clear or initialize registers before use

### 5. Overflow in Intermediate Steps

**Mistake**: Not monitoring intermediate result magnitude

**Solution**: Break calculations into manageable steps

## Related Documents

- [Technical Maintenance](13-maintenance.md) - Repair and service
- [Testing Procedures](14-testing.md) - Systematic testing
- [Automatic Mode Operation](06-automatic-mode.md) - Proper operation
- [Programming Mode](07-programming-mode.md) - Programming guidance
- [Functional Capabilities](03-functional-capabilities.md) - Function limitations
