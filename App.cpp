/*
*/

#include "App.h"

/* After this function executes, a texture has been greated and pixel data
   mapped. The texture ID, however, still needs to be bound to the appropriate
   uniform1i, which is the shader's responsibility, when rendering takes place.
*/
void App::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, NULL);
    printf("texture %u, surface formats bbp: %u\n", _textureId, surface->format->BytesPerPixel);
}
