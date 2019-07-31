@echo off
SETLOCAL

REM build.bat [file_name] [OPTS] [INCLUDE PATHS] [LIBS] [LIB PATHS] [SUBSYSTEM] [CPP_EXTRAS] [LNK_EXTRAS]

if not exist build\bin mkdir build\bin

pushd build\bin
set WARN=/W3 /WX
set CMN=-MDd -nologo -fp:fast -fp:except- -GR- -EHa- -Zo -FC -Z7
set OPTS=%2

IF [%2] == [] set OPTS=/Od

set INCLUDEPATHS=%~3

IF [%3] == [] set INCLUDEPATHS=/I..\..\ /IW:\zpl\code /IC:\VulkanSDK\1.1.97.0\Include /IC:\glfw\include

set LIBS=%~4

IF [%4] == [] set LIBS=user32.lib gdi32.lib winmm.lib opengl32.lib kernel32.lib shell32.lib

set LIBPATHS=%~5

set VULKAN=/LIBPATH:D:\VulkanSDK\1.1.97.0\Lib
set GLFW=/LIBPATH:C:\glfw\lib-vc2015

IF [%5] == [] set LIBPATHS=%VULKAN% %GLFW%

set SUBSYSTEM=%6

IF [%6] == [] set SUBSYSTEM=console

set CPP_EXTRAS=%~7
set LNK_EXTRAS=%~8

ctime -begin build.ctm
cl ..\..\%1 %WARN% %OPTS% %CMN% %INCLUDEPATHS% %CPP_EXTRAS% /link %LIBPATHS% /NODEFAULTLIB:glfw3 /SUBSYSTEM:%SUBSYSTEM% %LNK_EXTRAS% %LIBS%
ctime -end build.ctm
popd