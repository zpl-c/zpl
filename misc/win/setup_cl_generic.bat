@echo off

where /q cl
IF %ERRORLEVEL% == 0 (EXIT /b)

SET "LIB="


SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 13.0
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 11.0
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\Common7\Tools\VsDevCmd.bat"))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %1))

SET VC_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools
IF NOT DEFINED LIB (IF EXIST "%VC_PATH%" (call "%VC_PATH%\VC\Auxiliary\Build\vcvarsall.bat" %1))
