# Calculation Process - Metrological Verification of Water Meters

## 1. Introduction

This document describes the calculation process used for metrological verification of water meters. Verification consists of measuring the accuracy of the meter by comparing the volume indicated by the meter with a reference volume obtained through calibrated methods.

## 2. Initial Configuration

Before starting measurements, configure:

- **Meter type**: DN (nominal diameter), metrological class, characteristic flow rates (Q1, Q2, Q3)
- **Measurement method**: Volumetric or Gravimetric
- **Correction method** (for gravimetric): Classic, INM or ELCOST
- **Environmental conditions**: Temperature (t), Pressure (P), Humidity

## 3. Measurement Process

For each measurement (up to 20 measurements at different flow rates):

### 3.1. Measurement Steps

1. Record the meter's **initial index**: `Index_Start` [L]
2. Water flows through the meter and is collected:
   - **Volumetric method**: uses an electromagnetic flowmeter as a secondary standard for measuring the conventionally true volume
   - **Gravimetric method**: uses a precision balance to measure water mass which is then converted to volume
3. Measure method-specific parameters (see section 4)
4. Record the meter's **final index**: `Index_Stop` [L]
5. Calculate reference volume and error

### 3.2. Recorded Data

- Index Start and Index Stop [L]
- **For volumetric method**: Standard volume [L]
- **For gravimetric method**: Collected water mass [kg], Water temperature [°C]

## 4. Reference Volume Calculation

The reference volume represents the actual volume of water that passed through the meter, calculated independently of the meter's indication.

### 4.1. Volumetric Method

Water flows through the meter under test and is collected in a calibrated standard tank. **The conventionally true value is the one read on the flow meter used as a secondary standard** (not the tank volume).

```
V_reference = V_standard_flowmeter [L]
```

**Principle**: The secondary standard flow meter measures the actual volume of water that passed through the system, this value being considered the metrological reference for calculating the error of the tested meter.

### 4.2. Gravimetric Method - CLASSIC Variant

Water is weighed, and mass is converted to volume using a temperature-dependent correction factor.

```
V_reference = K(t) × m
```

Where:
- `m` = measured water mass [kg]
- `t` = water temperature [°C]
- `K(t)` = conversion factor [L/kg]

**Factor K(t)** is a temperature function that compensates for water density variation with temperature and includes the Archimedes force effect. It is obtained by interpolation from standard metrological tables (e.g., OIML R49 tables).

### 4.3. The beneficiary can agree with BRML/INM to obtain the installation calibration certificate using other methods provided by this program.

## 5. Error Calculation

After determining the reference volume, calculate the meter error.

### 5.1. General Formula

```
Error = [(Index_Stop - Index_Start) - V_reference] / V_reference × 100 [%]
```

Or equivalently:

```
Error = [(V_indicated - V_reference) / V_reference] × 100 [%]
```

Where:
- `V_indicated` = Index_Stop - Index_Start = volume displayed by meter [L]
- `V_reference` = actual volume calculated by chosen method [L]

### 5.2. Interpretation

- **Positive error** (+): Meter indicates more than actual volume → meter "runs fast"
- **Negative error** (−): Meter indicates less than actual volume → meter "runs slow"
- **Error = 0%**: Meter is perfectly calibrated (theoretical situation)

### 5.3. Examples

**Example 1**: Volumetric method
- Index_Start = 1000.00 L
- Index_Stop = 1050.00 L
- V_standard = 50.00 L
- V_indicated = 1050.00 - 1000.00 = 50.00 L
- Error = (50.00 - 50.00) / 50.00 × 100 = **0.00%** ✓

**Example 2**: Classic gravimetric method
- Index_Start = 2000.00 L
- Index_Stop = 2100.50 L
- Mass = 100.00 kg
- Temperature = 20°C → K(t=20°C) ≈ 1.002 L/kg
- V_reference = 1.002 × 100.00 = 100.20 L
- V_indicated = 100.50 L
- Error = (100.50 - 100.20) / 100.20 × 100 = **+0.30%**

## 6. Compliance Verification

### 6.1. Maximum Permissible Errors

Each meter class has maximum permissible errors (MPE) defined according to metrological standards (OIML R49, MID):

| Flow zone | Flow range | Maximum Permissible Error |
|-----------|------------|---------------------------|
| Lower zone | Q1 ≤ Q < Q2 | ±5% (class B) or ±2% (class C) |
| Upper zone | Q2 ≤ Q ≤ Q4 | ±2% (class B) or ±1% (class C) |

### 6.2. Acceptance Criterion

For each measurement:

```
|Calculated_Error| ≤ MPE_corresponding_to_flow_rate
```

**Overall result**:
- **PASS**: All measurements meet acceptance criterion
- **FAIL**: At least one measurement exceeds maximum permissible error

### 6.3. Verification Example

For a class B meter, DN15:
- Q1 = 15 L/h, Q2 = 30 L/h, Q3 = 300 L/h

Measurements performed:

| Flow rate | Calculated error | MPE | Status |
|-----------|------------------|-----|--------|
| 20 L/h (Q1) | +4.2% | ±5% | ✓ PASS |
| 25 L/h (Q1-Q2) | +3.8% | ±5% | ✓ PASS |
| 50 L/h (Q2) | +1.5% | ±2% | ✓ PASS |
| 150 L/h (Q2-Q3) | +0.8% | ±2% | ✓ PASS |
| 300 L/h (Q3) | -1.2% | ±2% | ✓ PASS |

**Final verdict**: **PASS** - all measurements are within limits

## 7. Complete Calculation Flow

```
INPUT DATA
    ↓
┌───────────────────────────────────────┐
│ Index_Start, Index_Stop               │
│ + Method-specific parameters          │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ REFERENCE VOLUME CALCULATION          │
│ - Volumetric: Standard flowmeter      │
│ - Classic: Mass corrected by temp.    │
│ - INM: Mass with density correction   │
│ - ELCOST: Mass with calibration       │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ INDICATED VOLUME CALCULATION          │
│ V_indicated = Index_Stop - Index_Start│
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ ERROR CALCULATION                     │
│ E = (V_ind - V_ref) / V_ref × 100%    │
└───────────────────────────────────────┘
    ↓
┌───────────────────────────────────────┐
│ LIMIT VERIFICATION                    │
│ |E| ≤ MPE ?                           │
└───────────────────────────────────────┘
      Yes ↓              ↓ No
┌─────────────┐      ┌─────────────┐
│    PASS     │      │    FAIL     │
└─────────────┘      └─────────────┘
```

---

**Document generated for**: Water Meter Verification Application
**Date**: 31.12.2025
**Version**: 1.8
