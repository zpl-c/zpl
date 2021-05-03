@echo off

del build\quick.*

call %~dp0\build_generic.bat "work/quick.c" "quick" "" "" "gdi32.lib user32.lib opengl32.lib" ""

IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)
