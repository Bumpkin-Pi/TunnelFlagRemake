//
// Created by holly on 16/03/24.
//

#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <sstream>

#include "loadTextures.h"
#include "io/keyboard.h"
#include "io/renderer.h"
#include "game/map.h"
#include "game/player.h"
#include "network/client.h"
extern int screenWidth;
extern int screenHeight;

/*
Game; contains all client side game logic.
Should include:
 - Entity position and velocity updates
 - Local player actions and UI
 - Basic interactions with external network class
Should generally be under the control of the server, with little actual gameplay logic.
*/
class Game {

    Textures textures{};
    int selfID = -1;

public:
    // Map of all players.
    std::unordered_map<int, Player> playerMap;
    Map map{0, 0};
    Renderer::Renderer renderer{0, 0, 1, screenWidth, screenHeight, 60};
    Client client{}; // Network manager

    Game();
    ~Game();

    // Get player from playerMap by ID. Returns pointer to player.
    Player* getPlayerByID(int id);
    // Adds a plyer to playerMap, with provided ID.
    void addPlayerByID(int id, Player player);
    // Removes a player with given ID from playerMap
    void removePlayerByID(int id);
    // Processes indevidual lines of packets
    void processPacketLine(const std::string& packetLine);
    // Processes a full string of packet lines
    void processPacketString(const std::string& packet);
    // Updates player position etc based on keyboard input.
    void processKeyboard(Keyboard::KeyboardInput keyboard);
    // Currently just updates all player positiones based on their velocity
    void playerUpdate();
    // Full tick update. Should be run 60 times a second.
    void gameTick();



};



#endif //GAME_H
