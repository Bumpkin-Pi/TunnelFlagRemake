//
// Created by holly on 13/03/24.
//

#include "loadTextures.h"
#include <SDL2/SDL_image.h>
#include <iostream>

// struct Textures {
//     SDL_Texture* player1;
//     SDL_Texture* player2;
//     SDL_Texture* background;
// };



Textures LoadTextures(SDL_Renderer *renderer) {
    Textures textures{};
    textures.player1 = IMG_LoadTexture(renderer, "textures/player1.png"); //TODO: Add error correction and better expandability to this
    textures.player2 = IMG_LoadTexture(renderer, "textures/player2.png");
    textures.background = IMG_LoadTexture(renderer, "textures/background.png");

    return textures;
}
