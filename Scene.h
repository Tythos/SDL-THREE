/*
*/

#ifndef MY_SCENE_H
#define MY_SCENE_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <glm/glm.hpp>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <SDL_image.h>

// convenient 2d point storage
struct Pos2D {
    GLfloat x;
    GLfloat y;
};
struct ColorRGBA {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};
struct MultiColorVertex2D { // aggregate final vertex format
    Pos2D pos;
    Pos2D uv;
};

class Scene {
public:
    Scene();
    ~Scene();
    bool loadProgram();
    void freeProgram();
    bool bind(GLuint mTextureID);
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
    void printProgramLog(GLuint program);
    void printShaderLog(GLuint shader);
    void loadTexture(std::string path);
    void createGlBindings();
    bool getIsVisible();
    void setIsVisible(bool);
    GLuint getTextureId();
    GLuint getProgramId();
    GLuint getVboId();
    GLuint getIboId();
protected:
    GLuint _programID;
    GLint _vertexPos2DLocation;
    GLint _texCoordLocation;
    GLint _textureUnitLocation;
    glm::mat4 _modelview;
    GLint _modelviewMatrixLocation;
    bool _isVisible;
    GLuint _vbo;
    GLuint _ibo;
    GLuint _textureId;
    bool _isGlBound;
private:
};

#endif
