#include <iostream>
#include <thread>
#include <chrono>

#include "io/keyboard.h"
#include "game/game.h"

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

        game.clientUpdate();
        game.processKeyboard(keyboardInput);
        // Update logic
        keyboardInput.update();

        // Update last frame time
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
}


int main(int argc, char* argv[]) {
    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--debug" || arg == "-d") { // Rules with debug output need to be done in a more set way
            debugOutput = true;
        }
    }

    // renderer.setPlayerMapPtr(&game.playerMap);
    std::cout << "\nStarting TunnelFlag...\n";

    std::thread physicsThread(&physicsThreadFunction);

    const std::string packet = "PLAYERMESSAGE:22,Hello world\n"
                                "PLAYERMOVE:22,34,678.7,-1,0";
    game.processPacketLines(packet);
    while (!closing) {
        game.renderer.render(game.map.map);
    }
    physicsThread.join();
    return 0;
}
