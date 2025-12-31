@echo off
REM ============================================
REM WStreamLab Deployment Script
REM ============================================
REM This script copies all necessary Qt DLLs and dependencies
REM to the build directory for distribution
REM ============================================

echo.
echo ============================================
echo WStreamLab Deployment Script v1.8
echo ============================================
echo.

REM Set Qt installation path
set QT_PATH=C:\Qt\6.7.1\mingw_64

REM Set build directory
set BUILD_DIR=%~dp0build

REM Check if Qt installation exists
if not exist "%QT_PATH%" (
    echo ERROR: Qt installation not found at %QT_PATH%
    echo Please update QT_PATH in this script
    pause
    exit /b 1
)

REM Check if build directory exists
if not exist "%BUILD_DIR%" (
    echo ERROR: Build directory not found at %BUILD_DIR%
    pause
    exit /b 1
)

REM Check if executable exists
if not exist "%BUILD_DIR%\WStreamLab.exe" (
    echo ERROR: WStreamLab.exe not found in build directory
    echo Please build the project first
    pause
    exit /b 1
)

echo [1/4] Cleaning previous deployment files...
del /Q "%BUILD_DIR%\*.dll" 2>nul

echo [2/4] Running windeployqt...
"%QT_PATH%\bin\windeployqt.exe" --no-compiler-runtime "%BUILD_DIR%\WStreamLab.exe"

if errorlevel 1 (
    echo ERROR: windeployqt failed
    pause
    exit /b 1
)

echo [3/4] Copying MinGW runtime DLLs...
copy /Y "%QT_PATH%\bin\libgcc_s_seh-1.dll" "%BUILD_DIR%\" >nul
copy /Y "%QT_PATH%\bin\libstdc++-6.dll" "%BUILD_DIR%\" >nul
copy /Y "%QT_PATH%\bin\libwinpthread-1.dll" "%BUILD_DIR%\" >nul

echo [4/4] Copying additional files...
REM Copy documentation if needed
if exist "%~dp0PROCES_CALCUL_VERIFICARE_CONTOARE.md" (
    copy /Y "%~dp0PROCES_CALCUL_VERIFICARE_CONTOARE.md" "%BUILD_DIR%\" >nul
)
if exist "%~dp0VERIFICATION_METHOD_PROCESS.md" (
    copy /Y "%~dp0VERIFICATION_METHOD_PROCESS.md" "%BUILD_DIR%\" >nul
)

echo.
echo ============================================
echo Deployment completed successfully!
echo ============================================
echo.
echo Build directory: %BUILD_DIR%
echo.
dir "%BUILD_DIR%\WStreamLab.exe"
echo.
pause
