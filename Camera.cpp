/*
*/

#include "Camera.h"

Camera::Camera() {
    /*
    */
    _projectionMatrixLocation = 0;
}

Camera::~Camera() {
    /*
    */
}

void Camera::setProjection(glm::mat4 matrix) {
    _projection = matrix;
}

void Camera::leftMultProjection(glm::mat4 matrix) {
    _projection = matrix * _projection;
}

void Camera::updateProjection() {
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(_projection));
}

void Camera::assertProjection(GLuint programID, int screenWidth, int screenHeight) {
    if (_projectionMatrixLocation == 0) {
        _projectionMatrixLocation = glGetUniformLocation(programID, "uProjection");
    }
    setProjection(glm::ortho<GLfloat>(0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0));
    updateProjection();
}
