@echo off

call Cleaner.bat
Vendor\bin\premake\premake5.exe --scripts=Vendor\bin\premake\scripts vs2022
pause