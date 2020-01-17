#/bin/bash 2>nul || goto :windows
cd "$(dirname $0)"
export INCLUDES="-I../code"
export LINKER="-lm -ldl"
export WARNINGS="-Wall -Wextra -Wno-write-strings -Wno-implicit-fallthrough -Wno-unused-parameter -Wno-unused-function -Wno-missing-field-initializers"

g++ -g -pthread -std=c++11 $WARNINGS $INCLUDES ../tests/tester.c $LINKER -o ../build/unit && ../build/unit

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
