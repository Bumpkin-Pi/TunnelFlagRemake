//
// Created by holly on 13/03/24.
//

#ifndef LOADTEXTURES_H
#define LOADTEXTURES_H
#include <SDL2/SDL.h>

// Struct for all texture pointers.
struct Textures {
    SDL_Texture* player1;
    SDL_Texture* player2;
    SDL_Texture* background;
};

// Loads textures into memory. Textures should be added to this and Textures struct manually.
Textures LoadTextures(SDL_Renderer *renderer);
// Unloads textures from memory
void UnloadTextures(Textures textures);



#endif //LOADTEXTURES_H
