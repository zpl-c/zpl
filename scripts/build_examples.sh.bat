#/bin/bash 2>nul || goto :windows
#./generate.sh.bat
export INCLUDES="-I../code"
export LINKER="-pthread -lm -ldl"
export WARNINGS="-Wall -Wextra -Wno-write-strings -Wno-implicit-fallthrough -Wno-unused-parameter -Wno-unused-function -Wno-missing-field-initializers"
for f in ../examples/*.*
do
    echo Building ${f##*/}
    g++ -g -std=c++11 $WARNINGS $INCLUDES $f $LINKER
done
exit

:windows
@echo off
rem call ./generate.sh.bat
for %%f in (..\examples\*.*) do (
    echo %%~f
    call build.bat %%~f /Od "user32.lib winmm.lib kernel32.lib" "/I..\..\..\code"

    if errorlevel 1 (
       echo Failure Reason Given is %errorlevel%
       exit /b %errorlevel%
    )
)
