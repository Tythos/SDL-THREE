@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../sdl2-2.0.12/include" /c main.cpp
