/*
*/

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;

void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

void cleanup(SDL_Texture* foreground, SDL_Renderer* renderer, SDL_Window* window) {
    if (foreground) { SDL_DestroyTexture(foreground); }
    if (renderer) { SDL_DestroyRenderer(renderer); }
    if (window) { SDL_DestroyWindow(window); }
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture == nullptr) {
        logSDLError(std::cout, "LoadTexture");
    }
    return texture;
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip=nullptr) {
    SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip=nullptr) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    if (clip != nullptr) {
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
        SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
    renderTexture(tex, ren, dst, clip);
}

int main(int, char**) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cout, "CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* image = loadTexture("bin/image.png", renderer);
    if (image == nullptr) {
        cleanup(image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    int iW = 100;
    int iH = 100;
    int x = 0.5 * (SCREEN_WIDTH - iW);
    int y = 0.5 * (SCREEN_HEIGHT - iH);
    SDL_Rect clips[4];
    for (int i = 0; i < 4; ++i) {
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }
    int useClip = 0;

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1: {
                        useClip = 0;
                        break;
                    }
                    case SDLK_2: {
                        useClip = 1;
                        break;
                    }
                    case SDLK_3: {
                        useClip = 2;
                        break;
                    }
                    case SDLK_4: {
                        useClip = 3;
                        break;
                    }
                    case SDLK_ESCAPE: {
                        quit = true;
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        SDL_RenderClear(renderer);
        renderTexture(image, renderer, x, y, &clips[useClip]);
        SDL_RenderPresent(renderer);
    }

    // close down
    cleanup(image, renderer, window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}