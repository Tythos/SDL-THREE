@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
link.exe /nologo /SUBSYSTEM:CONSOLE /libpath:"../../SDL2-2.0.12/lib" /OUT:"bin/main.exe" SDL2.lib SDL2main.lib shell32.lib obj/main.obj
