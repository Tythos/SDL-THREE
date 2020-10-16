/*
*/

#include "Scene.h"
#include "Camera.h"
#include "Renderer.h"

bool update() {
    SDL_Event event;
    SDL_StartTextInput();
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT: {
                return false;
                break;
            }
            case SDL_TEXTINPUT: {
                unsigned char key = event.text.text[0];
                switch (key) {
                    case 'q': {
                        return false;
                        break;
                    }
                }
            }
        }
    }
    SDL_StopTextInput();
    return true;
}

int main(int nArgs, char** vArgs) {
    // setup
    Scene* scene = new Scene();
    Camera* camera = new Camera();
    Renderer* renderer = new Renderer();
    bool isRunning = true;

    while (isRunning) {
        // updating
        isRunning = update();

        // rendering
        renderer->render(scene, camera);
    }

    // cleanup
    delete scene;
    delete camera;
    delete renderer;

    return 0;
}
