//
// Created by holly on 16/03/24.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "game/game.h"

extern bool debugOutput;
extern bool closing;

Game::Game() {
    map = Map(250, 500);
    textures = LoadTextures(renderer.renderer); // Loads textures from textures folder
    renderer.textures = &textures; // Janky as balls :).
//    addPlayerByID(selfID, Player{1, 0, 0, textures.player1, "uwuslayer123"}); // Debug players.
//    addPlayerByID(22, Player{2, 100, 50, textures.player2, "I am very cool"});
}
Game::~Game() { UnloadTextures(textures); }


Player *Game::getPlayerByID(int id) {
    auto player = playerMap.find(id);
    if (player != playerMap.end()) {
        return &(player->second); // First/Second instead of key/value for some reason.
    }
    return nullptr; // This needs better error catching
}
Player *Game::getSelfPlayer() {
    return selfPlayer;
}
void Game::removePlayerByID(int id) {
    auto player = playerMap.find(id);
    if (player != playerMap.end()) {
        playerMap.erase(player);
    } else if (debugOutput) { std::cout << "Failed to remove player by ID: " << id << "\n"; }
}
void Game::addPlayerByID(int id, Player player) {
    playerMap.emplace(id, player);
}
void Game::playerUpdate() {
    for (auto &pair: playerMap) {
        pair.second.update();
    }
}

void Game::processPacketLine(const std::string &packetLine) {
    if (packetLine == "") return;
    std::cout << packetLine << std::endl;
    std::istringstream iss(packetLine);
    std::vector<std::string> values;
    while (iss.good()) {
        std::string substr;
        std::getline(iss, substr, ',');
        values.push_back(substr);
    }
    switch (std::stoi(values[0])) {
        case 0: {                                                               // CONNECT: 0, UUID, team, x,y, idk what else
            selfID = std::stoi(values[1]);
            addPlayerByID(selfID, Player(std::stoi(values[2]), 0, 0, textures.player1, "MyUsername"));
            selfPlayer = getPlayerByID(selfID);
            break;
        }
        case 1: {                                                               // NEWPLAYERJOIN: 1, UUID, team, username
            int uuid = std::stoi(values[1]);
            int team = std::stoi(values[2]);
            addPlayerByID(uuid, Player{team, 0, 0, team == 1 ? textures.player1 : textures.player2, values[3]});
            break;
        }
        case 2: {                                                               // GAMEINIT: 2, idfk, teams n such ig.
            break;
        }
        case 3: {                                                               // MAPUPDATE: 3, map stuff.
            break;
        }
        case 4: {                                                               // PLAYERMOVE: 4, UUID, x,y, vx,vy
            int uuid = std::stoi(values[1]);
            float x = std::stof(values[2]), y = std::stof(values[3]);
//            float vx = std::stof(values[2]), vy = std::stof(values[3]);   // I havn't the faintest idea why this causes ghosting
            getPlayerByID(uuid)->setPos(x, y);
//            getPlayerByID(uuid)->setVelocity(vx, vy);
            break;
        }
        case 5: {                                                               // PLAYERMESSAGE: 5, UUID, message
            int uuid = std::stoi(values[1]);
            std::cout << getPlayerByID(uuid)->getUsername() << ": " << values[2] << std::endl;
            break;
        }
        case 6: {                                                               // PLAYERDISSCONECT: 6, UUID
            removePlayerByID(std::stoi(values[1]));
            break;
        }
        default: {
            std::cout << "Unknown packet line detected: " << packetLine << std::endl;
        }
    }
}
void Game::processPacketString() {
    std::unique_lock<std::mutex> recvLock(client.recvMutex);
    std::string packet = client.recvBuffer;
    client.recvBuffer = "";
    recvLock.unlock();
    if (packet == "") return;
    std::vector<std::string> lines;
    std::stringstream iss(packet);
    std::string SingleLine;
    while (iss.good()) {
        getline(iss, SingleLine, '\n');
        lines.push_back(SingleLine);
    }

    // Do shit with first line for verification;
//    lines.erase(lines.begin()); // Remove first line, currently not used.

    for (const std::string &line: lines) {
        if (!line.empty()) processPacketLine(line);
    }
}

