//
// Created by holly on 16/03/24.
//

#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <SDL2/SDL.h>

#include "../loadTextures.h"
#include "player.h"



class Game {
    /*
     * ## Game; contains all client side game logic.
     * Should include:
     *  - Entity position and velocity updates
     *  - Local player actions and UI
     *  - Basic interactions with external network class
     * Should generally be under the control of the server, with little actual gameplay logic.
     */
    Textures textures;
    std::unordered_map<int, Player> playerMap;
    int selfID = 0;

public:
    Game(SDL_Renderer *renderer);
    Player* getPlayerByID(int id);
    Player* addPlayerByID(int id, Player player);
    Player* removePlayerByID(int id);

};



#endif //GAME_H
