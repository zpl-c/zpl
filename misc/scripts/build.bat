@echo off

set WARN=/W3 /WX
set CMN=-MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -FC -Z7
set OPTS=/Od

cl %1 %WARN% %OPTS% %CMN% /I..\code
