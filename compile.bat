@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/sdl2-2.0.12/include" /I"../../SDL/SDL2_image-2.0.5" /c main.cpp
