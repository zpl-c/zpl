@echo off
SETLOCAL

REM build.bat [file_name] [OPTS] [LIBS] [INCLUDE PATHS] [LIB PATHS] [SUBSYSTEM] [CPP_EXTRAS] [LNK_EXTRAS]

if not exist build\bin mkdir build\bin

pushd build\bin
set WARN=/W3 /WX
set CMN=-MDd -nologo -fp:fast -fp:except- -GR- -EHa- -Zo -FC -Z7
set OPTS=%2

IF [%2] == [] set OPTS=/Od

set LIBS=%~3

IF [%3] == [] set LIBS=user32.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib vulkan-1.lib glfw3.lib shell32.lib

set INCLUDEPATHS=%~4

IF [%4] == [] set INCLUDEPATHS=/I..\..\code /IC:\VulkanSDK\1.1.82.1\Include /IC:\glfw\include

set LIBPATHS=%~5

IF [%5] == [] set LIBPATHS=/LIBPATH:C:\VulkanSDK\1.1.82.1\Lib /LIBPATH:C:\glfw\lib-vc2015

set SUBSYSTEM=%6

IF [%6] == [] set SUBSYSTEM=console

set CPP_EXTRAS=%~7
set LNK_EXTRAS=%~8

ctime -begin build.ctm
cl %1 %WARN% %OPTS% %CMN% %INCLUDEPATHS% %CPP_EXTRAS% /link %LIBPATHS% /NODEFAULTLIB:glfw3 /SUBSYSTEM:%SUBSYSTEM% %LNK_EXTRAS% %LIBS%
ctime -end build.ctm
popd