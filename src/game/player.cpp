//
// Created by holly on 16/03/24.
//

#include "player.h"

Player::Player(int team, float x, float y, SDL_Texture *texture) : team(team) {
    entity.setPos(x, y);
    entity.setSprite(texture);
}