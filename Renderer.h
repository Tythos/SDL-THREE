/* A renderer is responsible for generating a new display buffer for a specific
   display device context. Right now this is a generic renderer, focusing on
   SDL/OpenGL. Multiple renderer implementations may be supported in the future
   for alternate rendering configurations (e.g., Vulkan; IMGUI; etc.). When (or
   before) that happens, it will make sense to rename this to something like
   "SdlOglRenderer" and, perhaps, define an abstract base Renderer class.
*/

#ifndef SDLTHREE_RENDERER_H
#define SDLTHREE_RENDERER_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include "Camera.h"
#include "Scene.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    void render(Scene* scene, Camera* camera);
protected:
    int screenWidth; // states should probably belong to the camera, and window/context could be encapsulated in a seperate render() parameter for something like "display device"
    int screenHeight;
    SDL_Window* window;
    SDL_GLContext* context;
private:
};

#endif
