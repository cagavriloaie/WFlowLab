@echo off
REM Script author: Constantin
REM Release: 3.1
REM Description: Update .ts, generate .qm, or deploy translation files

setlocal enabledelayedexpansion

REM === Project paths ===
set "projectDir=C:\Users\Constantin\Desktop\WS_corrected\WS"
set "qtBinDir=C:\Qt\6.7.1\mingw_64\bin"
set "meterDir=%projectDir%\meter"
set "translationsDir=%meterDir%\translations"
set "meterProFile=%meterDir%\WStreamLab.pro"

echo.
echo ===== WStreamLab Translation Script =====
echo Select an option:
echo 1. Update all .ts files (lupdate)
echo 2. Generate .qm files from .ts files (lrelease)
echo 3. Copy translation files to build / debug / release
choice /c 123 /n /m "Enter your choice (1, 2 or 3): "
set "userChoice=%errorlevel%"

echo.

REM ==========================================================
REM OPTION 1: UPDATE .TS FILES
REM ==========================================================
if "%userChoice%"=="1" (
    echo Updating .ts files using project file...

    cd /D "%meterDir%" || (
        echo ERROR: Cannot change directory to %meterDir%
        goto end
    )

    "%qtBinDir%\lupdate.exe" "%meterProFile%"
    if errorlevel 1 (
        echo ERROR: lupdate failed
        goto end
    )

    echo.
    echo Updated .ts files:
    dir /b "%translationsDir%\*.ts"
    goto end
)

REM ==========================================================
REM OPTION 2: GENERATE .QM FILES
REM ==========================================================
if "%userChoice%"=="2" (
    echo Generating .qm files in meter\translations ...

    if not exist "%translationsDir%\*.ts" (
        echo ERROR: No .ts files found in %translationsDir%
        goto end
    )

    for %%f in ("%translationsDir%\*.ts") do (
        echo Generating %%~nf.qm
        "%qtBinDir%\lrelease.exe" "%%f" -qm "%translationsDir%\%%~nf.qm"
        if errorlevel 1 echo ERROR: lrelease failed for %%~nxf
    )

    echo.
    echo Generated .qm files:
    dir /b "%translationsDir%\*.qm"
    goto end
)

if "%userChoice%"=="3" (
    echo Deploying translation files...
    echo.

    set "dst1=%projectDir%\build\translations"
    set "dst2=%projectDir%\Debug\debug\translations"
    set "dst3=%projectDir%\Release\release\translations"

    for %%D in ("!dst1!" "!dst2!" "!dst3!") do (
        if not exist "%%~D" (
            echo Creating directory: %%~D
            mkdir "%%~D"
        )

        echo.
        echo Copying to: %%~D
        echo -------------------------------------------

        for %%F in (
            meter_en_EN.ts
            meter_en_EN.qm
            meter_ro_RO.ts
            meter_ro_RO.qm
        ) do (
            if exist "%translationsDir%\%%F" (
                copy /y "%translationsDir%\%%F" "%%~D\%%F" >nul && (
                    echo [OK] %%~D\%%F
                ) || (
                    echo [ERROR] %%~D\%%F
                )
            ) else (
                echo [SKIP] Source not found: %%F
            )
        )
    )

    echo.
    echo ===========================================
    echo Translation files deployed successfully.
    echo ===========================================
    goto end
)

goto :eof

:end
pause
