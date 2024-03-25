//
// Created by holly on 16/03/24.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#ifdef __linux__
#include <SDL2/SDL_image.h>
#elif _WIN32
#include <SDL_image.h>
#else
#endif
#include <string>

class Player : public Entity{
    /*
     * Generic player class. Expand as needed. Contains instance of Entity class
     */
    int team = 0;
    int health = 100;
    int maxHealth = 100;
    float maxSpeed = 1;
    std::string username;

public:

    Player(int team, float x, float y, SDL_Texture *texture, std::string username);


    std::string getUsername();                          // Getters
    int getHealth();
    int getTeam();
    int getMaxHealth();
    float getMaxSpeed();

    void setUsername(std::string username);             // Setters
    // Set health value; clamped between 0 and Player.maxHealth
    void setHealth(int health);
    // Changes health by value input. Clamped between 0 and Player.maxHealth
    void changeHealth(int healthChange);
    void setTeam(int team);
    void setMaxHealth(int maxHealth);
    void setMaxSpeed(float maxSpeed);

};


#endif //PLAYER_H
