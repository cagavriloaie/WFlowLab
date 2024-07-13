REM Script author: Constantin
REM Release: 1.0
REM Description: Generate translations for WStreamLab application

@echo off
cls
setlocal enabledelayedexpansion

REM Variables for paths and filenames
set "projectDir=C:\Users\Constantin\Desktop\HERE_WFlowLab"
set "qtBinDir=C:\Qt\6.7.1\mingw_64\bin"
set "translationsDir=%projectDir%\translations"
set "buildDir=%projectDir%\build"
set "meterDir=%projectDir%\meter"
set "meterProFile=%meterDir%\meter.pro"

echo. 
echo **1. ===== Checking current directory =====**
cd /D "%projectDir%"
if errorlevel 1 (
    echo Failed to change directory to %projectDir%
    goto end
)
echo Current directory: %CD%
echo.

echo.
echo **2. ===== Updating translations =====**
echo Running lupdate on meter.pro
cd "%meterDir%"
"%qtBinDir%\lupdate.exe" "%meterProFile%"
if errorlevel 1 (
    echo lupdate failed
    goto end
)
echo.

echo.
echo **3. ===== Copy .ts files to translations folder =====**
REM Create translations directory if it doesn't exist
mkdir "%translationsDir%" 2>nul
REM Copy .ts files to translations directory
copy "%meterDir%\translations\*.ts" "%translationsDir%"
echo.

echo.
echo **4. ===== Checking current directory (meterDir) =====**
cd /D "%meterDir%"
if errorlevel 1 (
    echo Failed to change directory to %meterDir%
    goto end
)
echo Current directory: %CD%
echo.

echo.
echo **4. ===== Generating .qm files =====**
REM Generate .qm files using lrelease
"%qtBinDir%\lrelease.exe" "%translationsDir%\meter_ro_RO.ts"
if errorlevel 1 (
    echo lrelease for meter_ro_RO.ts failed
    goto end
)

"%qtBinDir%\lrelease.exe" "%translationsDir%\meter_en_EN.ts"
if errorlevel 1 (
    echo lrelease for meter_en_EN.ts failed
    goto end
)
echo.

echo.
echo **7. ===== Copy translation files to build folder =====**
REM Copy .ts and .qm files to build folder
copy "%translationsDir%\*.ts" "%buildDir%"
copy "%translationsDir%\*.qm" "%buildDir%"
echo Files copied to build folder.
echo.

REM Pause to keep the console window open
pause

:end
