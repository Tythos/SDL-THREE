/*
*/

#include "Scene.h"

Scene::Scene() {
    _programID = NULL;
    _vertexPos2DLocation = 0;
    _texCoordLocation = 0;
    _modelviewMatrixLocation = 0;
    _textureUnitLocation = 0;
    _isGlBound = false;
    _vbo = 0;
    _ibo = 0;
    _isVisible = true;
}

bool Scene::getIsVisible() {
    return _isVisible;
}

void Scene::setIsVisible(bool _) {
    _isVisible = _;
}

GLuint Scene::getTextureId() {
    return _textureId;
}

GLuint Scene::getProgramId() {
    return _programID;
}

GLuint Scene::getVboId() {
    return _vbo;
}

GLuint Scene::getIboId() {
    return _ibo;
}

Scene::~Scene() {
    freeProgram();
    glDeleteProgram(getProgramID());
}

void Scene::freeProgram() {
    glDeleteProgram(_programID);
}

void Scene::createGlBindings() {
    /* we can't necessarily create things like buffer object handles at
       initialization, in case the renderer hasn't set up the GL context yet
       (calls will silently fail); so, we delay those actions until bind() is
       called, which checks to see if they've been created yet.
    */

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
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(MultiColorVertex2D), quadVertices, GL_STATIC_DRAW);

    // define index buffer
    GLuint indices[4];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 3;
    glGenBuffers(1, &_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    // load actual shader program
    bool success = loadProgram();
    if (!success) {
        printf("Mesh initialization failed");
    }

    // load texture, initialize uniforms
    loadTexture("image.png"); // also assigns GL texture ID to _textureId
    _isGlBound = true; // careful not to recurse
}

bool Scene::bind(GLuint mTextureID) {
    // check to see if the gl data has been bound yet
    if (!_isGlBound) {
        createGlBindings();
    }

    // continue using/binding handles
    glUseProgram(_programID);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader! %s\n", gluErrorString(error));
        printProgramLog(_programID);
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
    return _programID;
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
    _programID = glCreateProgram();
    GLuint vertexShader = loadShaderFromFile("poly.v.glsl", GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        glDeleteProgram(_programID);
        _programID = 0;
        return false;
    }
    glAttachShader(_programID, vertexShader);
    GLuint fragmentShader = loadShaderFromFile("poly.f.glsl", GL_FRAGMENT_SHADER);
    if (fragmentShader == 0) {
        glDeleteShader(vertexShader);
        glDeleteProgram(_programID);
        _programID = 0;
        return false;
    }
    glAttachShader(_programID, fragmentShader);
    glLinkProgram(_programID);
    glGetProgramiv(_programID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", _programID);
        printProgramLog(_programID);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(_programID);
        _programID = 0;
        return false;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    _vertexPos2DLocation = glGetAttribLocation(_programID, "aPos2D");
    if (_vertexPos2DLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "aPos2D");
        return false;
    }
    _texCoordLocation = glGetAttribLocation(_programID, "aTexCoord");
    if (_texCoordLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "aTexCoord");
        return false;
    }
    _textureUnitLocation = glGetUniformLocation(_programID, "uTextureUnit");
    if (_textureUnitLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uTextureUnit");
        return false;
    }
    _modelviewMatrixLocation = glGetUniformLocation(_programID, "uModelview");
    if (_modelviewMatrixLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "uModelview");
        return false;
    }
    _textureUnitLocation = glGetUniformLocation(_programID, "uTextureUnit");
    if (_textureUnitLocation == -1) {
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

void Scene::setModelview(glm::mat4 matrix) {
    _modelview = matrix;
}

void Scene::leftMultModelview(glm::mat4 matrix) {
    _modelview = matrix * _modelview;
}

void Scene::updateModelview() {
    glUniformMatrix4fv(_modelviewMatrixLocation, 1, GL_FALSE, glm::value_ptr(_modelview));
}

void Scene::setVertexPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Scene::setTexCoordPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(_texCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Scene::setTextureUnit(GLuint unit) {
    glUniform1i(_textureUnitLocation, unit);
}

void Scene::enableVertexPointer() {
    glEnableVertexAttribArray(_vertexPos2DLocation);
}

void Scene::disableVertexPointer() {
    glDisableVertexAttribArray(_vertexPos2DLocation);
}

void Scene::enableTexCoordPointer() {
    glEnableVertexAttribArray(_texCoordLocation);
}

void Scene::disableTexCoordPointer() {
    glDisableVertexAttribArray(_texCoordLocation);
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
