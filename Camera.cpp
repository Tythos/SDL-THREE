/*
*/

#include "Camera.h"

/**
 * Initializes camera by zero-ing the projection matrix location.
 */
Camera::Camera() {
    _projectionMatrixLocation = 0;
}

/**
 * Currently no destruction tasks are required.
 */
Camera::~Camera() {
}

/**
 * Assigns a new projection matrix from the given glm::mat4 instance
 */
void Camera::setProjection(glm::mat4 matrix) {
    _projection = matrix;
}

/**
 * Applies a matrix to the current projection using a left-multiplication
 * operator
 */
void Camera::leftMultProjection(glm::mat4 matrix) {
    _projection = matrix * _projection;
}

/**
 * Writes current projection matrix values to the GLSL uniform location defined
 * by the _projectionMatrixLocation variable.
 */
void Camera::updateProjection() {
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(_projection));
}

/**
 * Given a specific GLSL program ID, ensures that the uniform location has been
 * extracted and sets the projection matrix values from an orthogonal
 * projection using the given screen dimensions. The uniform matrix values are
 * then updated by invocation of the updateProjection() method.
 */
void Camera::assertProjection(GLuint programID, int screenWidth, int screenHeight) {
    if (_projectionMatrixLocation == 0) {
        _projectionMatrixLocation = glGetUniformLocation(programID, "uProjection");
    }
    setProjection(glm::ortho<GLfloat>(0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0));
    updateProjection();
}
