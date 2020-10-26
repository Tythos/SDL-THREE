/*
*/

#ifndef MY_RENDERER_H
#define MY_RENDERER_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
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
    const int _screenWidth = 640;
    const int _screenHeight = 480;
    SDL_Window* _window = NULL;
    SDL_GLContext _context;
private:
};

#endif
