//
// Created by holly on 16/03/24.
//

#include "player.h"

#include <utility>

Player::Player(int team, float x, float y, SDL_Texture* texture, std::string username) : team(team), username(std::move(username)) {
    entity.setWidthAndHeight(50, 50);
    entity.setPos(x, y);
    entity.setSprite(texture);
}