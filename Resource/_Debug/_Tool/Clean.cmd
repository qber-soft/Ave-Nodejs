@echo off

setlocal enabledelayedexpansion

:l_loop
if :%1:==:: goto l_exit

set CURDIR=%~f1
set CURDIRN=%~n1
if :^%CURDIR:~0,1%:==:^": set CURDIR=%CURDIR:~1,-1%

echo Cleaning %CURDIRN% ...
for /d %%i in ("%CURDIR%\*-Raw") do (
 set CURFILE=%%~i
 set CURFILE=!CURFILE:-Raw=!
 echo   !CURFILE!
 rd /s /q "!CURFILE!" 2>nul
)

shift
goto l_loop

:l_exit

echo Cleaning other files ...
del /f /q *.log 2>nul
del /f /q *.index 2>nul
