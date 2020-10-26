Nice starting template for command-line SDL/OpenGL/GLSL projects. Largely based on one of the better templates outlined at https://www.willusher.io/pages/sdl2/, but with a heavy dose of my own experience/experimentation and significant time spent developing in THREE.js

Compile stage assumes the following %INCLUDE% paths:
* glew headers at "../glew-2.1.0/include"
* glm headers at "../glm-0.9.9.8"
* SDL2 headers at "../../sdl2-2.0.12/include"
* SDL2_image headers at "../SDL2_image-2.0.5"

Link stage assumes SDL2 static libraries at "../../SDL2-2.0.12/lib" (using the subfolder x86 for 32-bit, x64 for 64-bit)
* glew libraries at "../glew-2.1.0/lib/x86"
* SDL2 libraries at "../SDL2-2.0.12/lib/x86"
* SDL2_image libraries at "../SDL2_image-2.0.5/lib/x86"

The link stage also links against the following, which should be in your system's %LIB% paths:
* OpenGL32.lib
* GlU32.lib
* shell32.lib

Execution assumes the following dynamic libraries in the "bin/" folder:
* glew32d.dll
* libpng16-16.dll
* SDL2_image.dll
* SDL2.dll
* zlib1.dll
