@echo off

call %~dp0%\setup_cl_generic.bat amd64

call %~dp0\build_generic.bat "code/apps/examples/%1.c" "%1" "" "" "gdi32.lib user32.lib opengl32.lib" ""

IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)

