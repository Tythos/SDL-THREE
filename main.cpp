/*
*/

#include <SDL.h>

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"

void handleKeys(Scene* myScene, unsigned char key, int x, int y) {
    if (key == 'q') {
        myScene->setIsVisible(!myScene->getIsVisible());
    }
}

bool update(Scene* myScene) {
    //
    bool quit = false;
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        } else if (event.type == SDL_TEXTINPUT)  {
            int x = 0, y = 0;
            SDL_GetMouseState(&x, &y);
            handleKeys(myScene, event.text.text[0], x, y);
        }
    }
    return quit;
}

int main(int nArgs, char** vArgs) {
    LOGGER.informational("initializing...");
    Scene* myScene = new Scene();
    Camera* myCamera = new Camera();
    Renderer* myRenderer = new Renderer();

    LOGGER.informational("looping...");
    bool quit = false;
    SDL_StartTextInput();
    while (!quit) {
        quit = update(myScene);
        myRenderer->render(myScene, myCamera);
    }

    LOGGER.informational("shutting down...");
    SDL_StopTextInput();
    delete myRenderer;
    delete myCamera;
    delete myScene;
    return 0;
}
