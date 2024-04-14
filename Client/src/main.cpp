#include <iostream>
#include <thread>
#include <chrono>
#include <random>

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

// Debug functions for testing map ----
short generateRandomValue() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<short> dist(0, 1); // Adjust range as needed
    return dist(gen);
}
void randomizeMapValues(Map& map) {
    for (int row = 0; row < map.getRows(); ++row) {
        for (int col = 0; col < map.getColumns(); ++col) {
            if ((col == 0 || col == map.getColumns() - 1) || (row == 0 || row == map.getRows() - 1)){
                map.setValue(row, col, 1);
            }else{
                map.setValue(row, col, generateRandomValue());
            }
        }
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

    std::thread physicsThread(&physicsThreadFunction);

    const std::string packet = "PLAYERMESSAGE:22,Hello world\n"
                                "PLAYERMOVE:22,34,678.7,-1,0";
    game.processPacketLines(packet);
    randomizeMapValues(game.map);
    while (!closing) {
        game.renderer.render(game.map);
    }
    physicsThread.join();
    return 0;
}

