//
// Created by holly on 16/03/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include <SDL2/SDL_image.h>

class Player {
    /*
     * Generic player class. Expand as needed. Contains instance of Entity class
     */
    int team = 0;
    int health = 100;
    float maxSpeed = 1;
public:
    Entity entity{nullptr, 0, 0, 10, 10};
    Player(int team, float x, float y, SDL_Texture *texture = nullptr);
};


#endif //PLAYER_H
