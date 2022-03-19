@echo off
cd /d "%~dp0"
call _Command\Common.cmd

%AC% @_Command\BuildMesh.txt

pause
