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
#include "App.h"

class Renderer {
public:
    bool init(App& myApp);
    bool initGL(App& myApp);
    void render(App& myApp);
    void close(App& myApp);
protected:
private:
};

#endif
