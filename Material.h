/*
*/

#ifndef SDLTHREE_MATERIAL_H
#define SDLTHREE_MATERIAL_H

#include <istream>
#include <SDL.h>
#include <gl/glew.h>
#include <gl/GL.h>

class Material {
public:
    Material();
    ~Material();
    void loadProgram(std::istream v, std::istream f);
protected:
    GLuint programID;
private:
};

#endif
