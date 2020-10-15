/*
*/

#include "Shader.h"
#include <fstream>

Shader::Shader() {
    mProgramID = NULL;
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
    /*GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShaderSource[] = {
        "void main() { gl_Position = gl_Vertex; }"
    };
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);*/
    GLuint vertexShader = loadShaderFromFile("bin/poly.v.glsl", GL_VERTEX_SHADER);
    if (vertexShader == 0) {
        glDeleteProgram(mProgramID);
        mProgramID = 0;
        return false;
    }
    glAttachShader(mProgramID, vertexShader);
    /*GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fragmentShaderSource[] = {
        "void main() { gl_FragColor = vec4( 0.2, 0.4, 0.8, 1.0 ); }"
    };
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);*/
    GLuint fragmentShader = loadShaderFromFile("bin/poly.f.glsl", GL_FRAGMENT_SHADER);
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
