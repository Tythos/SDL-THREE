/*
*/

#include "Scene.h"

Scene::Scene() {
    // define initial geometry for testing
    VertexFormat vertices[4];
    // lower-left
    vertices[0].xyz.x = -1.0f;
    vertices[0].xyz.y = -1.0f;
    vertices[0].xyz.z = 0.0f;
    vertices[0].rgb.r = 0.0f;
    vertices[0].rgb.g = 0.0f;
    vertices[0].rgb.b = 0.0f;
    // lower-right
    vertices[1].xyz.x = 1.0f;
    vertices[1].xyz.y = -1.0f;
    vertices[1].xyz.z = 0.0f;
    vertices[1].rgb.r = 1.0f;
    vertices[1].rgb.g = 0.0f;
    vertices[1].rgb.b = 0.0f;
    // upper-right
    vertices[2].xyz.x = 1.0f;
    vertices[2].xyz.y = 1.0f;
    vertices[2].xyz.z = 0.0f;
    vertices[2].rgb.r = 1.0f;
    vertices[2].rgb.g = 1.0f;
    vertices[2].rgb.b = 0.0f;
    // upper-left
    vertices[3].xyz.x = -1.0f;
    vertices[3].xyz.y = 1.0f;
    vertices[3].xyz.z = 0.0f;
    vertices[3].rgb.r = 0.0f;
    vertices[3].rgb.g = 1.0f;
    vertices[3].rgb.b = 0.0f;

    // bind data to vertex buffer object
    glGenBuffers(1, &this->hVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->hVBO);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(VertexFormat), vertices, GL_STATIC_DRAW);

    // define index buffer for a pair of right-handed triangles
    GLuint indices[6];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;

    // bind data to index buffer object
    glGenBuffers(1, &this->hIBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->hIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

Scene::~Scene() {

}
