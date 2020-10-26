/*
*/

#include <SDL.h>
#include <stdio.h>

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"

void handleKeys(Scene& myScene, unsigned char key, int x, int y) {
    if (key == 'q') {
        myScene.gRenderQuad= !myScene.gRenderQuad;
    }
}

void update() {
    //
}

int main(int nArgs, char** vArgs) {
    Scene myScene;
    Camera myCamera;
    Renderer myRenderer;
    myScene.init();
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
                handleKeys(myScene, e.text.text[0], x, y);
            }
        }
        myRenderer.render(myScene, myCamera);
    }
    SDL_StopTextInput();
    myRenderer.close();
    return 0;
}
