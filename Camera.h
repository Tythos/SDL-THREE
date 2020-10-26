/* A Camera model captures the user view, including projection matrix. More
   detailed future implementations may also include things like dolly behaviors
   and specific control manipulations.
*/

#ifndef SDLTHREE_CAMERA_H
#define SDLTHREE_CAMERA_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logger.h"

class Camera {
public:
    Camera();
    ~Camera();
    void setProjection(glm::mat4 matrix);
    void leftMultProjection(glm::mat4 matrix);
    void updateProjection();
    void assertProjection(GLuint programID, int width, int height);
protected:
    glm::mat4 _projection;
    GLint _projectionMatrixLocation;
private:
};

#endif
