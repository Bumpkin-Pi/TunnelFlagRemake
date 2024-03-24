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

// Getter functions
std::string Player::getUsername() {return username;}
int Player::getHealth() {return health;}
int Player::getTeam() {return team;}
int Player::getMaxHealth() {return maxHealth;}
float Player::getMaxSpeed() {return maxSpeed;}

// Setter functions
void Player::setUsername(std::string username) {this->username = std::move(username);}
void Player::setHealth(int health) {this->health = std::max(0, std::min(health, maxHealth));}
void Player::changeHealth(int healthChange) {this->health = std::max(0, std::min(this->health + healthChange, maxHealth));}
void Player::setTeam(int team) {this->team = team;}
void Player::setMaxHealth(int maxHealth) {this->maxHealth = maxHealth;}
void Player::setMaxSpeed(float maxSpeed) {this->maxSpeed = maxSpeed;}