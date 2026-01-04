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
   - Run `BuildInstaller.bat` to create both .exe and .msi installers

### Build Scripts

- **`BuildInstaller.bat`** - Automated installer builder
  - Compiles Inno Setup script to create .exe installer
  - Generates .msi installer using MSI Wrapper
  - Output files in `output/` directory:
    - `WStreamLab-1.8.0-Setup-x64.exe` - Windows installer (Inno Setup)
    - `WStreamLab-1.8.0-Setup-x64.msi` - MSI package (for enterprise deployment)
  - See `MSI_WRAPPER_GUIDE.txt` for MSI generation steps

- **`deploy.bat`** - Prepares application for deployment (copies Qt dependencies)

- **`startTranslations.bat`** - Updates translation files (.ts files)

## Project Structure

```
WStreamLab/
├── src/                # Main application source code
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

## Logging System

WStreamLab includes a comprehensive production-ready logging system for audit trail, troubleshooting, and compliance tracking.

### Overview

The logging system automatically records all important operations, user actions, and system events with detailed context. Logs are essential for:
- **Audit Trail:** Complete history of metrological verification sessions
- **Troubleshooting:** Detailed error messages and operational context
- **Compliance:** Tracking for metrological regulations
- **Performance Monitoring:** System behavior analysis

### Log File Location

Logs are automatically saved to:
```
{ApplicationFolder}\Logs\wstreamlab_YYYY-MM-DD.log
```

**Example:**
```
C:\Users\Constantin\Desktop\WS_corrected\WS\Release\Logs\wstreamlab_2026-01-01.log
```

### Log Management

- **Automatic Rotation:** New log file created daily
- **Retention:** Logs kept for 30 days (configurable)
- **File Splitting:** Automatic split when file exceeds 10 MB
- **Cleanup:** Old logs automatically deleted

### Log Levels

| Level        | Usage                                 | Examples                                  |
|--------------|---------------------------------------|-------------------------------------------|
| **INFO**     | Normal important operations           | Session started, PDF exported             |
| **WARNING**  | Unusual but recoverable situations    | Modbus connection retry, Missing data     |
| **ERROR**    | Errors affecting operations           | File save failed, Invalid calculation     |
| **CRITICAL** | Severe system errors                  | Application crash, Data corruption        |

### Log Categories

| Category        | Description              | Examples                                      |
|-----------------|--------------------------|-----------------------------------------------|
| **Metrology**   | Metrological operations  | Measurements, calculations, verifications     |
| **UserAction**  | User actions             | PDF export, data save/load, configuration     |
| **System**      | System operations        | App start/stop, file I/O, Modbus, registry    |
| **Error**       | Errors and exceptions    | All error types with context                  |

### Log Format

```
[YYYY-MM-DD HH:MM:SS] [LEVEL] [CATEGORY] Message
```

**Example:**
```
[2026-01-01 14:23:45] [INFO] [Metrology] Sesiune verificare început: Itron Flodis DN 25
[2026-01-01 14:24:12] [INFO] [UserAction] Măsurătoare adăugată: Q=3.5 m³/h, Index=1234.567
[2026-01-01 14:25:03] [WARNING] [System] Conectare Modbus device 1 eșuată (tentativa 2/3)
[2026-01-01 14:26:30] [INFO] [UserAction] PDF exportat: C:\Results\FM_20260101_142630.pdf (245.3 KB)
```

### Logged Events (50 cases)

#### Metrology Operations (12 events)
- ✅ Session start with full parameters (DN, flow rates, conditions, certificate)
- ✅ Session end
- ✅ Calculations started/completed with statistics (ADMIS/RESPINS counts)
- ✅ Temperature/mass values out of range (warnings)
- ✅ Invalid data auto-corrected (errors)

#### User Actions (14 events)
- ✅ PDF exported with file size
- ✅ Data saved/loaded with size and measurement count
- ✅ Meter type changed (old → new)
- ✅ Number of meters changed
- ✅ Measurement mode changed (Gravimetric ↔ Volumetric)
- ✅ Verification parameters set (temperature, pressure, humidity)
- ✅ Configuration changes

#### System Operations (19 events)
- ✅ Application started (version, user, PC name)
- ✅ Application closed
- ✅ Water meter database loaded (count of available types)
- ✅ Configuration loaded from watermeters.conf
- ✅ Configuration errors (missing file, invalid MD5, incomplete data)
- ✅ Modbus device connect/disconnect (success/failure with retry info)
- ✅ Registry keys created with defaults
- ✅ Multiple instance attempt blocked

#### Errors & Warnings (5 events)
- ✅ File access denied
- ✅ Registry write failed
- ✅ PDF export errors (directory creation, printer setup, invalid document)
- ✅ Data validation warnings

### Registry Configuration

Logging behavior can be customized via Windows Registry:

```
HKEY_CURRENT_USER\Software\WStreamLab\Logging
```

| Key              | Type   | Default | Description                             |
|------------------|--------|---------|-----------------------------------------|
| `Enabled`        | DWORD  | 1       | Enable/disable logging (1=on, 0=off)    |
| `MaxDays`        | DWORD  | 30      | Days to keep log files                  |
| `MaxFileSizeMB`  | DWORD  | 10      | Maximum size per log file (MB)          |
| `LogPath`        | String | ""      | Custom log path (empty = app folder)    |

**Note:** Registry keys are automatically created with default values on first run.

### Example Complete Log Session

```log
[2026-01-01 14:00:01] [INFO] [System] Aplicație pornită - Versiune: 1.5, Utilizator: Constantin, PC: DESKTOP-LAB
[2026-01-01 14:00:02] [INFO] [System] Configurație încărcată cu succes din watermeters.conf
[2026-01-01 14:00:02] [INFO] [System] Bază de date apometre încărcată: 156 tipuri disponibile
[2026-01-01 14:00:15] [INFO] [UserAction] Tip apometru schimbat: "Itron Flodis DN 15" → "Itron Flodis DN 25"
[2026-01-01 14:00:20] [INFO] [UserAction] Număr contoare schimbat: 3 → 5
[2026-01-01 14:00:25] [INFO] [UserAction] Temperatură setată: 22.5°C
[2026-01-01 14:00:30] [INFO] [Metrology] Sesiune verificare început: Itron Flodis DN 25, DN=25mm, Q_nom=3.500 m³/h, Q_max=7.000 m³/h, Q_t=0.053 m³/h, Q_min=0.0350 m³/h, Mod=Gravimetric, Interface=Manual, Entries=5, Temp=22.5°C, Presiune=1013mbar, Umiditate=65%, Certificat=CE 06.02-2025/15
[2026-01-01 14:05:45] [INFO] [Metrology] Calcule începute pentru 5 măsurători
[2026-01-01 14:05:46] [INFO] [Metrology] Calcule finalizate: 5/5 măsurători procesate, Rezultat: ADMIS (5 ADMIS, 0 RESPINS)
[2026-01-01 14:06:10] [INFO] [UserAction] PDF exportat: C:\Results\FM_20260101_140610.pdf (245.3 KB)
[2026-01-01 14:06:15] [INFO] [UserAction] Date salvate: inputData_20260101.txt (12.5 KB, 5 măsurători)
[2026-01-01 14:06:30] [INFO] [Metrology] Sesiune verificare terminată: Itron Flodis DN 25
[2026-01-01 14:10:00] [INFO] [System] Aplicație închisă
```

### Benefits

✅ **Complete Audit Trail** - Full session history for compliance
✅ **Fast Troubleshooting** - Detailed context for error diagnosis
✅ **No Performance Impact** - Asynchronous writing, minimal overhead
✅ **Automatic Management** - Rotation and cleanup handled automatically
✅ **Privacy-Conscious** - Only technical/operational data, no sensitive info

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

- **v1.8** (2026) - Current version with improved UI and calculation methods
- **v1.2** - Enhanced metrological verification features
- **v1.1** - Initial stable release

---

**Note:** This is a professional metrological instrument. Ensure proper calibration and training before use in official verification procedures.
