@echo off

goto Win%PROCESSOR_ARCHITEW6432%

:Win
goto %PROCESSOR_ARCHITECTURE%

:Winx86
goto x86

:Winamd64
goto x64

:x86
echo 32-bit
"%~dp0MirrInst32.exe" -u dfmirage
goto Result

:amd64
echo 64-bit
"%~dp0MirrInst64.exe" -u dfmirage
goto Result

:Result
echo Result code is %ERRORLEVEL%

:end
