@ECHO OFF
set /p FILE="File name : "
PEO.exe test_files/%FILE%.txt
PAUSE