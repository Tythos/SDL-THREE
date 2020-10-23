/*
*/

#include "Material.h"

Material::Material() {
    mProgramID = NULL;
    mVertexPos2DLocation = 0;
    mTexCoordLocation = 0;
    mProjectionMatrixLocation = 0;
    mModelviewMatrixLocation = 0;
    mTextureUnitLocation = 0;
}

Material::~Material() {
    /*
    */
    freeProgram();
}

void Material::freeProgram() {
    /*
    */
    if (0 < this->mProgramID) {
        glDeleteProgram(this->mProgramID);
        this->mProgramID = 0;
    }
}

bool Material::bind() {
    /*
    */
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

void Material::unbind() {
    /*
    */
    disableTexCoordPointer();
    disableVertexPointer();
    glBindTexture(GL_TEXTURE_2D, NULL);
    glUseProgram(NULL);
}

GLuint Material::getProgramID() {
    /*
    */
    return mProgramID;
}

void Material::printProgramLog(GLuint program) {
    /*
    */
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

void Material::printShaderLog(GLuint shader) {
    /*
    */
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

bool Material::loadProgram() {
    /*
    */
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
        printf("error linking program %d!\n", mProgramID);
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
        printf("%s is not a valid GLSL vertex attribute!\n", "aPos2D");
        return false;
    }
    mTexCoordLocation = glGetAttribLocation(mProgramID, "aTexCoord");
    if (mTexCoordLocation == -1) {
        printf("%s is not a valid GLSL vertex attribute!\n", "aTexCoord");
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

GLuint Material::loadShaderFromFile(std::string path, GLenum shaderType) {
    /*
    */
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
        if (shaderCompiled != GL_FALSE) {
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

void Material::setProjection(glm::mat4 matrix) {
    mProjection = matrix;
}

void Material::setModelview(glm::mat4 matrix) {
    mModelview = matrix;
}

void Material::leftMultProjection(glm::mat4 matrix) {
    mProjection = matrix * mProjection;
}

void Material::leftMultModelview(glm::mat4 matrix) {
    mModelview = matrix * mModelview;
}

void Material::updateProjection() {
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
}

void Material::updateModelview() {
    glUniformMatrix4fv(mModelviewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelview));
}

void Material::setVertexPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Material::setTexCoordPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mTexCoordLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Material::setTextureUnit(GLuint unit) {
    glUniform1i(mTextureUnitLocation, unit);
}

void Material::enableVertexPointer() {
    glEnableVertexAttribArray(mVertexPos2DLocation);
}

void Material::disableVertexPointer() {
    glDisableVertexAttribArray(mVertexPos2DLocation);
}

void Material::enableTexCoordPointer() {
    glEnableVertexAttribArray(mTexCoordLocation);
}

void Material::disableTexCoordPointer() {
    glDisableVertexAttribArray(mTexCoordLocation);
}

void Material::loadTexture(std::string path) {
    /*
    */
    SDL_Surface* surface = IMG_Load(path.c_str());
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
    printf("texture %u, surface formats bbp: %u\n", mTextureID, surface->format->BytesPerPixel);
}
