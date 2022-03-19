@echo off

set IC=%~dp0ImageConverter\_convert_svg_png.cmd

if "%ICSIZELIST%"=="" goto l_inputparam

setlocal enabledelayedexpansion

:l_loop
if :%1:==:: goto l_exit

set CURDIR=%~f1
set CURDIRN=%~n1
if :^%CURDIR:~0,1%:==:^": set CURDIR=%CURDIR:~1,-1%

echo Building %CURDIRN% icons...
set "nAdd=0"
set "nUpdate=0"
set "nRemove=0"
set "nSkip=0"

pushd "%CURDIR%"

for /r "Icon-Raw" %%i in (*.svg) do (
 set CURFILE=%%~i
 set CURFILE=!CURFILE:%~dp1Icon-Raw\=!
 set NEEDCOPY=0
 xcopy /l /d /y "Icon-Raw\!CURFILE!" "Icon\!CURFILE!*" | findstr /b /c:"1" > nul && set NEEDCOPY=1
 if !NEEDCOPY!==1 (
  if not exist "Icon\!CURFILE!*" (
   echo   + %CURDIRN%\Icon\!CURFILE!
   set /a "nAdd+=1"
  ) else (
   echo   * %CURDIRN%\Icon\!CURFILE!
   set /a "nUpdate+=1"
  )
  xcopy /y "Icon-Raw\!CURFILE!" "Icon\!CURFILE!*" > nul
  call "%IC%" "Icon\!CURFILE!"
 ) else (
  echo     %CURDIRN%\Icon\!CURFILE!
  set /a "nSkip+=1"
 )
)

for /r "Icon" %%i in (*.svg) do (
 set CURFILE=%%~i
 set CURFILE=!CURFILE:~0,-4!
 set CURFILE=!CURFILE:%~dp1Icon\=!
 if not exist "Icon-Raw\!CURFILE!.svg" (
  echo   - %CURDIRN%\Icon\!CURFILE!.svg
  del /f /q "Icon\!CURFILE!.svg"
  for /l %%i in (0,1,15) do del /f /q "Icon\!CURFILE!#%%i.png" 2>nul
  set /a "nRemove+=1"
 )
)

for /r "Icon" /d %%i in (*) do rd /q "%%i" 2>nul
rd /q Icon 2>nul

popd
echo   !nAdd! added^(+^), !nUpdate! updated^(*^), !nRemove! removed^(-^), !nSkip! skipped^( ^).
echo.

shift
goto l_loop

:l_inputparam
please set ICSIZELIST before call this command.
goto l_exit

:l_exit
