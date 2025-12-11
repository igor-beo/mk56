# 14. Testing Procedures

## Appendix: Test for Functional Control of the Microcalculator

### Overview

This document provides systematic testing procedures to verify the proper functioning of the MK-56 "Elektronika" microcalculator.

## Test Categories

### 1. Power-On Test

**Purpose**: Verify basic power and initialization

**Procedure**:
1. Install fresh batteries or connect power
2. Turn on calculator
3. Observe display initialization
4. Wait for warm-up period (up to 30 seconds)

**Expected Result**:
- Display shows `0.` or ready state
- All segments visible and clear
- No flickering or dimming

**Pass/Fail Criteria**:
- ✓ Pass: Display clear and stable
- ✗ Fail: No display, dim display, or erratic behavior

### 2. Display Test

**Purpose**: Verify all display segments function correctly

**Procedure**:
1. Enter: [8] [8] [8] [8] [8] [8] [8] [8]
2. Observe all digits showing "8"
3. Press [СХ] to clear
4. Enter: [1] [2] [3] [4] [5] [6] [7] [8]
5. Verify each digit displays correctly

**Expected Result**:
- All segments illuminate for "8"
- Each digit displays correctly
- Decimal points visible when tested

**Pass/Fail Criteria**:
- ✓ Pass: All segments work, digits clear
- ✗ Fail: Missing segments, dim digits, or incorrect display

### 3. Keyboard Test

**Purpose**: Verify all keys respond correctly

#### 3.1 Digit Keys Test

**Procedure**:
1. Press [СХ] to clear
2. Press each digit key [0] through [9]
3. Verify each appears on display
4. Press [СХ] between tests

**Expected Result**: Each digit displays correctly

#### 3.2 Operation Keys Test

**Procedure**:
Test each operation with simple calculation:
- Addition: [2] [ВП] [3] [+] = `5.`
- Subtraction: [5] [ВП] [2] [−] = `3.`
- Multiplication: [4] [ВП] [3] [×] = `12.`
- Division: [8] [ВП] [2] [÷] = `4.`

**Expected Result**: Correct results for all operations

#### 3.3 Function Keys Test

**Procedure**:
Test each function:
- Square: [5] [x²] = `25.`
- Square root: [9] [√x] = `3.`
- Reciprocal: [4] [1/x] = `0.25`

**Expected Result**: Correct results for all functions

### 4. Arithmetic Operations Test

**Purpose**: Verify calculation accuracy

#### Test 4.1: Basic Arithmetic

| Operation | Input Sequence | Expected Result |
|-----------|----------------|-----------------|
| 15 + 27 | [1][5][ВП][2][7][+] | 42. |
| 100 - 37 | [1][0][0][ВП][3][7][−] | 63. |
| 12 × 8 | [1][2][ВП][8][×] | 96. |
| 144 ÷ 12 | [1][4][4][ВП][1][2][÷] | 12. |

#### Test 4.2: Complex Arithmetic

| Operation | Input Sequence | Expected Result |
|-----------|----------------|-----------------|
| (5 + 3) × 2 | [5][ВП][3][+][2][×] | 16. |
| 100 ÷ (2 + 3) | [2][ВП][3][+][1][0][0][↔][÷] | 20. |

**Pass/Fail Criteria**:
- ✓ Pass: All results correct within precision
- ✗ Fail: Any incorrect result

### 5. Mathematical Functions Test

**Purpose**: Verify advanced function accuracy

#### Test 5.1: Power and Root Functions

| Function | Input | Expected Result | Tolerance |
|----------|-------|-----------------|-----------|
| x² | [7][x²] | 49. | Exact |
| √x | [16][√x] | 4. | Exact |
| 1/x | [8][1/x] | 0.125 | ±1×10⁻⁷ |

#### Test 5.2: Exponential and Logarithmic

| Function | Input | Expected Result | Tolerance |
|----------|-------|-----------------|-----------|
| 10ˣ | [2][Г][10ˣ] | 100. | ±4×10⁻⁷ |
| eˣ | [1][Г][eˣ] | 2.7182818 | ±5×10⁻⁸ |
| lg x | [100][Г][lg] | 2. | ±3×10⁻⁷ |
| ln x | [2.7182818][Г][ln] | 1. | ±3×10⁻⁷ |

#### Test 5.3: Trigonometric Functions

**Note**: Angles in radians

| Function | Input (radians) | Expected Result | Tolerance |
|----------|-----------------|-----------------|-----------|
| sin x | [0][Г][sin] | 0. | ±3×10⁻⁷ |
| sin x | [1.5707963][Г][sin] | 1. (π/2) | ±3×10⁻⁷ |
| cos x | [0][Г][cos] | 1. | ±3×10⁻⁷ |
| cos x | [3.1415927][Г][cos] | -1. (π) | ±3×10⁻⁷ |

**Pass/Fail Criteria**:
- ✓ Pass: Results within specified tolerance
- ✗ Fail: Results exceed tolerance

### 6. Memory Test

