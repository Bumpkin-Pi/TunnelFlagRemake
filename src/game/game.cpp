//
// Created by holly on 16/03/24.
//

#include <iostream>

#include "game.h"
#include "../io/renderer.h"
extern bool debugOutput;

Game::Game(){
    map = Map(100, 100);
    textures = LoadTextures(renderer.renderer); // Loads textures from textures folder
    addPlayerByID(selfID, Player{1, 50, 50, textures.player1, "uwuslayer123"}); // Debug players.
    addPlayerByID(22, Player{1, 100, 50, textures.player2, "I am very cool"});
}
Game::~Game() {UnloadTextures(textures);} // For some reason, when I bother to delete the textures, it gets angry at me, so idk.



Player *Game::getPlayerByID(int id) {
    auto player = playerMap.find(id);
    if (player != playerMap.end()) {
        return &(player->second); // First/Second instead of key/value for some reason.
    }
    return nullptr;
}
void Game::removePlayerByID(int id) {
    auto player = playerMap.find(id);
    if (player != playerMap.end()) {
        playerMap.erase(player);
    }else if(debugOutput) {std::cout << "Failed to remove player by ID: " << id << "\n";}
}
void Game::addPlayerByID(int id, Player player) {
    playerMap.emplace(id, player);
}

void Game::clientUpdate() {
    for (auto& pair : playerMap) {
        pair.second.update();
    }
}


void Game::processSubpacket(const std::string& subpacketLine) {
    std::istringstream iss(subpacketLine);
    std::string packetType;
    std::getline(iss, packetType, ':');

    if (packetType == "PLAYERMESSAGE") {
        // Parse player message subpacket
        std::string idStr, message;
        std::getline(iss, idStr, ',');
        std::getline(iss, message);

        int id = std::stoi(idStr);
        Player* player = getPlayerByID(id);
        if (player) {
            std::cout << "Player " << player->getUsername() << " says: " << message << std::endl;
        } else {
            if (debugOutput) {std::cerr << "Player with ID " << id << " not found." << std::endl;}
        }
    } else if (packetType == "PLAYERMOVE") {
        // Parse player move subpacket
        int id;
        float x, y, vx, vy;
        char comma;
        iss >> id >> comma >> x >> comma >> y >> comma >> vx >> comma >> vy;


        Player* player = getPlayerByID(id);
        if (player) {
            if (debugOutput) {
                std::cout << "Player " << player->getUsername() << " moved to ("
                      << x << ", " << y << ") with velocity (" << vx << ", " << vy << ")" << std::endl;
            }
            player->setPos(x, y);
            player->setVelocityX(vx); // TODO: Proper getters and setters for velocity, as well as username.
            player->setVelocityY(vy);
        } else {
            if (debugOutput) {std::cerr << "Player with ID " << id << " not found." << std::endl;}
        }
    } else {
        std::cerr << "Unknown packet type: " << packetType << std::endl;
    }
}
void Game::processPacketLines(const std::string& packetLines) {
    std::istringstream iss(packetLines);
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            processSubpacket(line);
        }
    }
}

void Game::processKeyboard(Keyboard::KeyboardInput keyboard) {
    // Might be smart to just store the getPlayerByID(selfID) pointer rather than rerunning it every time

    if (keyboard.isUpScroll()) {renderer.zoomOut();             //This whole movement system should probably be reworked
    } else if (keyboard.isDownScroll()) {renderer.zoomIn();}
    if (keyboard.getState(keyboard.keybinds.PlayerUp)) {getPlayerByID(selfID)->setVelocityY(-1);; // Move up
    } else if (keyboard.getState(keyboard.keybinds.PlayerDown)) {getPlayerByID(selfID)->setVelocityY(1);; // Move down
    } else {getPlayerByID(selfID)->setVelocityY(0);} // No movement
    if (keyboard.getState(keyboard.keybinds.PlayerLeft)) {getPlayerByID(selfID)->setVelocityX(-1); // Move left
    } else if (keyboard.getState(keyboard.keybinds.PlayerRight)) {getPlayerByID(selfID)->setVelocityX(1); // Move right
    } else {getPlayerByID(selfID)->setVelocityX(0);} // No movement
    if (keyboard.getState(keyboard.keybinds.cameraToPlayer)) {
        renderer.setCameraPos(getPlayerByID(selfID)->getPosx(), getPlayerByID(selfID)->getPosy());
    }

}

