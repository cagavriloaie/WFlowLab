rem Turns the echo on so that each command will be shown as executed

cls
echo off 

cd C:\Users\Constantin\Desktop\w

echo ===== Start refactoring sources =====
.\AStyle\bin\AStyle.exe .\Meter\*.cpp --style=java --indent=spaces=4 --break-blocks --pad-oper --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c --recursive --indent-col1-comments --indent-classes --style=whitesmith --add-brackets
.\AStyle\bin\AStyle.exe .\Meter\*.h --style=java --indent=spaces=4 --break-blocks --pad-oper --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c --recursive --indent-col1-comments --indent-classes --style=whitesmith --add-brackets

echo

cd C:\Users\Constantin\Desktop\w\Meter\translations
copy *.qm C:\Users\Constantin\Desktop\w\Build\translations
copy *.qm C:\Users\Constantin\Desktop\w\Debug\translations
copy *.qm C:\Users\Constantin\Desktop\w\Debug\debug\translations
copy *.qm C:\Users\Constantin\Desktop\w\Release\translations
copy *.qm C:\Users\Constantin\Desktop\w\Release\release\translations

copy *.ts C:\Users\Constantin\Desktop\w\Build\translations
copy *.ts C:\Users\Constantin\Desktop\w\Debug\translations
copy *.ts C:\Users\Constantin\Desktop\w\Debug\debug\translations
copy *.ts C:\Users\Constantin\Desktop\w\Release\translations
copy *.ts C:\Users\Constantin\Desktop\w\Release\release\translations


echo

echo ===== Compile apllication =====
echo Open QT Creator and set Debug / Release mode
cd C:\Users\Constantin\Desktop\w\Meter

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

cd C:\Users\Constantin\Desktop\w\Debug
c:\msys64\mingw64\bin\mingw32-make.exe clean -j16

cd C:\Users\Constantin\Desktop\w\Meter
C:\Qt6.5\6.5.0\mingw_64\bin\qmake meter.pro

cd C:\Users\Constantin\Desktop\w\Debug
c:\msys64\mingw64\bin\mingw32-make.exe -j16

echo >>>> Copy from C:\Users\Constantin\Desktop\w\Debug\debug\WStreamLab.exe to C:\Users\Constantin\Desktop\w\Build
copy C:\Users\Constantin\Desktop\w\Debug\debug\WStreamLab.exe C:\Users\Constantin\Desktop\w\Build

echo >>>> Copy watermeters.conf
copy C:\Users\Constantin\Desktop\w\Meter\watermeters.conf C:\Users\Constantin\Desktop\w\build
goto end

:Release
ECHO echo ===== Release build =====

cd C:\Users\Constantin\Desktop\w\Release
c:\msys64\mingw64\bin\mingw32-make.exe clean -j16

cd C:\Users\Constantin\Release\w\Meter
C:\Qt6.5\6.5.0\mingw_64\bin\qmake meter.pro

cd C:\Users\Constantin\Release\w\Debug
c:\msys64\mingw64\bin\mingw32-make.exe -j16

echo >>>> Copy from C:\Users\Constantin\Desktop\w\Release\release\WStreamLab.exe to C:\Users\Constantin\Desktop\w\Build
copy C:\Users\Constantin\Desktop\w\Release\release\WStreamLab.exe C:\Users\Constantin\Desktop\w\Build

echo >>>> Copy watermeters.conf
copy C:\Users\Constantin\Desktop\w\Meter\watermeters.conf C:\Users\Constantin\Desktop\w\Build
goto end


echo 
cd C:\Users\Constantin\Desktop\w\
echo ===== Create the build =====
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" WStreamLab.iss

echo Ready

pause