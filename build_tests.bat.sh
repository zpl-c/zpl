#/bin/bash 2>nul || goto :windows
./generate.sh
for f in test/*.c
do
    echo Building ${f##*/}
    ./build.sh $f
done
exit

:windows
@echo off
./generate.sh
for %%f in (test\*.c) do (
    echo %%~f
	call build.bat ..\..\%%~f /Od "user32.lib winmm.lib kernel32.lib" "/I..\..\code"
)