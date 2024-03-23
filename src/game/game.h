//
// Created by holly on 16/03/24.
//

#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <SDL2/SDL.h>
#include <iostream>
#include <sstream>

#include "../loadTextures.h"
#include "../io/keyboard.h"
#include "../io/renderer.h"
#include "player.h"
extern int screenWidth;
extern int screenHeight;

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
    int selfID = 012;
    Renderer::Renderer renderer{0, 0, 1, screenWidth, screenHeight, 60};


public:
    std::unordered_map<int, Player> playerMap;

    Game();
    void init();
    void render();
    // ~Game();
    Player* getPlayerByID(int id);
    void addPlayerByID(int id, Player player);
    void removePlayerByID(int id);
    void processSubpacket(const std::string& subpacketLine);
    void processPacketLines(const std::string& packetLines);

    void processKeyboard(Keyboard::KeyboardInput keyboard);

    void clientUpdate();

};



#endif //GAME_H
