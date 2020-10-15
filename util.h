/*
*/

#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include "App.h"

bool init(App& myApp);
bool initGL(App& myApp);
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);

#endif
