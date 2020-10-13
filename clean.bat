@echo off
rem Removes build artifacts (object files, binary executables)
if exist obj\*.obj (
    del obj\*.obj
)
if exist bin\*.exe (
    del bin\*.exe
)
