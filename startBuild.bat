@echo off
setlocal enabledelayedexpansion

rem Function to clean a directory
:cleanDirectory
    if exist "%1\*" (
        echo Cleaning directory: %1
        for %%f in ("%1\*") do (
            if exist "%%f" (
                del /f /q "%%f" > nul 2>&1
                if exist "%%f" (
                    echo Failed to delete: "%%f"
                ) else (
                    echo Deleted: "%%f"
                )
            )
        )
        for /d %%d in ("%1\*") do (
            if exist "%%d" (
                rmdir /s /q "%%d" > nul 2>&1
                if exist "%%d" (
                    echo Failed to delete directory: "%%d"
                ) else (
                    echo Deleted directory: "%%d"
                )
            )
        )
    ) else (
        echo Directory %1 is already clean or does not exist.
    )
goto :eof

echo ===== Cleaning Debug and Release directories =====
call :cleanDirectory "C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug"
call :cleanDirectory "C:\Users\Constantin\Desktop\HERE_WFlowLab\Release"

echo ===== Checking current directory =====
cd /D C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter
echo Current directory: %CD%

echo ===== Updating translations =====
lupdate meter.pro
cd /D C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\translations
lrelease meter_en_EN.ts
lrelease meter_ro_RO.ts

rem Copy translation files to Build, Debug, and Release directories
set "translation_dirs=Build Debug Release"
for %%D in (%translation_dirs%) do (
    echo ===== Copying translations to %%D directory =====
    mkdir C:\Users\Constantin\Desktop\HERE_WFlowLab\%%D\translations > nul 2>&1
    copy *.qm C:\Users\Constantin\Desktop\HERE_WFlowLab\%%D\translations
    copy *.ts C:\Users\Constantin\Desktop\HERE_WFlowLab\%%D\translations
)

echo ===== Compiling application =====
echo Open QT Creator and set Debug / Release mode
cd /D C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter

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
C:\Qt6.5\6.5.0\mingw_64\bin\qmake.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\meter.pro -spec win32-g++ %qmake_config%

echo ">>>>>>>>>>>>>>>>>>> STEP 2: Generating Makefile"
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe qmake_all

echo ">>>>>>>>>>>>>>>>>>> STEP 3: Building"
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe -j16

timeout /nobreak /t 5 >nul
echo "Done waiting for 5 seconds"

echo >>>> Copying executable to Build directory
copy /Y C:\Users\Constantin\Desktop\HERE_WFlowLab\%build_type%\WStreamLab.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Build

goto :EOF

:end
echo ===== Creating the installer =====
cd /D C:\Users\Constantin\Desktop\HERE_WFlowLab
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" WStreamLab.iss

echo Ready
pause
