/*
*/

#include "Scene.h"

Scene::Scene() {
    mProgramID = NULL;
    mVertexPos2DLocation = 0;
    mTexCoordLocation = 0;
    mProjectionMatrixLocation = 0;
    mModelviewMatrixLocation = 0;
    mTextureUnitLocation = 0;
}

void Scene::init() {
    // load mesh
    bool success = loadProgram();
    if (!success) {
        printf("Mesh initialization failed");
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
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(MultiColorVertex2D), quadVertices, GL_STATIC_DRAW);

    // define index buffer
    GLuint indices[4];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // load texture
    loadTexture("bin/image.png"); // also assigns GL texture ID to _textureId

    // initialize mesh's shader uniforms
    bind(_textureId); {
        setModelview(glm::mat4());
        updateModelview();
        setTextureUnit(0);
    } unbind();
}

Scene::~Scene() {
    freeProgram();
    glDeleteProgram(getProgramID());
}

void Scene::freeProgram() {
    glDeleteProgram(mProgramID);
}

bool Scene::bind(GLuint mTextureID) {
    glUseProgram(mProgramID);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader! %s\n", gluErrorString(error));
        printProgramLog(mProgramID);
        return false;
    }
    enableVertexPointer();
    enableTexCoordPointer();
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    return true;
}

void Scene::unbind() {
    disableTexCoordPointer();
    disableVertexPointer();
    glBindTexture(GL_TEXTURE_2D, NULL);
    glUseProgram(NULL);
}

GLuint Scene::getProgramID() {
    return mProgramID;
}

void Scene::printProgramLog(GLuint program) {
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

void Scene::printShaderLog(GLuint shader) {
    if (glIsShader(shader)) {
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            printf("%s\n", infoLog);
        }
        delete[] infoLog;
    } else {
        printf("Name %d is not a shader\n", shader);
    }
}

bool Scene::loadProgram() {
    GLint programSuccess = GL_TRUE;
    mProgramID = glCreateProgram();
    GLuint vertexShader = loadShaderFromFile("poly.v.glsl", GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    glAttachShader(mProgramID, vertexShader);
    GLuint fragmentShader = loadShaderFromFile("poly.f.glsl", GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    glAttachShader(mProgramID, fragmentShader);
    glLinkProgram(mProgramID);
    glGetProgramiv(mProgramID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", mProgramID);
        printProgramLog(mProgramID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    mVertexPos2DLocation = glGetAttribLocation(mProgramID, "aPos2D");
    if (mVertexPos2DLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "aPos2D");
        return false;
    }
    mTexCoordLocation = glGetAttribLocation(mProgramID, "aTexCoord");
    if (mTexCoordLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "aTexCoord");
        return false;
    }
    mTextureUnitLocation = glGetUniformLocation(mProgramID, "uTextureUnit");
    if (mTextureUnitLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uTextureUnit");
        return false;
    }
    mProjectionMatrixLocation = glGetUniformLocation(mProgramID, "uProjection");
    if (mProjectionMatrixLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uProjection");
        return false;
    }
    mModelviewMatrixLocation = glGetUniformLocation(mProgramID, "uModelview");
    if (mModelviewMatrixLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uModelview");
        return false;
    }
    mTextureUnitLocation = glGetUniformLocation(mProgramID, "uTextureUnit");
    if (mTextureUnitLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uTextureUnit");
        return false;
    }
    return true;
}

GLuint Scene::loadShaderFromFile(std::string path, GLenum shaderType) {
    GLuint shaderID = 0;
    std::string shaderString;
    std::ifstream sourceFile(path.c_str());
    if (sourceFile) {
        shaderString.assign((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
        shaderID = glCreateShader(shaderType);
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);
        glCompileShader(shaderID);
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE) {
            printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, shaderSource);
            printShaderLog(shaderID);
            glDeleteShader(shaderID);
            shaderID = 0;
        }
    } else {
        printf("Unable to open file %s\n", path.c_str());
    }
    return shaderID;
}

void Scene::setProjection(glm::mat4 matrix) {
    mProjection = matrix;
}

void Scene::setModelview(glm::mat4 matrix) {
    mModelview = matrix;
}

void Scene::leftMultProjection(glm::mat4 matrix) {
    mProjection = matrix * mProjection;
}

void Scene::leftMultModelview(glm::mat4 matrix) {
    mModelview = matrix * mModelview;
}

void Scene::updateProjection() {
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
}

void Scene::updateModelview() {
    glUniformMatrix4fv(mModelviewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelview));
}

void Scene::setVertexPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Scene::setTexCoordPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Scene::setTextureUnit(GLuint unit) {
    glUniform1i(mTextureUnitLocation, unit);
}

void Scene::enableVertexPointer() {
    glEnableVertexAttribArray(mVertexPos2DLocation);
}

void Scene::disableVertexPointer() {
    glDisableVertexAttribArray(mVertexPos2DLocation);
}

void Scene::enableTexCoordPointer() {
    glEnableVertexAttribArray(mTexCoordLocation);
}

void Scene::disableTexCoordPointer() {
    glDisableVertexAttribArray(mTexCoordLocation);
}

void Scene::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
    printf("texture %u, surface formats bbp: %u\n", _textureId, surface->format->BytesPerPixel);
}
