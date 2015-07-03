rem @echo off

ver | find "5.0" > nul
if %ERRORLEVEL% == 0 goto Win2000

ver | find "5.1" > nul
if %ERRORLEVEL% == 0 goto WinXP%PROCESSOR_ARCHITEW6432%

goto Win2003

:Win2000
goto v068

:WinXP
goto WinXP%PROCESSOR_ARCHITECTURE%

:WinXPx86
goto v068

:WinXPamd64
goto v105x64

:Win2003
goto v105%PROCESSOR_ARCHITEW6432%

:v105
goto v105%PROCESSOR_ARCHITECTURE%

:v105x86
echo 2.0.105 32-bit
"%~dp0MirrInst32.exe" -i "dfmirage" "Mirage Driver" "%~dp0105\" "%~dp0105\dfmirage.inf"
goto Result

:v105amd64
echo 2.0.105 64-bit
"%~dp0MirrInst64.exe" -i "dfmirage" "Mirage Driver" "%~dp0105\" "%~dp0105\dfmirage.inf"
goto Result

:v068
echo 1.1.68
"%~dp0MirrInst32.exe" -i "dfmirage" "Mirage Driver" "%~dp0068\" "%~dp0068\dfmirage.inf"
goto Result

:Result
echo Result code is %ERRORLEVEL%

:end
