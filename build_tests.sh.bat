#/bin/bash 2>nul || goto :windows
#./generate.sh.bat
for f in test/*.*
do
    echo Building ${f##*/}
    ../build.sh $f
done
exit

:windows
@echo off
rem call ./generate.sh.bat
for %%f in (test\*.*) do (
    echo %%~f
    call build.bat %%~f /Od "user32.lib winmm.lib kernel32.lib" "/I..\..\code"
)
