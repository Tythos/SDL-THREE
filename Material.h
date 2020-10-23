/*
*/

#ifndef SDLTHREE_MATERIAL_H
#define SDLTHREE_MATERIAL_H

#include <istream>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <SDL_image.h>
#include <fstream>
#include "glm/gtc/type_ptr.hpp"

class Material {
public:
    Material();
    ~Material();
    bool loadProgram();
    void freeProgram();
    bool bind();
    void unbind();
    GLuint getProgramID();
    GLuint loadShaderFromFile(std::string path, GLenum shaderType);
    void setProjection(glm::mat4 matrix);
    void setModelview(glm::mat4 matrix);
    void leftMultProjection(glm::mat4 matrix);
    void leftMultModelview(glm::mat4 matrix);
    void updateProjection();
    void updateModelview();
    void setVertexPointer(GLsizei stride, const GLvoid* data);
    void setTexCoordPointer(GLsizei stride, const GLvoid* data);
    void enableVertexPointer();
    void disableVertexPointer();
    void enableTexCoordPointer();
    void disableTexCoordPointer();
    void setTextureUnit(GLuint unit);
    void loadTexture(std::string path);
protected:
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
    GLuint mProgramID;
    GLint mVertexPos2DLocation;
    GLint mTexCoordLocation;
    GLint mTextureUnitLocation;
    glm::mat4 mProjection;
    GLint mProjectionMatrixLocation;
    glm::mat4 mModelview;
    GLint mModelviewMatrixLocation;
    GLuint mTextureID;
private:
};

#endif
