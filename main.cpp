/*
*/

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include "App.h"
#include "Shader.h"

// global function prototypes
bool init(App&);
bool initGL(App&);
void handleKeys(App&, unsigned char, int, int);
void update();
void render(App&);
void close(App&);

bool init(App& myApp) {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        myApp.gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, myApp.SCREEN_WIDTH, myApp.SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (myApp.gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
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
    success = myApp.myShader.loadProgram();
    if (!success) {
        printf("Shader initialization failed");
        return false;
    }
    /*glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    GLfloat vertexData[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };
    GLuint indexData[] = {0, 1, 2, 3};
    glGenBuffers(1, &myApp.gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myApp.gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
    glGenBuffers(1, &myApp.gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);*/
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
    glLoadIdentity();
    if (myApp.gRenderQuad) {
        myApp.myShader.bind();
        glTranslatef(myApp.SCREEN_WIDTH / 2.0f, myApp.SCREEN_HEIGHT / 2.0f, 0.0f);
        glBegin(GL_QUADS); {
            glColor3f(0.0f, 1.0f, 1.0f);
            glVertex2f(-0.5f, -0.5f);
            glVertex2f(0.5f, -0.5f);
            glVertex2f(0.5f, 0.5f);
            glVertex2f(-0.5f, 0.5f);
        } glEnd();
        myApp.myShader.unbind();
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
