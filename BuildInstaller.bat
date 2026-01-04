@echo off
REM ========================================
REM WStreamLab Installer Builder
REM Builds both .exe and .msi installers
REM ========================================

setlocal enabledelayedexpansion

echo.
echo ========================================
echo  WStreamLab Installer Builder
echo ========================================
echo.

REM Define paths
set INNO_COMPILER=C:\Program Files (x86)\Inno Setup 6\ISCC.exe
set MSI_WRAPPER=C:\Program Files (x86)\MSI Wrapper\MsiWrapper.exe
set ISS_FILE=WStreamLab.iss
set OUTPUT_DIR=output
set MWRP_CONFIG=WStreamLab.mwrp

REM Check if Inno Setup Compiler exists
if not exist "%INNO_COMPILER%" (
    echo [ERROR] Inno Setup Compiler not found at:
    echo "%INNO_COMPILER%"
    echo.
    echo Please install Inno Setup 6 or update the path in this script.
    pause
    exit /b 1
)

REM Check if MSI Wrapper exists
if not exist "%MSI_WRAPPER%" (
    echo [ERROR] MSI Wrapper not found at:
    echo "%MSI_WRAPPER%"
    echo.
    echo Please install MSI Wrapper from https://www.exemsi.com/download/
    pause
    exit /b 1
)

REM Check if .iss file exists
if not exist "%ISS_FILE%" (
    echo [ERROR] Installer script not found: %ISS_FILE%
    pause
    exit /b 1
)

echo [1/4] Compiling Inno Setup script...
echo.

REM Compile the Inno Setup script
"%INNO_COMPILER%" "%ISS_FILE%"

if errorlevel 1 (
    echo.
    echo [ERROR] Inno Setup compilation failed!
    pause
    exit /b 1
)

echo.
echo [2/4] Compilation successful!
echo.

REM Find the generated .exe file
for %%F in ("%OUTPUT_DIR%\*.exe") do (
    set "EXE_FILE=%%F"
    set "EXE_NAME=%%~nF"
)

if not defined EXE_FILE (
    echo [ERROR] No .exe file found in %OUTPUT_DIR%\
    pause
    exit /b 1
)

echo [3/4] Found installer: !EXE_NAME!.exe
echo.

REM Generate MSI filename (same name as EXE but with .msi extension)
set "MSI_FILE=%OUTPUT_DIR%\!EXE_NAME!.msi"

echo [4/4] Generating MSI package...
echo.

REM Check MSI Wrapper version to determine automation capability
for /f %%v in ('"%MSI_WRAPPER%" /?') do set MSI_VERSION=%%v
echo [INFO] MSI Wrapper version: %MSI_VERSION%

REM Check if .mwrp configuration file exists
if exist "%MWRP_CONFIG%" (
    echo [INFO] Found project file: %MWRP_CONFIG%
    echo.
    echo [IMPORTANT] MSI Wrapper 11.x Free version requires GUI interaction.
    echo The project file can be loaded manually in MSI Wrapper.
    echo.
    echo Options:
    echo   1. Manual: Open MSI Wrapper GUI and load %MWRP_CONFIG%
    echo   2. Auto:   Purchase MSI Wrapper Pro for CLI automation
    echo   3. Alternative: Use WiX Toolset for full automation (free)
    echo.
    choice /c 12 /n /m "Press 1 to open MSI Wrapper GUI, or 2 to skip MSI generation: "

    if errorlevel 2 (
        echo [SKIPPED] MSI generation skipped by user.
        goto skip_msi
    )

    if errorlevel 1 (
        echo [INFO] Opening MSI Wrapper GUI...
        echo [INFO] Opening quick reference guide...
        echo.

        REM Open the guide and MSI Wrapper
        if exist "MSI_WRAPPER_GUIDE.txt" start "" "MSI_WRAPPER_GUIDE.txt"
        start "" "%MSI_WRAPPER%"

        echo ========================================
        echo  MANUAL STEPS REQUIRED
        echo ========================================
        echo.
        echo In MSI Wrapper GUI:
        echo   1. Input:  !EXE_FILE!
        echo   2. Output: !MSI_FILE!
        echo   3. Product: WStreamLab 1.8.0.0 by ELCOST
        echo   4. Upgrade Code: {3F8A2C5E-1B4D-4A7C-9E2F-6D8B5A4C3E1F}
        echo   5. Click "Wrap" button
        echo   6. Save project as: %MWRP_CONFIG% (optional)
        echo.
        echo See MSI_WRAPPER_GUIDE.txt for detailed instructions.
        echo.
        echo Press any key when MSI generation is complete...
        pause >nul
    )
) else (
    echo [WARNING] Project file not found: %MWRP_CONFIG%
    echo [INFO] Attempting to open MSI Wrapper GUI...
    echo.
    start "" "%MSI_WRAPPER%"
    echo.
    echo Please configure manually:
    echo   - Input:  !EXE_FILE!
    echo   - Output: !MSI_FILE!
    echo   - Then save as: %MWRP_CONFIG%
    echo.
    echo Press any key when done...
    pause >nul
)

:skip_msi

REM Check if MSI was created
if exist "!MSI_FILE!" (
    echo.
    echo ========================================
    echo  BUILD SUCCESSFUL!
    echo ========================================
    echo.
    echo Generated files in %OUTPUT_DIR%\:
    echo   [EXE] !EXE_NAME!.exe
    echo   [MSI] !EXE_NAME!.msi
    echo.
) else (
    echo.
    echo [ERROR] MSI file was not created!
    echo Please run MSI Wrapper manually on:
    echo !EXE_FILE!
    echo.
)

REM Show output directory
echo Opening output directory...
start "" "%OUTPUT_DIR%"

echo.
echo Press any key to exit...
pause >nul
