/*
*/

#include "Renderer.h"
#include "Logger.h"
#include <glm/gtx/transform.hpp>

Renderer::Renderer() {
    int result = 0;
    this->screenWidth = 640;
    this->screenHeight = 480;

    // initialize SDL
    result = SDL_Init(SDL_INIT_VIDEO);
    if (result < 0) {
        LOGGER.informational("SDL could not be initialized");
        LOGGER.error(SDL_GetError());
    }

    // initialize a window
    this->window = SDL_CreateWindow("SDL:THREE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth, this->screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (this->window == NULL) {
        LOGGER.informational("SDL window could not be created");
        LOGGER.error(SDL_GetError());
    }

    // set/constrain OpenGL attributes before creating context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext ctx = SDL_GL_CreateContext(this->window);
    this->context = &ctx;
    if (this->context == NULL) {
        LOGGER.informational("OpenGL context could not be created from SDL window");
        LOGGER.error(SDL_GetError());
    }

    // configure GL extension wrangler (optional?)
    GLenum result1 = glewInit();
    int result2 = SDL_GL_SetSwapInterval(1);
    if (result1 != GLEW_OK || result2 < 0) {
        LOGGER.warning("Unable to configure OpenGL extension wrangler");
    }
}

Renderer::~Renderer() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Renderer::render(Scene* scene, Camera* camera) {
    /* Sets up a new rendering pass for the GPU, after which display buffers
       are swapped.
    */
    glClear(GL_COLOR_BUFFER_BIT);
    if (scene->isVisible) {
        scene->material->bind(); {
            scene->material->setModelview(glm::translate<GLfloat>(glm::vec3(screenWidth, screenHeight, 0)));
            scene->material->updateModelview();
            glBindBuffer(GL_ARRAY_BUFFER, scene->hVBO);
            scene->setVertexPointers();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scene->hIBO);
            glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, NULL);
        } scene->material->unbind();
    }
    SDL_GL_SwapWindow(this->window);
}
