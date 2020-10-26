@echo off
rem Links .OBJ resources and .LIB dependencies using MSVC's command-line linker to generate a binary executable
if not exist .\bin (
    mkdir bin
    echo Binary artifact folder ".\bin" did not exist; I have created it...
    echo ...But you will still need to populate it with dynamic library dependencies
    echo (See README.rst for more details)
)
link.exe /nologo /SUBSYSTEM:CONSOLE /OUT:"bin/main.exe" ^
    /LIBPATH:"../glew-2.1.0/lib/x86" ^
    /LIBPATH:"../SDL2_image-2.0.5/lib/x86" ^
    /LIBPATH:"../SDL2-2.0.12/lib/x86" ^
    glew32d.lib ^
    OpenGL32.lib ^
    GlU32.lib ^
    SDL2.lib ^
    SDL2main.lib ^
    SDL2_image.lib ^
    shell32.lib ^
    obj/Scene.obj ^
    obj/Camera.obj ^
    obj/Renderer.obj ^
    obj/main.obj
