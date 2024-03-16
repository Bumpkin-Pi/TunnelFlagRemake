//
// Created by holly on 16/03/24.
//

#include <iostream>

#include "game.h"
#include "../io/renderer.h"


Game::Game(SDL_Renderer *renderer) {
    textures = LoadTextures(renderer);
    addPlayerByID(selfID, Player{1, 50, 50, textures.player1});
    addPlayerByID(2, Player{1, 100, 50, textures.player2});
    // getPlayerByID(selfID)->entity.setSprite(textures.player1);
}
// Game::~Game() {UnloadTextures(textures);} // For some reason, when I bother to delete the textures, it gets angry at me, so idk.


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
    }else {
        std::cout << "Failed to remove player by ID: " << id << "\n";
    }
}
void Game::addPlayerByID(int id, Player player) {
    playerMap.emplace(id, player);
}

