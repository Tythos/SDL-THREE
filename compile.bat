@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/SDL2_image-2.0.5" /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /I"../../SDL/glm-0.9.9.8" /c App.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/SDL2_image-2.0.5" /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /I"../../SDL/glm-0.9.9.8" /c Shader.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../../SDL/SDL2_image-2.0.5" /I"../../SDL/glew-2.1.0/include" /I"../../SDL/sdl2-2.0.12/include" /I"../../SDL/glm-0.9.9.8" /c main.cpp
