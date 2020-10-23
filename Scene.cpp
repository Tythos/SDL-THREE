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
    vertices[0].uv.u = 0.0f;
    vertices[0].uv.v = 0.0f;
    // lower-right
    vertices[1].xyz.x = 1.0f;
    vertices[1].xyz.y = -1.0f;
    vertices[1].xyz.z = 0.0f;
    vertices[1].uv.u = 1.0f;
    vertices[1].uv.v = 0.0f;
    // upper-right
    vertices[2].xyz.x = 1.0f;
    vertices[2].xyz.y = 1.0f;
    vertices[2].xyz.z = 0.0f;
    vertices[2].uv.u = 1.0f;
    vertices[2].uv.v = 1.0f;
    // upper-left
    vertices[3].xyz.x = -1.0f;
    vertices[3].xyz.y = 1.0f;
    vertices[3].xyz.z = 0.0f;
    vertices[3].uv.u = 0.0f;
    vertices[3].uv.v = 1.0f;

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
    /*
    */
}

void Scene::setVertexPointers() {
    /*
    */
    this->material->setVertexPointer(sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, xyz));
    this->material->setTexCoordPointer(sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, uv));
}