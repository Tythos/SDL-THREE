/*
*/

#include "Renderer.h"

bool Renderer::init(App& myApp) {
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

bool Renderer::initGL(App& myApp) {
    bool success = true;

    // load mesh
    success = myApp.myMesh.loadProgram();
    if (!success) {
        printf("Mesh initialization failed");
        return false;
    }

    // define vertices buffer
    MultiColorVertex2D quadVertices[4];
    quadVertices[0].pos.x = -50.0f;
    quadVertices[0].pos.y = -50.0f;
    quadVertices[0].uv.x = 0.0f;
    quadVertices[0].uv.y = 0.0f;
    quadVertices[1].pos.x = 50.0f;
    quadVertices[1].pos.y = -50.0f;
    quadVertices[1].uv.x = 1.0f;
    quadVertices[1].uv.y = 0.0f;
    quadVertices[2].pos.x = 50.0f;
    quadVertices[2].pos.y = 50.0f;
    quadVertices[2].uv.x = 1.0f;
    quadVertices[2].uv.y = 1.0f;
    quadVertices[3].pos.x = -50.0f;
    quadVertices[3].pos.y = 50.0f;
    quadVertices[3].uv.x = 0.0f;
    quadVertices[3].uv.y = 1.0f;
    glGenBuffers(1, &myApp.myMesh.gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, myApp.myMesh.gVBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(MultiColorVertex2D), quadVertices, GL_STATIC_DRAW);

    // define index buffer
    GLuint indices[4];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    glGenBuffers(1, &myApp.myMesh.gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.myMesh.gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // load texture
    myApp.myMesh.loadTexture("bin/image.png"); // also assigns GL texture ID to _textureId

    // initialize mesh's shader uniforms
    myApp.myMesh.bind(myApp.myMesh._textureId); {
        myApp.myMesh.setProjection(glm::ortho<GLfloat>(0.0, myApp.SCREEN_WIDTH, myApp.SCREEN_HEIGHT, 0.0, 1.0, -1.0));
        myApp.myMesh.updateProjection();
        myApp.myMesh.setModelview(glm::mat4());
        myApp.myMesh.updateModelview();
        myApp.myMesh.setTextureUnit(0);
    } myApp.myMesh.unbind();

    return success;
}

void Renderer::render(App& myApp) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (myApp.myMesh.gRenderQuad) {
        myApp.myMesh.bind(myApp.myMesh._textureId); {
            myApp.myMesh.setModelview(glm::translate<GLfloat>(glm::vec3(myApp.SCREEN_WIDTH / 2.0f, myApp.SCREEN_HEIGHT / 2.0f, 0.0f)));
            myApp.myMesh.updateModelview(); {
                glBindBuffer(GL_ARRAY_BUFFER, myApp.myMesh.gVBO);
                myApp.myMesh.setVertexPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, pos));
                myApp.myMesh.setTexCoordPointer(sizeof(MultiColorVertex2D), (GLvoid*)offsetof(MultiColorVertex2D, uv));
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myApp.myMesh.gIBO);
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
            }
        } myApp.myMesh.unbind();
    }
    SDL_GL_SwapWindow(myApp.gWindow);
}

void Renderer::close(App& myApp) {
    glDeleteProgram(myApp.myMesh.getProgramID());
    SDL_DestroyWindow(myApp.gWindow);
    myApp.gWindow = NULL;
    SDL_Quit();
}
