@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
link.exe /nologo /SUBSYSTEM:CONSOLE /libpath:"../../SDL/glew-2.1.0/lib/x86" /libpath:"../../SDL/SDL2-2.0.12/lib/x86" /OUT:"bin/main.exe" SDL2.lib SDL2main.lib OpenGL32.lib GLU32.lib glew32d.lib shell32.lib obj/main.obj obj/util.obj obj/App.obj
