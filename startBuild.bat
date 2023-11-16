rem Turns the echo on so that each command will be shown as executed

cls
echo off 

cd C:\Users\Constantin\Desktop\HERE_WFlowLab\

  echo ===== Start refactoring sources =====
.\AStyle\bin\AStyle.exe .\Meter\*.cpp ^
--recursive ^
--add-brackets ^
--add-braces ^
--style=allman ^
--indent=spaces=4 ^
--indent-modifiers ^
--indent-switches ^
--indent-cases ^
--indent-namespaces ^
--indent-preproc-block ^
--min-conditional-indent=2 ^
--pad-oper ^
--pad-header ^
--unpad-paren ^
--delete-empty-lines ^
--align-pointer=name ^
--align-reference=name ^
--keep-one-line-statements ^
--convert-tabs ^
--close-templates ^
--max-code-length=70 ^
--suffix=none ^
--lineend=linux ^
--verbose 

.\AStyle\bin\AStyle.exe .\Meter\*.h ^
--recursive ^
--add-brackets ^
--add-braces ^
--style=allman ^
--indent=spaces=4 ^
--indent-modifiers ^
--indent-switches ^
--indent-cases ^
--indent-namespaces ^
--indent-preproc-block ^
--min-conditional-indent=2 ^
--pad-oper ^
--pad-header ^
--unpad-paren ^
--delete-empty-lines ^
--align-pointer=name ^
--align-reference=name ^
--keep-one-line-statements ^
--convert-tabs ^
--close-templates ^
--max-code-length=70 ^
--suffix=none ^
--lineend=linux ^
--verbose 

echo ===== Translations update ===== 

cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter
lupdate meter.pro

cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\translations
lrelease meter_en_EN.ts
lrelease meter_ro_RO.ts

cd C:\Users\Constantin\Desktop\HERE_WFlowLab

cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\translations
copy *.qm C:\Users\Constantin\Desktop\HERE_WFlowLab\Build\translations
copy *.ts C:\Users\Constantin\Desktop\HERE_WFlowLab\Build\translations

mkdir C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug\translations
copy *.qm C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug\translations
copy *.ts C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug\translations

mkdir C:\Users\Constantin\Desktop\HERE_WFlowLab\Release\translations
copy *.qm C:\Users\Constantin\Desktop\HERE_WFlowLab\Release\translations
copy *.ts C:\Users\Constantin\Desktop\HERE_WFlowLab\Release\translations

echo " "
echo ===== Compile apllication =====
echo Open QT Creator and set Debug / Release mode
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter

:start
ECHO.
ECHO 1. Debug
ECHO 2. Release
set choice=
set /p choice=Type the number to print text.
if not '%choice%'=='' set choice=%choice:~0,1%
if '%choice%'=='1' goto Debug
if '%choice%'=='2' goto Release
ECHO "%choice%" is not valid, try again
ECHO.
goto start

:Debug
ECHO echo ===== Debug build =====

echo ">>>>>>>>>>>>>>>>>>> STEP 1"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe clean -j16

echo ">>>>>>>>>>>>>>>>>>> STEP 2"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter
C:\Qt6.5\6.5.0\mingw_64\bin\qmake.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\meter.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"

echo ">>>>>>>>>>>>>>>>>>> STEP 3"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe -f C:/Users/Constantin/Desktop/HERE_WFlowLab/Debug/Makefile qmake_all

echo ">>>>>>>>>>>>>>>>>>> STEP 4"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe -j16

timeout /nobreak /t 5 >nul
echo Done waiting for 5 seconds

cd ..

echo >>>> Copy from C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug\debug\WStreamLab.exe to C:\Users\Constantin\Desktop\HERE_WFlowLab\Build
copy C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug\debug\WStreamLab.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Build

echo >>>> Copy watermeters.conf
copy C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\watermeters.conf C:\Users\Constantin\Desktop\HERE_WFlowLab\Build

goto end


:Release
ECHO echo ===== Release build =====

echo ">>>>>>>>>>>>>>>>>>> STEP 1"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Debug
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe clean -j16

echo ">>>>>>>>>>>>>>>>>>> STEP 2"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter
C:\Qt6.5\6.5.0\mingw_64\bin\qmake.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\meter.pro -spec win32-g++ "CONFIG+=qtquickcompiler"

echo ">>>>>>>>>>>>>>>>>>> STEP 3"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Release
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe -f C:/Users/Constantin/Desktop/HERE_WFlowLab/Release/Makefile qmake_all

echo ">>>>>>>>>>>>>>>>>>> STEP 4"
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\Release
C:\Qt6.5\Tools\mingw1120_64\bin\mingw32-make.exe -j16

cd ..

echo >>>> Copy from C:\Users\Constantin\Desktop\HERE_WFlowLab\Release\release\WStreamLab.exe to C:\Users\Constantin\Desktop\HERE_WFlowLab\Build
copy C:\Users\Constantin\Desktop\HERE_WFlowLab\Release\release\WStreamLab.exe C:\Users\Constantin\Desktop\HERE_WFlowLab\Build

echo >>>> Copy watermeters.conf
copy C:\Users\Constantin\Desktop\HERE_WFlowLab\Meter\watermeters.conf C:\Users\Constantin\Desktop\HERE_WFlowLab\build

goto end


echo 
cd C:\Users\Constantin\Desktop\HERE_WFlowLab\
echo ===== Create the build =====
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" WStreamLab.iss

:end

echo Ready

pause