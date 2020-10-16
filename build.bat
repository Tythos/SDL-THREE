@echo off
rem Runs all steps in build/ scripts
echo --- CLEANING ---
call build/clean.bat
echo --- COMPILING ---
call build/compile.bat
echo --- LINKING ---
call build/link.bat
echo --- RUNNING ---
call build/run.bat

