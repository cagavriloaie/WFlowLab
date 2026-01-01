# WStreamLab

**Water Meter Metrological Verification Software**

WStreamLab is a professional desktop application for metrological verification and calibration of water meters. It provides comprehensive testing capabilities using both volumetric and gravimetric measurement methods, compliant with international standards (OIML R49, MID).

## Overview

WStreamLab (formerly WFlowLab) is designed for calibration laboratories and metrology institutes to perform accurate verification of water meters. The application supports multiple measurement methodologies, automated calculations, and generates compliance reports according to metrological regulations.

**Version:** 1.8
**Developer:** ELCOST
**Website:** http://www.elcost.com/

## Key Features

- **Multiple Measurement Methods**
  - Volumetric method (calibrated standard tank)
  - Gravimetric method with three correction variants:
    - Classic (temperature-based K factor)
    - INM (Bucharest Metrology Institute method)
    - ELCOST/CULI (calibration-based)

- **Comprehensive Testing**
  - Up to 20 measurements per verification session
  - Support for multiple flow rates (Q1, Q2, Q3, Q4)
  - Automatic error calculation and compliance verification
  - Real-time temperature and density corrections

- **Meter Configuration**
  - Support for various DN (nominal diameter) sizes
  - Metrological class configuration (Class A, B, C)
  - Characteristic flow rate definitions
  - Custom meter profiles

- **Data Management**
  - Measurement validation (mark individual tests as valid/invalid)
  - Environmental condition tracking (temperature, pressure, humidity)
  - Export capabilities for reports and data analysis
  - Configuration templates for different locations

- **User Interface**
  - Intuitive Qt-based graphical interface
  - Multi-language support (Romanian, English)
  - Real-time calculation display
  - Tabular data entry and visualization

## Technical Specifications

### Measurement Process

1. **Initial Setup:** Configure meter type, measurement method, and environmental conditions
2. **Data Collection:** Record index start/stop values and method-specific parameters
3. **Calculation:** Automatic computation of reference volume and error percentage
4. **Verification:** Compliance check against maximum permissible errors (MPE)
5. **Reporting:** Generate verification bulletin with results

### Error Calculation

```
Error (%) = [(V_indicated - V_reference) / V_reference] × 100
```

Where:
- `V_indicated` = Volume shown by meter (Index_Stop - Index_Start)
- `V_reference` = Actual volume calculated by chosen method

### Compliance Standards

- **OIML R49:** International Recommendation for Water Meters
- **MID (2014/32/EU):** Measuring Instruments Directive
- Maximum Permissible Errors:
  - Lower zone (Q1 to Q2): ±5% (Class B) or ±2% (Class C)
  - Upper zone (Q2 to Q4): ±2% (Class B) or ±1% (Class C)

## Building from Source

### Requirements

