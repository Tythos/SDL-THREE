/*
*/

#include <SDL.h>
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include "util.h"
#include "App.h"

void handleKeys(unsigned char key, int x, int y);
void update();
void render();
void close();

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
        glUseProgram(myApp.gProgramID);
        glEnableVertexAttribArray(myApp.gVertexPos2DLocation);
        glBindBuffer(GL_ARRAY_BUFFER, myApp.gVBO);
        glVertexAttribPointer(myApp.gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.gIBO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
        glDisableVertexAttribArray(myApp.gVertexPos2DLocation);
        glUseProgram(NULL);
    }
}

void close(App& myApp) {
    glDeleteProgram(myApp.gProgramID);
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
            SDL_GL_SwapWindow(myApp.gWindow);
        }
        SDL_StopTextInput();
    }
    close(myApp);
    return 0;
}
