/* Because this will become an "OpenGLRenderer", we focus on initializing the
   OpenGL API here. However, it is the Camera responsible for defining the
   rendering target, including window and context.
*/

#include "Renderer.h"

Renderer::Renderer() {
    /*
    */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    gContext = SDL_GL_CreateContext(gWindow);
    if (gContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
    }
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }
    int swapResult = SDL_GL_SetSwapInterval(1);
    if (swapResult < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }
}

Renderer::~Renderer() {
    /*
    */
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();
}

void Renderer::render(Scene& myScene, Camera& myCamera) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (myScene.gRenderQuad) {
        myScene.bind(myScene._textureId); {
            // update projection matrix from camera, modelview matrix from scene
            myCamera.mProjectionMatrixLocation = glGetUniformLocation(myScene.mProgramID, "uProjection");
            myCamera.setProjection(glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0));
            myCamera.updateProjection();
            myScene.setModelview(glm::translate<GLfloat>(glm::vec3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f)));
            myScene.updateModelview(); {
                glBindBuffer(GL_ARRAY_BUFFER, myScene.gVBO);
                myScene.setVertexPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, pos));
                myScene.setTexCoordPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, uv));
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myScene.gIBO);
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
            }
        } myScene.unbind();
    }
    SDL_GL_SwapWindow(gWindow);
}

void Renderer::close() {
    /*
    */
}
