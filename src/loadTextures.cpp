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
#include <iostream>

Textures LoadTextures(SDL_Renderer *renderer) {
    Textures textures{};
    textures.player1 = IMG_LoadTexture(renderer, "../textures/player1.png"); //TODO: Add error correction and better expandability to this
    textures.player2 = IMG_LoadTexture(renderer, "../textures/player2.png");

    // Load map textures
    textures.map0000 = IMG_LoadTexture(renderer, "../textures/squares/0000.png");
    textures.map0001 = IMG_LoadTexture(renderer, "../textures/squares/0001.png");
    textures.map0010 = IMG_LoadTexture(renderer, "../textures/squares/0010.png");
    textures.map0011 = IMG_LoadTexture(renderer, "../textures/squares/0011.png");
    textures.map0100 = IMG_LoadTexture(renderer, "../textures/squares/0100.png");
    textures.map0101 = IMG_LoadTexture(renderer, "../textures/squares/0101.png");
    textures.map0110 = IMG_LoadTexture(renderer, "../textures/squares/0110.png");
    textures.map0111 = IMG_LoadTexture(renderer, "../textures/squares/0111.png");
    textures.map1000 = IMG_LoadTexture(renderer, "../textures/squares/1000.png");
    textures.map1001 = IMG_LoadTexture(renderer, "../textures/squares/1001.png");
    textures.map1010 = IMG_LoadTexture(renderer, "../textures/squares/1010.png");
    textures.map1011 = IMG_LoadTexture(renderer, "../textures/squares/1011.png");
    textures.map1100 = IMG_LoadTexture(renderer, "../textures/squares/1100.png");
    textures.map1101 = IMG_LoadTexture(renderer, "../textures/squares/1101.png");
    textures.map1110 = IMG_LoadTexture(renderer, "../textures/squares/1110.png");
    textures.map1111 = IMG_LoadTexture(renderer, "../textures/squares/1111.png");

    return textures;
}

void UnloadTextures(Textures textures) {
    SDL_DestroyTexture(textures.player1);
    SDL_DestroyTexture(textures.player2);

    // Destroy Map textures.
    SDL_DestroyTexture(textures.map0000);
    SDL_DestroyTexture(textures.map0001);
    SDL_DestroyTexture(textures.map0010);
    SDL_DestroyTexture(textures.map0011);
    SDL_DestroyTexture(textures.map0100);
    SDL_DestroyTexture(textures.map0101);
    SDL_DestroyTexture(textures.map0110);
    SDL_DestroyTexture(textures.map0111);
    SDL_DestroyTexture(textures.map1000);
    SDL_DestroyTexture(textures.map1001);
    SDL_DestroyTexture(textures.map1010);
    SDL_DestroyTexture(textures.map1011);
    SDL_DestroyTexture(textures.map1100);
    SDL_DestroyTexture(textures.map1101);
    SDL_DestroyTexture(textures.map1110);
    SDL_DestroyTexture(textures.map1111);
}
