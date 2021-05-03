@echo off
call %~dp0\build_quick.bat

IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)

build\quick.exe
