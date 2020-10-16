/*
*/

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "App.h"
#include "Shader.h"

// global function prototypes
bool init(App&);
bool initGL(App&);
void handleKeys(App&, unsigned char, int, int);
void update();
void render(App&);
void close(App&);

// convenient 2d point storage
struct Pos2D {
    GLfloat x;
    GLfloat y;
};
struct ColorRGBA {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};
struct MultiColorVertex2D{
    Pos2D pos;
    ColorRGBA rgba;
};

bool init(App& myApp) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        myApp.gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, myApp.SCREEN_WIDTH, myApp.SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (myApp.gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // renderer vs context?
            /*myApp.gRenderer = SDL_CreateRenderer(myApp.gWindow, 01, SDL_RENDERER_ACCELERATED);
            if (myApp.gRenderer == NULL) {
                printf("CreateRenderer error: %s\n", SDL_GetError());
                return false;
            }*/
            
            // continue with context
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            myApp.gContext = SDL_GL_CreateContext(myApp.gWindow);
            if (myApp.gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();
                if (glewError != GLEW_OK) {
                    printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
                }
                if (SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
                if (!initGL(myApp)) {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }
    return success;
}

bool initGL(App& myApp) {
    bool success = true;

    // load shader program
    success = myApp.myShader.loadProgram();
    if (!success) {
        printf("Shader initialization failed");
        return false;
    }

    // initialize matrices
    myApp.myShader.bind(); {
        myApp.myShader.setProjection(glm::ortho<GLfloat>(0.0, myApp.SCREEN_WIDTH, myApp.SCREEN_HEIGHT, 0.0, 1.0, -1.0));
        myApp.myShader.updateProjection();
        myApp.myShader.setModelview(glm::mat4());
        myApp.myShader.updateModelview();
    } myApp.myShader.unbind();

    // define vertices buffer
    MultiColorVertex2D quadVertices[4];
    quadVertices[0].pos.x = -50.0f;
    quadVertices[0].pos.y = -50.0f;
    quadVertices[0].rgba.r = 1.0f;
    quadVertices[0].rgba.g = 0.0f;
    quadVertices[0].rgba.b = 0.0f;
    quadVertices[0].rgba.a = 1.0f;
    quadVertices[1].pos.x = 50.0f;
    quadVertices[1].pos.y = -50.0f;
    quadVertices[1].rgba.r = 1.0f;
    quadVertices[1].rgba.g = 1.0f;
    quadVertices[1].rgba.b = 0.0f;
    quadVertices[1].rgba.a = 1.0f;
    quadVertices[2].pos.x = 50.0f;
    quadVertices[2].pos.y = 50.0f;
    quadVertices[2].rgba.r = 0.0f;
    quadVertices[2].rgba.g = 1.0f;
    quadVertices[2].rgba.b = 0.0f;
    quadVertices[2].rgba.a = 1.0f;
    quadVertices[3].pos.x = -50.0f;
    quadVertices[3].pos.y = 50.0f;
    quadVertices[3].rgba.r = 0.0f;
    quadVertices[3].rgba.g = 0.0f;
    quadVertices[3].rgba.b = 1.0f;
    quadVertices[3].rgba.a = 1.0f;
    glGenBuffers(1, &myApp.gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myApp.gVBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(MultiColorVertex2D), quadVertices, GL_STATIC_DRAW);

    // define index buffer
    GLuint indices[4];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    glGenBuffers(1, &myApp.gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // load texture
    myApp.loadTexture("bin/image.png");
    return success;
}

void handleKeys(App& myApp, unsigned char key, int x, int y) {
    if (key == 'q') {
        myApp.gRenderQuad= !myApp.gRenderQuad;
    }
}

void update() {
    //
}

void render(App& myApp) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (myApp.gRenderQuad) {
        myApp.myShader.bind(); {
            myApp.myShader.setModelview(glm::translate<GLfloat>(glm::vec3(myApp.SCREEN_WIDTH / 2.0f, myApp.SCREEN_HEIGHT / 2.0f, 0.0f)));
            myApp.myShader.updateModelview();
            myApp.myShader.enableVertexPointer();
            myApp.myShader.enableColorPointer(); {
                glBindBuffer(GL_ARRAY_BUFFER, myApp.gVBO);
                myApp.myShader.setVertexPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, pos));
                myApp.myShader.setColorPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, rgba));
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.gIBO);
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
            }
            myApp.myShader.disableVertexPointer();
            myApp.myShader.disableColorPointer();
        } myApp.myShader.unbind();
    }
    SDL_GL_SwapWindow(myApp.gWindow);
}

void close(App& myApp) {
    glDeleteProgram(myApp.myShader.getProgramID());
    SDL_DestroyWindow(myApp.gWindow);
    myApp.gWindow = NULL;
    SDL_Quit();
}

int main(int nArgs, char** vArgs) {
    App myApp;
    if (!init(myApp)) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;
        SDL_StartTextInput();
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_TEXTINPUT)  {
                    int x = 0, y = 0;
                    SDL_GetMouseState(&x, &y);
                    handleKeys(myApp, e.text.text[0], x, y);
                }
            }
            render(myApp);
        }
        SDL_StopTextInput();
    }
    close(myApp);
    return 0;
}
