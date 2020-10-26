/**
 * A renderer is a (theoretically) stateless process by which a scene graph and
 * camera/display states are used to generate a new rasterized display buffer.
 * In this case, that takes the 
 */
  
#ifndef MY_RENDERER_H
#define MY_RENDERER_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Logger.h"
#include "Camera.h"
#include "Scene.h"

class Renderer {
public:
    Renderer();
    ~Renderer();
    bool init();
    void render(Scene* myScene, Camera* myCamera);
    void close();
protected:
    const int _screenWidth = 800;
    const int _screenHeight = 450;
    SDL_Window* _window = NULL;
    SDL_GLContext _context;
private:
};

#endif
