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
#include <glm/glm.hpp>

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
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a=1.0f);
    void setProjection(glm::mat4 matrix);
    void setModelview(glm::mat4 matrix);
    void leftMultProjection(glm::mat4 matrix);
    void leftMultModelview(glm::mat4 matrix);
    void updateProjection();
    void updateModelview();
protected:
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
    GLuint mProgramID;
    GLint mPolygonColorLocation;
    glm::mat4 mProjection;
    GLint mProjectionMatrixLocation;
    glm::mat4 mModelview;
    GLint mModelviewMatrixLocation;
};

#endif
