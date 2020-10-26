/*
*/

#ifndef MY_CAMERA_H
#define MY_CAMERA_H

#include <stdio.h>
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera();
    ~Camera();
    void setProjection(glm::mat4 matrix);
    void leftMultProjection(glm::mat4 matrix);
    void updateProjection();
    glm::mat4 mProjection;
    GLint mProjectionMatrixLocation;
protected:
private:
};

#endif
