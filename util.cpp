/*
*/

#include "util.h"

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
    myApp.gProgramID = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShaderSource[] = {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE) {
        printf("Unable to compile vertex shader %d!\n", vertexShader);
        printShaderLog(vertexShader);
        success = false;
    } else {
        glAttachShader(myApp.gProgramID, vertexShader);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar* fragmentShaderSource[] = {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
        };
        glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
        if (fShaderCompiled != GL_TRUE) {
            printf("Unable to compile fragment shader %d!\n", fragmentShader);
            printShaderLog(fragmentShader);
            success = false;
        } else {
            glAttachShader(myApp.gProgramID, fragmentShader);
            glLinkProgram(myApp.gProgramID);
            GLint programSuccess = GL_TRUE;
            glGetProgramiv(myApp.gProgramID, GL_LINK_STATUS, &programSuccess);
            if (programSuccess != GL_TRUE) {
                printf("Error linking program %d!\n", myApp.gProgramID);
                printProgramLog(myApp.gProgramID);
                success = false;
            } else {
                myApp.gVertexPos2DLocation = glGetAttribLocation(myApp.gProgramID, "LVertexPos2D");
                if (myApp.gVertexPos2DLocation == -1) {
                    printf("LVertexPos2D is not a valid GLSL program variable!\n");
                    success = false;
                } else {
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
                }
            }
        }
    }
    return success;
}

void printProgramLog(GLuint program) {
    if (glIsProgram(program)) {
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            printf("%s\n", infoLog);
        }
        delete[] infoLog;
    } else {
        printf("Name %d is not a program\n", program);
    }
}

void printShaderLog(GLuint shader) {
    if (glIsShader(shader)) {
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            printf("%s\n", infoLog);
        }
    } else {
        printf("Name %d is not a shader\n", shader);
    }
}
