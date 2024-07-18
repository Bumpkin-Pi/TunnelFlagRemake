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
bool debugOutput = false;           // Needs better implementation. That's a problem for later me.

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

void clientListenThreadFunction(){
    game.client.listener(); // Sit listening for packets from server.
}
void clientSenderThreadFunction(){
    constexpr int targetSendTime = 1000 / 30; // 30 frames per second
    auto lastSendTime = std::chrono::high_resolution_clock::now();
    while (!closing) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastSendTime).count();
        if (elapsedTime < targetSendTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(targetSendTime - elapsedTime));
        }

        game.client.send(); // Send packets and flush buffer.

        // Update last frame time
        lastSendTime = std::chrono::high_resolution_clock::now();
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
    randomizeMapValues(game.map);
    game.client.connect("localhost", 42342);

    std::cout << "\nStarting TunnelFlag...\n";
    SDL_Init(SDL_INIT_EVERYTHING);
    std::thread physicsThread(&physicsThreadFunction);
    std::thread clientListenThread(&clientListenThreadFunction);
    std::thread clientSenderThread(&clientSenderThreadFunction);

//    const std::string packet = "1, 100, 2, hiImANewPlayer, 0, 0.1\n 4, 100, 50, 0, 0, 4\n5, 100, Hello world";
//    game.processPacketString(packet);

    while (!closing) {
        game.renderer.render(game.map);
    }
    physicsThread.join();
//    std::terminate();
    clientSenderThread.join();
    clientListenThread.join();
    return 0;
}

