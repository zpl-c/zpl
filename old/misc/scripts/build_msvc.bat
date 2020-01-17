@echo off
SETLOCAL

if not exist bin mkdir bin

pushd bin
set WARN=/W3 /WX
set CMN=-MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -FC -Z7
set OPTS=/Od
set LIBS=user32.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib
set SUBSYSTEM=console

python.exe w:\zpl\code\zpl\build.py

ctime -begin quick.ctm
cl ..\%1 %WARN% %OPTS% %CMN% /I..\..\code /link /SUBSYSTEM:%SUBSYSTEM% %LIBS%
ctime -end quick.ctm
popd