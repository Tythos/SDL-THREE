@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /c App.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /c Shader.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /c main.cpp
