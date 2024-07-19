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
    SDL_Texture* background;
    SDL_Texture* mapTextures[16];
};

// Loads textures into memory. Textures should be added to this and Textures struct manually.
Textures LoadTextures(SDL_Renderer *renderer);
// Unloads textures from memory
void UnloadTextures(Textures textures);



#endif //LOADTEXTURES_H
