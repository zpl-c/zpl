@echo off
set location=%cd%
set me="%~dp0"
cd %me%

call setup_cl_generic.bat amd64
cd %location%

rem source_file %1
rem app_name %2
rem build_opts %3
rem compile_flags %4
rem link_flags %5
rem mode %6

set debug=/Zi /D_DEBUG
set release=/O2 /Zi /D_NDEBUG
set mode=%debug%
if "%6" == "release" (set mode=%release%)

set final_build_opts=%~3 /GR- /nologo /FC /D_WIN32 /D_WIN64
set final_warnings=/WL /W4 /WX /wd4310 /wd4100 /wd4201 /wd4756 /wd4204 /wd4214 /wd4505 /wd4996 /wd4127 /wd4510 /wd4244 /wd4512 /wd4610 /wd4457
set final_compile_flags=%~4 %mode% %final_warnings% /I ../code/
set final_link_flags=%~5 winmm.lib -opt:ref -incremental:no

if not exist build mkdir build
pushd build
	cl %final_build_opts% %final_compile_flags% ../%~1 /link %final_link_flags% /out:%~2.exe
popd