- **Qt Framework:** 6.7.1 or later
- **Compiler:** MinGW 11.2.0 (64-bit) or MSVC 2019+
- **Build System:** Qt Creator or CMake
- **Platform:** Windows (primary), Linux (experimental)

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/cagavriloaie/WFlowLab.git
   cd WFlowLab
   ```

2. **Open in Qt Creator:**
   - Open the `.pro` file in Qt Creator
   - Configure the kit (Qt 6.7.1 + MinGW or MSVC)
   - Build the project

3. **Alternative - Command line build:**
   ```bash
   qmake
   make
   ```

4. **Generate installer:**
   - Build the Release version
   - Run `deploy.bat` to prepare deployment files
   - Use Inno Setup with `WStreamLab.iss` to create installer

### Build Scripts

- `deploy.bat` - Prepares application for deployment (copies Qt dependencies)
- `startTranslations.bat` - Updates translation files (.ts files)

## Project Structure

```
WStreamLab/
├── meter/              # Main application source code
├── configs/            # Configuration files for different locations
├── manuals/            # User manuals (PDF)
├── templates/          # Standard templates and configurations
├── code-formatting/    # Code formatting tools (Artistic Style)
├── docs/               # Technical documentation
├── build/              # Build artifacts and resources
├── output/             # Installer output directory
├── Debug/              # Debug build output
├── Release/            # Release build output
└── doxygen/            # Code documentation generation
```

## Documentation

- **[Calculation Process (Romanian)](docs/PROCES_CALCUL_VERIFICARE_CONTOARE.md)** - Detailed explanation of calculation methods
- **[Verification Method (English)](docs/VERIFICATION_METHOD_PROCESS.md)** - Metrological verification process
- **[User Manuals](manuals/)** - Complete application user guides (PDF)
- **[Translation Preview](docs/PREVIEW_TRADUCERI_MODIFICARI.txt)** - UI translation notes

## Configuration

Configuration files are located in `configs/` directory:
- `CUP_Dunarea_Braila/` - Configuration for Dunarea Braila facility
- `CUP_Focsani/` - Configuration for Focsani facility
- `CUP_General/` - General default configuration
- `watermeters.conf` - Main water meter configuration file

## Windows Registry Settings

WStreamLab stores application settings in the Windows Registry under:
```
HKEY_CURRENT_USER\SOFTWARE\WStreamLab
```

### Registry Groups and Keys

#### LabConditions
Laboratory environmental conditions for metrological calculations:

| Key           | Type   | Default | Description                   |
|---------------|--------|---------|-------------------------------|
| `temperature` | String | "18"    | Ambient temperature (°C)      |
| `humidity`    | String | "51"    | Relative air humidity (%)     |
| `pressure`    | String | "1026"  | Atmospheric pressure (mbar)   |

#### BenchConfiguration
Test bench configuration:

| Key                 | Type    | Default | Description                              |
|---------------------|---------|---------|------------------------------------------|
| `numberWaterMeters` | Integer | 20      | Number of water meters to test (max 20)  |
| `waterMeterType`    | Integer | 0       | Selected water meter type index          |

#### Report
Verification report settings:

| Key                     | Type    | Default                      | Description                           |
|-------------------------|---------|------------------------------|---------------------------------------|
| `authorizationNumber`   | String  | "1050/2024"                  | Authorization number                  |
| `registrationNumber`    | Integer | 1                            | Registration number (auto-increments) |
| `beneficiary`           | String  | "Termo Util"                 | Beneficiary name                      |
| `ltCode`                | String  | "1.06.28.1.1"                | LT code identifier                    |
| `standard`              | String  | "NML"                        | Normative standard reference          |
| `validityYears`         | Integer | 6                            | Validity period index (years)         |
| `cost`                  | String  | "100"                        | Verification cost                     |
| `metrologistName`       | String  | "Adrian Pintilie"            | Metrologist name                      |
| `verificationLocation`  | String  | "Str. Morilor nr 8, Pascani" | Verification location                 |

#### RS_485_422
Serial communication settings (when RS-485/422 support is enabled):

| Key                                       | Type    | Default (Port 1) | Default (Port 2) | Description                     |
|-------------------------------------------|---------|------------------|------------------|---------------------------------|
| `serialPort_1` / `serialPort_2`           | Integer | 0                | 1                | Serial port selection index     |
| `baudRate_1` / `baudRate_2`               | Integer | 3                | 3                | Baud rate index (9600)          |
| `dataBits_1` / `dataBits_2`               | Integer | 3                | 3                | Data bits index (8 bits)        |
| `parity_1` / `parity_2`                   | Integer | 1                | 1                | Parity index (Even)             |
| `stopBits_1` / `stopBits_2`               | Integer | 0                | 0                | Stop bits index (1 bit)         |
| `timeout_1` / `timeout_2`                 | Integer | 1000             | 1000             | Communication timeout (ms)      |
| `numberOfRetries_1` / `numberOfRetries_2` | Integer | 4                | 4                | Number of retries (5 retries)   |

**Note:** RS-485/422 settings only apply when built without the `BUILD_WITHOUT_RS_485_422_MODBUS` flag.

### Registry Cleanup

To remove old registry keys from previous versions, run the provided PowerShell script:
```powershell
.\cleanup_old_registry_keys.ps1
```

This script safely removes deprecated registry keys while preserving user data through application defaults.

## License

Copyright (c) 2026 ELCOST
All rights reserved.

This software is proprietary and confidential. Unauthorized copying, distribution, or use is strictly prohibited.

## Contact

**ELCOST**
Website: http://www.elcost.com/

For technical support or inquiries, please visit the website or contact ELCOST directly.

## Development

### Code Formatting

The project uses Artistic Style for consistent code formatting:
```bash
# Format source code (see code-formatting/ directory)
astyle --style=allman --indent=spaces=4 *.cpp *.h
```

Configuration: `.clang-format`

### Version History

- **v1.8** (2025) - Current version with improved UI and calculation methods
- **v1.2** - Enhanced metrological verification features
- **v1.1** - Initial stable release

---

**Note:** This is a professional metrological instrument. Ensure proper calibration and training before use in official verification procedures.
