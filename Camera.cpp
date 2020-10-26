/*
*/

#include "Camera.h"

Camera::Camera() {
    /*
    */
    mProjectionMatrixLocation = 0;
}

Camera::~Camera() {
    /*
    */
}

void Camera::setProjection(glm::mat4 matrix) {
    mProjection = matrix;
}

void Camera::leftMultProjection(glm::mat4 matrix) {
    mProjection = matrix * mProjection;
}

void Camera::updateProjection() {
    glUniformMatrix4fv(mProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(mProjection));
}

void Camera::assertProjection(GLuint programID, int screenWidth, int screenHeight) {
    if (mProjectionMatrixLocation == 0) {
        mProjectionMatrixLocation = glGetUniformLocation(programID, "uProjection");
    }
    setProjection(glm::ortho<GLfloat>(0.0, screenWidth, screenHeight, 0.0, 1.0, -1.0));
    updateProjection();
}
