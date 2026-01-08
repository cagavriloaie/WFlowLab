# Calculation Process - Metrological Verification of Water Meters

## 1. Introduction

This document describes the calculation process used for metrological verification of water meters. Verification consists of measuring the accuracy of the meter by comparing the volume indicated by the meter with a reference volume obtained through calibrated methods.

## 2. Initial Configuration

Before starting measurements, configure:

- **Meter type**: DN (nominal diameter), metrological class, characteristic flow rates (Q1, Q2, Q3)
- **Measurement method**: Volumetric or Gravimetric
- **Correction method** (for gravimetric): Classic, INM or ELCOST
- **Environmental conditions**: Temperature (T), Pressure (P), Humidity

## 3. Measurement Process

For each measurement (up to 20 measurements at different flow rates):

### 3.1. Measurement Steps

1. Record the meter's **initial index**: `Index_Start` [L]
2. Water flows through the meter and is collected:
   - **Volumetric method**: in a calibrated standard tank
   - **Gravimetric method**: in a tank on a precision scale
3. Measure method-specific parameters (see section 4)
4. Record the meter's **final index**: `Index_Stop` [L]
5. Calculate reference volume and error

### 3.2. Recorded Data

- Index Start and Index Stop [L]
- **For volumetric method**: Standard volume [L]
- **For gravimetric method**:
  - Collected water mass [kg]
  - Water temperature [°C]

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
V_reference = K(T) × m
```

Where:
- `m` = measured water mass [kg]
- `T` = water temperature [°C]
- `K(T)` = conversion factor [L/kg] obtained from standard density tables

**Factor K(T)** is a temperature function that compensates for water density variation with temperature and includes the Archimedes force effect. It is obtained by interpolation from standard metrological tables (e.g., OIML R49 tables).

**Mathematical relationship**:
```
K(T) ≈ 1 / ρ(T)  [L/kg]
```
Factor K is approximately inversely proportional to water density at temperature T and includes the Archimedes force correction.

**Principle**:
- At 4°C: water density = 1.000 kg/L → K(4°C) ≈ 1.000 L/kg
- At 20°C: water density ≈ 0.998 kg/L → K(20°C) ≈ 1.002 L/kg
- At higher temperatures, density decreases, so K increases

### 4.3. Gravimetric Method - INM Variant (Bucharest Metrology Institute)

This method applies an additional correction based on actual water density.

```
V_corrected = (1000 × 1.00105) / ρ_real(T)
```

Where actual density is calculated:

```
ρ_real(T) = ρ_ideal(T) × (ρ_real20 / ρ_ideal20)
```

Parameters:
- `ρ_ideal(T)` = theoretical density of pure water at temperature T [kg/m³] - from tables
- `ρ_real20` = actual water density measured at 20°C [kg/m³]
- `ρ_ideal20` = theoretical density of pure water at 20°C = 998.203 kg/m³
- `1.00105` = volumetric correction factor for water (compensates for thermal expansion of measurement vessel and Archimedes force effect)

**Final volume**:
```
V_reference = [(1000 × 1.00105) / ρ_real(T)] × m [L]
```

**Principle**: The INM method accounts for:
1. Differences between actual available water density (which may contain impurities) and theoretical density
2. Volumetric correction through factor 1.00105 which includes:
   - Thermal expansion of measurement vessel
   - Archimedes force effect on water

### 4.4. Gravimetric Method - ELCOST Variant

This method uses an experimentally determined calibration factor.

```
V_reference = K(T) × calibration_factor × m
```

Where:
```
calibration_factor = ρ_ideal20 / ρ_real20
```

Parameters:
- `K(T)` = temperature-dependent conversion factor [L/kg]
- `calibration_factor` = ratio between theoretical and actual density at 20°C
- `m` = water mass [kg]
- `ρ_ideal20` = 998.203 kg/m³ (theoretical density at 20°C)
- `ρ_real20` = actual measured density at 20°C [kg/m³]

**Principle**: Combines temperature correction K(T) with calibration based on actual water density used in the laboratory.

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
- Temperature = 20°C → K(20°C) ≈ 1.002 L/kg
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
│ - Volumetric: V = V_standard          │
│ - Classic: V = K(T) × m               │
│ - INM: V = [1000×1.00105/ρ(T)] × m    │
│ - ELCOST: V = K(T) × calibr × m       │
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
    ↓
┌─────────────┐      ┌─────────────┐
│    PASS     │      │    FAIL     │
└─────────────┘      └─────────────┘
```

## 8. Important Notes

1. **Measurement precision**:
   - Temperature must be measured with ±0.1°C precision
   - Mass must be measured with precision scale (±0.01 kg or better)
   - Indexes must be read with maximum meter precision

2. **Number of measurements**: Minimum 3 measurements at each characteristic flow rate (Q1, Q2, Q3)

3. **Stability conditions**:
   - Flow rate must be stable during measurement
   - Water temperature must be uniform
   - Air bubbles must be eliminated from circuit

4. **Measurement validation**: Each measurement can be marked as valid/invalid via checkbox

5. **Reporting**: Results are recorded in metrological verification bulletin according to current regulations

---

**Document generated for**: Water Meter Verification Application
**Date**: 31.12.2025
**Version**: 1.8
