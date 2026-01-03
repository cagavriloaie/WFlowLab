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

REM Run MSI Wrapper to convert .exe to .msi
"%MSI_WRAPPER%" "!EXE_FILE!" "!MSI_FILE!" /q

if errorlevel 1 (
    echo.
    echo [WARNING] MSI Wrapper returned error code, but file might still be generated.
    echo Please check the output folder.
)

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
