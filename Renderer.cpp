/* Because this will become an "OpenGLRenderer", we focus on initializing the
   OpenGL API here. However, it is the Camera responsible for defining the
   rendering target, including window and context.
*/

#include "Renderer.h"

Renderer::Renderer() {
    /*
    */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOGGER.informational("SDL could not initialize! SDL Error:");
        LOGGER.error(SDL_GetError());
    }
    _window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (_window == NULL) {
        LOGGER.informational("Window could not be created! SDL Error:");
        LOGGER.error(SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    _context = SDL_GL_CreateContext(_window);
    if (_context == NULL) {
        LOGGER.informational("OpenGL context could not be created! SDL Error:");
        LOGGER.error(SDL_GetError());
    }
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        LOGGER.informational("Error initializing GLEW! Error message:");
        LOGGER.error(SDL_GetError());
    }
    int swapResult = SDL_GL_SetSwapInterval(1);
    if (swapResult < 0) {
        LOGGER.informational("Warning: Unable to set VSync! SDL Error:");
        LOGGER.error(SDL_GetError());
    }
}

Renderer::~Renderer() {
    /*
    */
    SDL_DestroyWindow(_window);
    _window = NULL;
    SDL_Quit();
}

void Renderer::render(Scene* myScene, Camera* myCamera) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (myScene->getIsVisible()) {
        myScene->bind(myScene->getTextureId()); {
            // update projection matrix from camera, modelview matrix from scene
            myCamera->assertProjection(myScene->getProgramId(), _screenWidth, _screenHeight);
            myScene->setModelview(glm::translate<GLfloat>(glm::vec3(_screenWidth / 2.0f, _screenHeight / 2.0f, 0.0f)));
            myScene->updateModelview(); {
                glBindBuffer(GL_ARRAY_BUFFER, myScene->getVboId());
                myScene->setVertexPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, pos));
                myScene->setTexCoordPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, uv));
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myScene->getIboId());
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
            }
        } myScene->unbind();
    }
    SDL_GL_SwapWindow(_window);
}
