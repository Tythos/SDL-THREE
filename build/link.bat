@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
link.exe /nologo /SUBSYSTEM:CONSOLE /OUT:"bin/main.exe" /LIBPATH:"../glew-2.1.0/lib/x86" /LIBPATH:"../SDL2-2.0.12/lib/x86" SDL2.lib SDL2main.lib shell32.lib OpenGL32.lib glew32d.lib obj/Camera.obj obj/Geometry.obj obj/Material.obj obj/Mesh.obj obj/Renderer.obj obj/Scene.obj obj/main.obj
