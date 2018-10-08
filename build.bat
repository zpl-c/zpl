@echo off
SETLOCAL

if not exist build\bin mkdir build\bin

call generate.bat

pushd build\bin
set WARN=/W3 /WX
set CMN=-MDd -nologo -fp:fast -fp:except- -GR- -EHa- -Zo -FC -Z7
set OPTS=/O2
set LIBS=user32.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib vulkan-1.lib glfw3.lib shell32.lib
set SUBSYSTEM=console
set INCLUDEPATHS=/I..\..\code /IC:\VulkanSDK\1.1.82.1\Include /IC:\glfw\include
set LIBPATHS=/LIBPATH:C:\VulkanSDK\1.1.82.1\Lib /LIBPATH:C:\glfw\lib-vc2015

echo %1

ctime -begin build.ctm
cl %1 %WARN% %OPTS% %CMN% %INCLUDEPATHS% /link %LIBPATHS% /NODEFAULTLIB:glfw3 /SUBSYSTEM:%SUBSYSTEM% %LIBS%
ctime -end build.ctm
popd