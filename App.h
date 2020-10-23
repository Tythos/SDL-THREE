/*
*/

#ifndef MY_APP_H
#define MY_APP_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <SDL_image.h>
#include "Mesh.h"

class App {
public:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    SDL_Window* gWindow = NULL;
    SDL_GLContext gContext;
    bool gRenderQuad = true;
    GLuint gProgramID = 0;
    GLint gVertexPos2DLocation = -1;
    GLuint gVBO = 0;
    GLuint gIBO = 0;
    Mesh myMesh;
    GLuint _textureId;
    void loadTexture(std::string path);
};

#endif
