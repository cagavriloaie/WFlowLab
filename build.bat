rem Turns the echo on so that each command will be shown as executed

cls
echo off 


echo ===== Remove Debug and Release folders =====
cd C:\Users\Constantin\Desktop\WFlowLab\stream
rem @rd /S /Q "C:\Users\Constantin\Desktop\stream\WFlowLab\Debug"
rem @rd /S /Q "C:\Users\Constantin\Desktop\stream\WFlowLab\Release"

echo

echo ===== Start refactoring sources =====
.\AStyle\bin\AStyle.exe .\contor\*.cpp --style=java --indent=spaces=4 --break-blocks --pad-oper --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c --recursive
.\AStyle\bin\AStyle.exe .\contor\*.h --style=java --indent=spaces=4 --break-blocks --pad-oper --pad-comma --pad-paren --align-pointer=name --add-braces --mode=c --recursive

echo

echo ===== Start translations =====
cd contor
c:\Qt\Tools\CMake_64\bin\cmake.exe  --build . --target update_translations
dir *.ts
lrelease romanian.ts
lrelease english.ts
dir *.qm
echo copy qm files
mkdir C:\Users\Constantin\Desktop\stream\WFlowLab\Debug
mkdir C:\Users\Constantin\Desktop\stream\WFlowLab\Debug\translations
mkdir C:\Users\Constantin\Desktop\stream\WFlowLab\Release
mkdir C:\Users\Constantin\Desktop\stream\WFlowLab\Release\translations
copy *.qm C:\Users\Constantin\Desktop\stream\WFlowLab\build\translations
copy *.qm C:\Users\Constantin\Desktop\stream\WFlowLab\Debug\translations
copy *.qm C:\Users\Constantin\Desktop\stream\WFlowLab\Release\translations

echo

echo ===== Compile apllication =====
echo Open QT Creator and set Debug / Release mode
cd C:\Users\Constantin\Desktop\stream\WFlowLab
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
ECHO Debug build
C:\Qt\Tools\CMake_64\bin\cmake.exe --build C:\Users\Constantin\Desktop\stream\WFlowLab\Debug --target clean
C:\Qt\Tools\CMake_64\bin\cmake.exe --build C:\Users\Constantin\Desktop\stream\WFlowLab\Debug --target all

copy C:\Users\Constantin\Desktop\stream\WFlowLab\Debug\WStreamLab.exe C:\Users\Constantin\Desktop\stream\WFlowLab\build
copy C:\Users\Constantin\Desktop\stream\WFlowLab\Contor\watermeters.conf C:\Users\Constantin\Desktop\stream\WFlowLab\Debug
goto end

:Release
ECHO Relese build
C:\Qt\Tools\CMake_64\bin\cmake.exe --build C:\Users\Constantin\Desktop\stream\WFlowLab\Release --target clean
C:\Qt\Tools\CMake_64\bin\cmake.exe --build C:\Users\Constantin\Desktop\stream\WFlowLab\Release --target all
copy C:\Users\Constantin\Desktop\stream\WFlowLab\Release\WStreamLab.exe C:\Users\Constantin\Desktop\stream\WFlowLab\build
copy C:\Users\Constantin\Desktop\stream\WFlowLab\Contor\watermeters.conf C:\Users\Constantin\Desktop\stream\WFlowLab\Release
goto end

:end

echo 

echo ===== Create the build =====
"C:\Program Files (x86)\Inno Setup 6\ISCC.exe" WStreamLab.iss

echo Ready

pause