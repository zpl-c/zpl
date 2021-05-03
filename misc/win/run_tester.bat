@echo off
call %~dp0\build_generic.bat "code/tests/tester.c" "tester" "" "" "" ""
build\tester.exe
