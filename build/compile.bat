@echo off
rem Compiles .CPP source to .OBJ resources using MSVC's command-line compiler
if not exist .\obj (
    mkdir obj
)
set INCLUDE_FLAGS= ^
    /I"../glew-2.1.0/include" ^
    /I"../glm-0.9.9.8" ^
    /I"../SDL2-2.0.12/include" ^
    /I"../SDL2_image-2.0.5"
cl.exe /Fo:"obj/" /nologo /EHsc %INCLUDE_FLAGS% /c Scene.cpp
cl.exe /Fo:"obj/" /nologo /EHsc %INCLUDE_FLAGS% /c Camera.cpp
cl.exe /Fo:"obj/" /nologo /EHsc %INCLUDE_FLAGS% /c Renderer.cpp
cl.exe /Fo:"obj/" /nologo /EHsc %INCLUDE_FLAGS% /c main.cpp
