/*
*/

#ifndef MY_SHADER_H
#define MY_SHADER_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();
    bool loadProgram();
    void freeProgram();
    bool bind();
    void unbind();
    GLuint getProgramID();
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
protected:
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
    GLuint mProgramID;
};

#endif
