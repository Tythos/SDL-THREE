/*
*/

#include "Shader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader() {
    mProgramID = NULL;
    mVertexPos2DLocation = 0;
    mMultiColorLocation = 0;
    mProjectionMatrixLocation = 0;
    mModelviewMatrixLocation = 0;
}

Shader::~Shader() {
    freeProgram();
}

void Shader::freeProgram() {
    glDeleteProgram(mProgramID);
}

bool Shader::bind() {
    glUseProgram(mProgramID);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error binding shader! %s\n", gluErrorString(error));
        printProgramLog(mProgramID);
        return false;
    }
    return true;
}

void Shader::unbind() {
    glUseProgram(NULL);
}

GLuint Shader::getProgramID() {
    return mProgramID;
}

void Shader::printProgramLog(GLuint program) {
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

void Shader::printShaderLog(GLuint shader) {
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

bool Shader::loadProgram() {
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
    mMultiColorLocation = glGetAttribLocation(mProgramID, "aMultiColor");
    if (mMultiColorLocation == -1) {
        printf("%s is not a valid GLSL program variable!\n", "aMultiColor");
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
    return true;
}

GLuint Shader::loadShaderFromFile(std::string path, GLenum shaderType) {
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

void Shader::setProjection(glm::mat4 matrix) {
    mProjection = matrix;
}

void Shader::setModelview(glm::mat4 matrix) {
    mModelview = matrix;
}

void Shader::leftMultProjection(glm::mat4 matrix) {
    mProjection = matrix * mProjection;
}

void Shader::leftMultModelview(glm::mat4 matrix) {
    mModelview = matrix * mModelview;
}

void Shader::updateProjection() {
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
}

void Shader::updateModelview() {
    glUniformMatrix4fv(mModelviewMatrixLocation, 1, GL_FALSE, glm::value_ptr(mModelview));
}

void Shader::setVertexPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::setColorPointer(GLsizei stride, const GLvoid* data) {
    glVertexAttribPointer(mMultiColorLocation, 4, GL_FLOAT, GL_FALSE, stride, data);
}

void Shader::enableVertexPointer() {
    glEnableVertexAttribArray(mVertexPos2DLocation);
}

void Shader::disableVertexPointer() {
    glDisableVertexAttribArray(mVertexPos2DLocation);
}

void Shader::enableColorPointer() {
    glEnableVertexAttribArray(mMultiColorLocation);
}

void Shader::disableColorPointer() {
    glDisableVertexAttribArray(mMultiColorLocation);
}
