@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
cl.exe /Fo:"obj/" /nologo /EHsc /I"../SDL2_image-2.0.5" /I"../glew-2.1.0/include" /I"../SDL2-2.0.12/include" /I"../glm-0.9.9.8" /c Camera.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../SDL2_image-2.0.5" /I"../glew-2.1.0/include" /I"../SDL2-2.0.12/include" /I"../glm-0.9.9.8" /c Scene.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../SDL2_image-2.0.5" /I"../glew-2.1.0/include" /I"../SDL2-2.0.12/include" /I"../glm-0.9.9.8" /c Renderer.cpp
cl.exe /Fo:"obj/" /nologo /EHsc /I"../SDL2_image-2.0.5" /I"../glew-2.1.0/include" /I"../SDL2-2.0.12/include" /I"../glm-0.9.9.8" /c main.cpp
