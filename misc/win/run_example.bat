@echo off

call %~dp0\build_example.bat %1
IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)
for /f "tokens=1,* delims= " %%a in ("%*") do set REST=%%b
build\%1.exe %REST%

