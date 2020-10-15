@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
link.exe /nologo /SUBSYSTEM:CONSOLE /libpath:"../../SDL/SDL2-2.0.12/lib/x86" /libpath:"../../SDL/SDL2_image-2.0.5/lib/x86" /libpath:"../../SDL/SDL2_ttf-2.0.15/lib/x86" /OUT:"bin/main.exe" SDL2.lib SDL2main.lib SDL2_image.lib SDL2_ttf.lib shell32.lib obj/main.obj
