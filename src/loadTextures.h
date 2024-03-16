//
// Created by holly on 13/03/24.
//

#ifndef LOADTEXTURES_H
#define LOADTEXTURES_H
#include <SDL2/SDL.h>

struct Textures {
    SDL_Texture* player1;
    SDL_Texture* player2;
    SDL_Texture* background;
};



Textures LoadTextures(SDL_Renderer *renderer);
Textures UnloadTextures(Textures textures);



#endif //LOADTEXTURES_H
