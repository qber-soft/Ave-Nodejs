@echo off
cd /d "%~dp0"
call _Command\Common.cmd

call _Tool\Clean.cmd %ResFolder%

pause
