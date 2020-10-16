@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
set SDL_PATH=../../SDL
link.exe /nologo /SUBSYSTEM:CONSOLE /libpath:"%SDL_PATH%/SDL2_Image-2.0.5/lib/x86" /libpath:"%SDL_PATH%/glew-2.1.0/lib/x86" /libpath:"%SDL_PATH%/SDL2-2.0.12/lib/x86" /OUT:"bin/main.exe" SDL2.lib SDL2main.lib SDL2_image.lib OpenGL32.lib GLU32.lib glew32d.lib shell32.lib obj/App.obj obj/Shader.obj obj/main.obj
