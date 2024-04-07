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
    SDL_Texture* map0000;
    SDL_Texture* map0001;
    SDL_Texture* map0010;
    SDL_Texture* map0011;
    SDL_Texture* map0100;
    SDL_Texture* map0101;
    SDL_Texture* map0110;
    SDL_Texture* map0111;
    SDL_Texture* map1000;
    SDL_Texture* map1001;
    SDL_Texture* map1010;
    SDL_Texture* map1011;
    SDL_Texture* map1100;
    SDL_Texture* map1101;
    SDL_Texture* map1110;
    SDL_Texture* map1111;
};

// Loads textures into memory. Textures should be added to this and Textures struct manually.
Textures LoadTextures(SDL_Renderer *renderer);
// Unloads textures from memory
void UnloadTextures(Textures textures);



#endif //LOADTEXTURES_H
