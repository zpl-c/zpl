@echo off

for %%f in (test\*.c) do (
    echo %%~f
	call build.bat ..\..\%%~f /Od
)