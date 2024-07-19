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
    textures.player1 = IMG_LoadTexture(renderer, "../../Client/textures/player1.png"); //TODO: Add error correction and better expandability to this
    textures.player2 = IMG_LoadTexture(renderer, "../../Client/textures/player2.png");

    // Load map textures
    textures.mapTexturesSingle[0b0000] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0000.png");
    textures.mapTexturesSingle[0b0001] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0001.png");
    textures.mapTexturesSingle[0b0010] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0010.png");
    textures.mapTexturesSingle[0b0011] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0011.png");
    textures.mapTexturesSingle[0b0100] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0100.png");
    textures.mapTexturesSingle[0b0101] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0101.png");
    textures.mapTexturesSingle[0b0110] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0110.png");
    textures.mapTexturesSingle[0b0111] = IMG_LoadTexture(renderer, "../../Client/textures/squares/0111.png");
    textures.mapTexturesSingle[0b1000] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1000.png");
    textures.mapTexturesSingle[0b1001] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1001.png");
    textures.mapTexturesSingle[0b1010] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1010.png");
    textures.mapTexturesSingle[0b1011] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1011.png");
    textures.mapTexturesSingle[0b1100] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1100.png");
    textures.mapTexturesSingle[0b1101] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1101.png");
    textures.mapTexturesSingle[0b1110] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1110.png");
    textures.mapTexturesSingle[0b1111] = IMG_LoadTexture(renderer, "../../Client/textures/squares/1111.png");

    // Probably worth doing in future, but for now I think that larger tiles is an unnecessary optimisation.
//    for (int a = 0; a <= 0b1111; a++)for (int b = 0; b <= 0b1111; b++)for (int c = 0; c <= 0b1111; c++)for (int d = 0; d <= 0b1111; d++){
//        std::cout << ((a << 12) | (b << 8) | (c << 4) | d) << std::endl;
//        textures.mapTextures[(a << 12) | (b << 8) | (c << 4) | d] = CombineTexture(renderer, textures.mapTexturesSingle[a], textures.mapTexturesSingle[b], textures.mapTexturesSingle[c], textures.mapTexturesSingle[d], 50);
//    }

    return textures;
}

void UnloadTextures(Textures textures) {
    SDL_DestroyTexture(textures.player1);
    SDL_DestroyTexture(textures.player2);

    // Destroy Map textures.
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0000]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0001]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0010]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0011]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0100]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0101]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0110]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b0111]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1000]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1001]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1010]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1011]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1100]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1101]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1110]);
    SDL_DestroyTexture(textures.mapTexturesSingle[0b1111]);
}

SDL_Texture* CombineTexture(SDL_Renderer *renderer, SDL_Texture* topLeft, SDL_Texture* topRight, SDL_Texture* bottomLeft, SDL_Texture* bottomRight, int tilePixels){
    SDL_Texture* combinedTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, tilePixels * 3, tilePixels * 3);
    SDL_SetRenderTarget(renderer, combinedTexture);
    SDL_RenderClear(renderer);
    // Rectangle to draw with
    SDL_Rect destRect = {0,0,tilePixels,tilePixels};

    // Top left
    SDL_RenderCopy(renderer, topLeft, nullptr, &destRect);
    // Top-right
    destRect.x = tilePixels*2;
    SDL_RenderCopy(renderer, topLeft, nullptr, &destRect);
    // Bottom left
    destRect.x = 0;
    destRect.y = tilePixels*2;
    SDL_RenderCopy(renderer, topLeft, nullptr, &destRect);
    // Bottom right
    destRect.x = tilePixels*2;
    SDL_RenderCopy(renderer, topLeft, nullptr, &destRect);

    SDL_SetRenderTarget(renderer, nullptr);
    return combinedTexture;
}
