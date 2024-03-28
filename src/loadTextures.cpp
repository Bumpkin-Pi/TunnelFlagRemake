//
// Created by holly on 13/03/24.
//

#include "loadTextures.h"
#ifdef __linux__
#include <SDL2/SDL_image.h>
#elif _WIN32
#include <SDL_image.h>
#else
#endif

Textures LoadTextures(SDL_Renderer *renderer) {
    Textures textures{};
    textures.player1 = IMG_LoadTexture(renderer, "../textures/player1.png"); //TODO: Add error correction and better expandability to this
    textures.player2 = IMG_LoadTexture(renderer, "../textures/player2.png");
    // textures.background = IMG_LoadTexture(renderer, "../textures/background.png");
    return textures;
}

void UnloadTextures(Textures textures) {
    SDL_DestroyTexture(textures.player1);
    SDL_DestroyTexture(textures.player1);
    // SDL_DestroyTexture(textures.background);
}
