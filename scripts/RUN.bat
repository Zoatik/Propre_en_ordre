@echo off
:while
set /p FILE=File name : 
PEO.exe test_files/%FILE%.txt
set /p CONTINUE=lire un autre fichier ? (O/N) : 
echo -------------------------------------------
echo:
if /i "%CONTINUE%" == "O" (
	goto :while
)
PAUSE