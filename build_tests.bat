@echo off

for %%f in (test\*.c) do (
    echo %%~f
	call build.bat ..\..\%%~f /Od "user32.lib winmm.lib kernel32.lib" "/I..\..\code"
)