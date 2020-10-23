/*
*/

#ifndef SDLTHREE_SCENE_H
#define SDLTHREE_SCENE_H

#include "Mesh.h"

// The following structs are placeholders for more robust vertex attribute management within the Geometry class
struct VertexXYZ {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
struct VertexUV {
    GLfloat u;
    GLfloat v;
};
struct VertexRGB {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};
struct VertexNorm {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
struct VertexFormat {
    VertexXYZ xyz;
    VertexUV uv;
};

class Scene : public Mesh {
public:
    Scene();
    ~Scene();
    void setVertexPointers();
    GLuint hVBO = 0; // technically NULL would be more obvious, but also implies type mismatch
    GLuint hIBO = 0;
protected:
private:
};

#endif
