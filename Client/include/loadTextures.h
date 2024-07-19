//
// Created by holly on 13/03/24.
//

#ifndef LOADTEXTURES_H
#define LOADTEXTURES_H
#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#else
#endif
// Struct for all texture pointers.
struct Textures {
    SDL_Texture* player1;
    SDL_Texture* player2;
//    SDL_Texture* background;
    SDL_Texture* mapTexturesSingle[16];
//    SDL_Texture* mapTextures[65536];
};

// Loads textures into memory. Textures should be added to this and Textures struct manually.
Textures LoadTextures(SDL_Renderer *renderer);
// Unloads textures from memory
void UnloadTextures(Textures textures);

// Combine a 2x2 map tile into a 3x3 map tiles. titlePixels refers to the pixel dimension of a single 2x2 tile.
SDL_Texture* CombineTexture(SDL_Renderer *renderer, SDL_Texture* topLeft, SDL_Texture* topRight, SDL_Texture* bottomLeft, SDL_Texture* bottomRight, int tilePixels);


#endif //LOADTEXTURES_H
