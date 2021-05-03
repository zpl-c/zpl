@echo off
call %~dp0\build_generic.bat "code/tests/tester.c" "tester" "" "" "" ""

IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)

build\tester.exe
