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
    void render(Scene& myScene, Camera& myCamera);
    void close();
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;
protected:
private:
};

#endif
