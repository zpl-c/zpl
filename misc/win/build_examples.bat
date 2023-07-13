@echo off

call %~dp0%\setup_cl_generic.bat amd64

for %%f in (code/apps/examples/*.c) do call %~dp0\build_generic.bat "code/apps/examples/%%f" "%%~nf" "" "" "gdi32.lib user32.lib opengl32.lib" ""

IF NOT %ERRORLEVEL% == 0 (EXIT /b -1)

