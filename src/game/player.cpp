//
// Created by holly on 16/03/24.
//

#include "player.h"

#include <utility>

Player::Player(int team, float x, float y, SDL_Texture* texture, std::string username)
        : Entity(texture, x, y, 50, 50), team(team), username(std::move(username)) {
    setWidthAndHeight(50, 50);
    setPos(x, y);
    setSprite(texture);
}