void Game::processKeyboard(Keyboard::KeyboardInput keyboard) {
    // Might be smart to just store the getPlayerByID(selfID) pointer rather than rerunning it every time
    float playerSpeed = 3;
    if (selfID == -1) return;
    // Zoom control.
    if (keyboard.isUpScroll()) {
        renderer.zoomOut();             //This whole movement system should probably be reworked
    } else if (keyboard.isDownScroll()) { renderer.zoomIn(); }
    // Movement
    if (keyboard.getState(keyboard.keybinds.PlayerUp)) {
        selfPlayer->setVelocityY(-playerSpeed);; // Move up
    } else if (keyboard.getState(keyboard.keybinds.PlayerDown)) {
        selfPlayer->setVelocityY(playerSpeed);; // Move down
    } else { selfPlayer->setVelocityY(0); } // No movement
    if (keyboard.getState(keyboard.keybinds.PlayerLeft)) {
        selfPlayer->setVelocityX(-playerSpeed); // Move left
    } else if (keyboard.getState(keyboard.keybinds.PlayerRight)) {
        selfPlayer->setVelocityX(playerSpeed); // Move right
    } else { selfPlayer->setVelocityX(0); } // No movement

    if (keyboard.isSpace()) {
        lockCameraToPlayer = !lockCameraToPlayer;
    }

    if (keyboard.isLeftClick()){
        breaking.breaking = true;
        breaking.x = renderer.pixelToRealX(keyboard.getMouseX())/map.getTileSize();
        breaking.y = renderer.pixelToRealY(keyboard.getMouseY())/map.getTileSize();
    }
    if (keyboard.isLeftClickHeld()){
        breaking.breaking = true;
//        std::cout << "Breaking " << breaking.x << "," << breaking.y << "- " << breaking.timer << "- "<< (int) (renderer.pixelToRealX(keyboard.getMouseX())/map.getTileSize() - 1)  << "," << (int) (renderer.pixelToRealY(keyboard.getMouseY())/map.getTileSize() - 1) << "\n";
        if (breaking.x == (int) (renderer.pixelToRealX(keyboard.getMouseX())/map.getTileSize()) && breaking.y == (int) (renderer.pixelToRealY(keyboard.getMouseY())/map.getTileSize())){
            breaking.timer++;
        }else{
            breaking.x = keyboard.getMouseX()/map.getTileSize();
            breaking.y = keyboard.getMouseY()/map.getTileSize();
            breaking.timer = 0;
        }
    }else{
        breaking.breaking = false;
        breaking.timer = 0;
    }

}

void Game::gameTick() {
    // Keyboard processing happens in main.cpp.
    // Deal with packet buffer.
    playerUpdate();
    processPacketString(); // Take packet from buffer and process them.
    client.addToSendBuffer("1,"+ std::to_string(selfPlayer->getPosx())+","+std::to_string(getPlayerByID(selfID)->getPosy())+","+std::to_string(getPlayerByID(selfID)->getVelocityX())+","+std::to_string(getPlayerByID(selfID)->getVelocityY())+"\n");
    if (lockCameraToPlayer){
        renderer.setCameraPos(selfPlayer->getPosx(), selfPlayer->getPosy());
    }
    if (breaking.breaking && breaking.timer >= 60){
        breakTile(breaking.y, breaking.x);
        breaking.timer = 0;
    }
}

void Game::setTile(int row, int col, short value) { map.setValue(row, col, value); }
void Game::setTiles(const std::vector<int[2]>& tiles, short value) {
    for (auto& tile : tiles) setTile(tile[0], tile[1], value);
}
void Game::breakTile(int row, int col) {map.setValue(row, col, 0);}
void Game::breakTiles(const std::vector<int[2]> &tiles) {
    for (auto& tile : tiles) breakTile(tile[0], tile[1]);
}



