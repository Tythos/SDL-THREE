SDL-THREE
=========

Nice starting template for command-line SDL/OpenGL/GLSL projects. Largely based
on one of the better templates outlined at https://www.willusher.io/pages/sdl2/
but with a heavy dose of my own experience/experimentation and significant time
spent developing THREE.js applications.

The compile stage assumes the following %INCLUDE% paths:

* glew headers at "../glew-2.1.0/include"
* glm headers at "../glm-0.9.9.8"
* SDL2 headers at "../../sdl2-2.0.12/include"
* SDL2_image headers at "../SDL2_image-2.0.5"

Link stage assumes static libraries at the following paths (using the subfolder
x86 for 32-bit, x64 for 64-bit, but feel free to customize):

* glew libraries at "../glew-2.1.0/lib/x86"
* SDL2 libraries at "../SDL2-2.0.12/lib/x86"
* SDL2_image libraries at "../SDL2_image-2.0.5/lib/x86"

This stage also links against the following, which should be in your system's
%LIB% paths:

* OpenGL32.lib
* GlU32.lib
* shell32.lib

Execution assumes the following dynamic libraries in the "bin/" folder:

* glew32d.dll
* libpng16-16.dll
* SDL2_image.dll
* SDL2.dll
* zlib1.dll

Other file dependencies include the GLSL shaders and the texture file, which
should be at the top level of this project already:

* poly.v.glsl
* poly.f.glsl
* image.png

The top-level "build.bat" script will clean, compile, link, and run the test
application. This assumes "cl.exe" and "link.exe" are on the system path. Note
that Git will (as specified in .gitignore) ignore contents of bin/ and obj/
folders.
