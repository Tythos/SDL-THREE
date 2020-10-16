/*
*/

#include "App.h"

void App::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    printf("surface formats bbp: %u\n", surface->format->BytesPerPixel);
}
