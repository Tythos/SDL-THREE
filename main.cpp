/*
*/

#include <SDL.h>
#include <stdio.h>
#include <string>

#include "App.h"
#include "Renderer.h"

// global function prototypes
void handleKeys(App&, unsigned char, int, int);
void update();

void handleKeys(App& myApp, unsigned char key, int x, int y) {
    if (key == 'q') {
        myApp.myMesh.gRenderQuad= !myApp.myMesh.gRenderQuad;
    }
}

void update() {
    //
}

int main(int nArgs, char** vArgs) {
    App myApp;
    Renderer myRenderer;
    if (!myRenderer.init(myApp)) {
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
            myRenderer.render(myApp);
        }
        SDL_StopTextInput();
    }
    myRenderer.close(myApp);
    return 0;
}
