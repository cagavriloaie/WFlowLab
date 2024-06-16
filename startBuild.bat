@echo off
setlocal enabledelayedexpansion

rem Define paths
set BASE_PATH=C:\Users\Constantin\Desktop\HERE_WFlowLab
set PROJECT_PATH=%BASE_PATH%\Meter
set TRANSLATIONS_PATH=%PROJECT_PATH%\translations
set OUTPUT_PATH=%BASE_PATH%\output

rem Define Qt paths
set QT_BIN_PATH=C:\Qt\Tools\mingw1310_64\bin
set QT_VERSION_BIN_PATH=C:\Qt\6.5.0\bin
set INNO_SETUP_PATH="C:\Program Files (x86)\Inno Setup 6"

echo ===== Checking current directory =====
cd /D %PROJECT_PATH%
if errorlevel 1 (
    echo Failed to change directory to %PROJECT_PATH%
    goto end
)
echo Current directory: %CD%

echo ===== Updating translations =====
%QT_VERSION_BIN_PATH%\lupdate.exe meter.pro
if errorlevel 1 (
    echo lupdate failed
    goto end
)

cd /D %TRANSLATIONS_PATH%
if errorlevel 1 (
    echo Failed to change directory to %TRANSLATIONS_PATH%
    goto end
)

%QT_VERSION_BIN_PATH%\lrelease.exe meter_en_EN.ts
if errorlevel 1 (
    echo lrelease for meter_en_EN.ts failed
    goto end
)

%QT_VERSION_BIN_PATH%\lrelease.exe meter_ro_RO.ts
if errorlevel 1 (
    echo lrelease for meter_ro_RO.ts failed
    goto end
)

rem Copy translation files to Build, Debug, and Release directories
set "translation_dirs=Build Debug Release"
for %%D in (%translation_dirs%) do (
    echo ===== Copying translations to %%D directory =====
    mkdir %OUTPUT_PATH%\%%D\translations > nul 2>&1
    copy *.qm %OUTPUT_PATH%\%%D\translations
    copy *.ts %OUTPUT_PATH%\%%D\translations
)

echo ===== Compiling application =====
cd /D %PROJECT_PATH%
if errorlevel 1 (
    echo Failed to change directory to %PROJECT_PATH%
    goto end
)

:start
echo.
echo 1. Debug
echo 2. Release
set choice=
set /p choice=Type the number to select build mode: 
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='1' goto Debug
if '%choice%'=='2' goto Release
echo "%choice%" is not valid, try again
echo.
goto start

:Debug
echo ===== Debug build =====
call :build Debug "CONFIG+=debug CONFIG+=qml_debug"
goto end

:Release
echo ===== Release build =====
call :build Release "CONFIG+=qtquickcompiler"
goto end

:build
set "build_type=%1"
set "qmake_config=%2"

echo ">>>>>>>>>>>>>>>>>>> STEP 1: Running qmake"
%QT_BIN_PATH%\qmake.exe %PROJECT_PATH%\meter.pro -spec win32-g++ %qmake_config%
if errorlevel 1 (
    echo qmake failed
    goto end
)

echo ">>>>>>>>>>>>>>>>>>> STEP 2: Generating Makefile"
%QT_BIN_PATH%\mingw32-make.exe qmake_all
if errorlevel 1 (
    echo Makefile generation failed
    goto end
)

echo ">>>>>>>>>>>>>>>>>>> STEP 3: Building"
%QT_BIN_PATH%\mingw32-make.exe -j16
if errorlevel 1 (
    echo Build failed
    goto end
)

timeout /nobreak /t 5 >nul
echo "Done waiting for 5 seconds"

echo >>>> Copying executable to Build directory
mkdir %OUTPUT_PATH%\Build > nul 2>&1
copy /Y %BASE_PATH%\%build_type%\WStreamLab.exe %OUTPUT_PATH%\Build
if errorlevel 1 (
    echo Failed to copy executable
    goto end
)

goto :EOF

:end
echo ===== Creating the installer =====
cd /D %OUTPUT_PATH%
if errorlevel 1 (
    echo Failed to change directory to %OUTPUT_PATH%
    goto end
)

echo Ready
pause