**Purpose**: Verify memory storage and recall

#### Test 6.1: Register Storage

**Procedure**:
1. [5][x→П][0] - Store 5 in RG0
2. [СХ] - Clear display
3. [П→x][0] - Recall RG0
4. Verify display shows `5.`
5. Repeat for registers 1-9

**Expected Result**: All registers store and recall correctly

#### Test 6.2: Memory Arithmetic

**Procedure**:
1. [10][x→П][5] - Store 10 in RG5
2. [3][П][+][5] - Add 3 to RG5
3. [П→x][5] - Recall RG5
4. Verify display shows `13.`

**Expected Result**: `13.`

### 7. Stack Operations Test

**Purpose**: Verify stack functionality

**Procedure**:
1. [СХ][ВП][СХ][ВП] - Clear stack
2. [1][ВП] - Push 1
3. [2][ВП] - Push 2
4. [3][ВП] - Push 3
5. [4] - Enter 4
6. [+] - Should add 4 + 3 = 7
7. [+] - Should add 7 + 2 = 9
8. [+] - Should add 9 + 1 = 10

**Expected Result**: Final result `10.`

**Pass/Fail Criteria**:
- ✓ Pass: Correct stack behavior
- ✗ Fail: Incorrect results

### 8. Programming Mode Test

**Purpose**: Verify programming functionality

#### Test 8.1: Program Entry

**Procedure**:
1. [ПРГ] - Enter programming mode
2. Display should show `00`
3. [x²] - Enter command
4. Display advances to `01`
5. [5] - Enter constant
6. Display advances to `02`
7. [+] - Enter operation
8. Display advances to `03`
9. [С/П] - Enter stop
10. [ПРГ] - Exit programming mode

**Expected Result**: Program stored correctly

#### Test 8.2: Program Execution

**Procedure**:
1. [3] - Enter test value
2. [В/О] - Run program from address 00
3. Wait for stop
4. Verify result: 3² + 5 = 14

**Expected Result**: Display shows `14.`

#### Test 8.3: Jump Commands

**Procedure**:
Create simple loop program and verify execution

**Expected Result**: Loop executes correctly

### 9. Error Handling Test

**Purpose**: Verify error detection

#### Test 9.1: Division by Zero

**Procedure**:
1. [5][ВП][0][÷]
2. Observe error indication

**Expected Result**: Error displayed

#### Test 9.2: Invalid Domain

**Procedure**:
1. [1][/~/][√x] - Square root of -1
2. Observe error indication

**Expected Result**: Error displayed

#### Test 9.3: Overflow

**Procedure**:
1. [9][•][9][9][9][9][9][9][9][ВП][1][0][0][Г][10ˣ][×]
2. Observe error indication

**Expected Result**: Error displayed (overflow)

### 10. Comprehensive Function Test

**Purpose**: Complete system verification

This test exercises all major functions in sequence:

```
Test Sequence:
1. Power on
2. Display test (all 8s)
3. Clear: [СХ]
4. Arithmetic: 15 + 27 = 42
5. Function: √(42) ≈ 6.4807407
6. Memory: Store in RG0
7. Clear: [СХ]
8. Recall from RG0
9. Trigonometric: sin(result) 
10. Store result
11. Programming: Create simple program
12. Execute program
13. Verify final result
```

**Pass/Fail Criteria**:
- ✓ Pass: All steps complete successfully
- ✗ Fail: Any step fails

## Test Results Documentation

### Test Report Template

```
MK-56 Calculator Test Report
Date: _______________
Tester: _____________
Serial Number (if available): _______________

Test Results:
[ ] Power-On Test: Pass / Fail
[ ] Display Test: Pass / Fail
[ ] Keyboard Test: Pass / Fail
[ ] Arithmetic Test: Pass / Fail
[ ] Function Test: Pass / Fail
[ ] Memory Test: Pass / Fail
[ ] Stack Test: Pass / Fail
[ ] Programming Test: Pass / Fail
[ ] Error Handling Test: Pass / Fail
[ ] Comprehensive Test: Pass / Fail

Overall Result: Pass / Fail

Notes:
_________________________________
_________________________________
_________________________________

Recommendations:
_________________________________
_________________________________
```

## Acceptance Criteria

### For New/Refurbished Units

**Minimum Requirements**:
- All tests must pass
- No missing display segments
- All keys responsive
- Calculation accuracy within specifications
- Memory functions correctly
- Programming mode operational

### For Used Units

**Acceptable**:
- Minor cosmetic wear
- All functional tests pass
- Accuracy within specifications

**Unacceptable**:
- Any failed functional test
- Missing display segments
- Non-responsive keys
- Calculation errors
- Memory failures

## Related Documents

- [Functional Capabilities](03-functional-capabilities.md) - Function specifications
- [Technical Specifications](10-specifications.md) - Performance specifications
- [Technical Maintenance](13-maintenance.md) - Troubleshooting
- [Automatic Mode Operation](06-automatic-mode.md) - Operation instructions
