#include <iostream>
#include <thread>
#include <chrono>
#include <random>

#include "io/keyboard.h"
#include "game/game.h"
#include "debugFunctions.h"

int screenWidth = 1680;     // Determins starting screen resolution.
int screenHeight = 1050;

bool closing = false;               // Variable to change to close game, all threads should check this variable to close.
bool debugOutput = false;

Keyboard::KeyboardInput keyboardInput;
Game game;

void physicsThreadFunction() {
    constexpr int targetFrameTime = 1000 / 60; // 60 frames per second
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (!closing) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime).count();

        if (elapsedTime < targetFrameTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(targetFrameTime - elapsedTime));
        }

        game.gameTick();
        // Update logic
        keyboardInput.update();
        game.processKeyboard(keyboardInput);

        // Update last frame time
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
}


// -------------

int main(int argc, char* argv[]) {

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--debug" || arg == "-d") { // Rules with debug output need to be done in a more set way
            debugOutput = true;
        } 
    }

    std::cout << "\nStarting TunnelFlag...\n";
    SDL_Init(SDL_INIT_EVERYTHING);
    std::thread physicsThread(&physicsThreadFunction);

    const std::string packet = "1, 100, 2, hiImANewPlayer, 0, 0.1\n 4, 100, 50, 0, 0, 4\n5, 100, Hello world";
    game.processPacketString(packet);
    randomizeMapValues(game.map);
    while (!closing) {
        game.renderer.render(game.map);
    }
    physicsThread.join();
    return 0;
}

