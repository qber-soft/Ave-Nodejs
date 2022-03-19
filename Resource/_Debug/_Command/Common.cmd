@echo off

if not exist ..\Data md ..\Data
rem if not exist ..\DataTemp md ..\DataTemp

rem set AC=..\..\Code\External\Avernakis\Code\Avernakis-Property\MsBuild\Avernakis-Compiler.exe
set AC=_Tool\Avernakis-Compiler.exe

set ICSIZELIST=16 24 32 48 64 96 128
set ICNOECHO=1

set ResFolder=AppRes

rem set ResFolder=%ResFolder% 
