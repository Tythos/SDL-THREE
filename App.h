/*
*/

#ifndef MY_APP_H
#define MY_APP_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include "Mesh.h"

class App {
public:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;
    Mesh myMesh;
};

#endif
