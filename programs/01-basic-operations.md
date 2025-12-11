# Basic Operations Programs

Programs for fundamental numerical operations.

## Program 3.1: Integer Part Extraction

**Purpose**: Extract integer part of x where 1 < x < 10⁸

**Input**: x = PX (M = 7, 8, 9, A, B, C or D)

**Program**:
```
ПM КИПM ИПM С/П
```

**Test**: x = 123.4567 → Result: 123

---

## Program 3.2: Fractional Part Extraction

**Purpose**: Extract fractional part of x where 0 < x < 10⁸

**Input**: x = PX

**Program**:
```
↑ 1 + ПM КИПM XY ИПM − С/П
```

**Test**: x = 123.4567 → Result: 0.4567

---

## Program 3.3: Number Truncation

**Purpose**: Truncate number x (0 < x < 10⁸) with precision ε = 1·10⁻ⁿ

**Input**: ε = PД, x = PX

**Program**:
```
ИПД + ПС КИПС ИПС ИПД × С/П
```

**Test**: ε = 1·10⁻² and x = 123.4567 → Result: 123.45

---

## Program 3.4: Rounding with Sign Correction

**Purpose**: Round number x with precision ε = 1·10⁻ⁿ, correcting last digit

**Input**: ε = 1·10⁻ⁿ = PД, x = PX

**Program**:
```
↑       Fx<0  04    /−/   +     П9  FBx  ИПД  +    ПС
КИПС    XY    ИПС   −     F1/x  2   −    Fx<0 23   ИПС
1       +     ПС    ИПД   ×     ИП9 ×    С/П
```

**Test**: x = ±12.345678 and ε = 1·10⁻² → Result: ±12.35
        x = ±12.344999 → Result: ±12.34

---

## Program 3.5: Absolute Value

**Purpose**: Extract absolute value |x|

**Input**: x = PX

**Program**:
```
... ... Fx<0 N /−/ ... ... ...
```

Where N = address after /−/ operator.

---

## Program 3.6: Angle Conversion (Radians to Degrees/Minutes/Seconds)

**Purpose**: Convert angle φ in radians to degrees φ°, minutes φ', seconds φ"

**Input**: φ = PX

**Program**:
```
П8  С/П  П9  С/П  ↑   6   0   +   ИП9  +
6   0    +   ИП8  +   П0  1   8   0    +
Fπ  ×    С/П БП   00
```

**Test**: φ = 2 rad → φ° = 114, φ' = 35, φ" = 29.616"
        (i.e., φ = 114° 35' 29.616")

---

## Program 3.7: Angle Conversion (Degrees/Minutes/Seconds to Radians)

**Purpose**: Convert angle in degrees/minutes/seconds to radians

**Input**: φ°, φ', φ" in register X

**Program**:
```
П8  С/П  П9  С/П  ↑   6   0   +   ИП9  +
6   0    +   ИП8  +   П0  1   8   0    +
Fπ  ×    С/П БП   00
```

**Test**: φ = 114° 35' 29.616" → φ_rad = 2

---

## Usage Notes

1. All programs use B3-34 notation
2. For MK-56, translate:
   - `ИП` → `П→x`
   - `П` → `x→П`
   - Stack operations differ in algebraic mode
3. Test with control examples before use
