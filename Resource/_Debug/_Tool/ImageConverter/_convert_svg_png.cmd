@echo off

rem ====================================================================================================
rem = Modify the SIZELIST
rem ====================================================================================================
rem = ICSIZELIST: Speicify size list
rem = ICNOECHO: Don't output file name
rem ====================================================================================================

set SIZELIST=16 24 32 48 64 96 128 256



rem ====================================================================================================

set CONV="%~dp0convert.exe"

if not exist %CONV% (
 echo Can't find convert.exe at %CONV%
 echo.
 echo Please edit this cmd file to set a correct path
 echo or you can put convert.exe ^(from ImageMagick^) to this folder.
 echo.
 goto l_exit
)

if :%1:==:: goto l_nofile

if not "%ICSIZELIST%"=="" goto l_listinput

echo   [1] Use list (7 sizes): 16 24 32 48 64 96 128
echo   [2] Use list (10 sizes): 16 20 24 32 40 48 64 80 96 128
echo   [3] Use list (13 sizes): 16 20 24 28 32 40 48 56 64 80 96 112 128
echo   [4] Use list (15 sizes): 16 20 24 28 32 36 40 48 56 64 72 80 96 112 128
echo   [5] Use list (You can edit this cmd file): %SIZELIST%
echo.
echo   [Q] Quit
echo.
choice /C 12345Q /N /M Select:
if errorlevel 6 goto l_end
if errorlevel 5 goto l_start
if errorlevel 4 goto l_list3
if errorlevel 3 goto l_list2
if errorlevel 2 goto l_list1
if errorlevel 1 goto l_list0
goto l_end

:l_list0
set SIZELIST=16 24 32 48 64 96 128
goto l_start

:l_list1
set SIZELIST=16 20 24 32 40 48 64 80 96 128
goto l_start

:l_list2
set SIZELIST=16 20 24 28 32 40 48 56 64 80 96 112 128
goto l_start

:l_list3
set SIZELIST=16 20 24 28 32 36 40 48 56 64 72 80 96 112 128
goto l_start

:l_listinput
set SIZELIST=%ICSIZELIST%
goto l_start

rem ====================================================================================================

:l_start
set FLAG=-background transparent -depth 8 -gravity center -strip
setlocal enabledelayedexpansion

:l_loop
if :%1:==:: goto l_exit
set CURFILE=%~f1
set CURFILEN=%~dpn1
set CURFILEX=%~x1
if :^%CURFILE:~0,1%:==:^": set CURFILE=%CURFILE:~1,-1%
if not %CURFILEX%==.svg goto l_next

if "%ICNOECHO%"=="" echo Converting "%CURFILE%"

set "index=0"
for %%i in (%SIZELIST%) do (
 %CONV% %FLAG% -size %%ix%%i -extent %%ix%%i "%CURFILE%" "%CURFILEN%#!index!.png"
 set /a "index+=1"
)

:l_next
shift
goto l_loop

:l_nofile
echo Please drag svg files on this cmd batch file.
echo You can also drag non-svg files together and they will be ignored automatically.
echo.
:l_exit
if not "%ICSIZELIST%"=="" goto l_end
pause
:l_end
