#include <iostream>
#include <thread>
#include <chrono>

#include "keyboard.h"
#include "renderer.h"
#include "entity.h"

// Init vars
int screenWidth = 1680;
int screenHeight = 1050;

bool closing = false;               // Variable to change to close game, all threads should check this variable to close.

Keyboard::KeyboardInput keyboardInput;
Renderer::Renderer renderer(0, 0, 1, screenWidth, screenHeight, 60);


void physicsThreadFunction() {
    constexpr int targetFrameTime = 1000 / 60; // 60 frames per second
    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!closing) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFrameTime).count();

        if (elapsedTime < targetFrameTime) {
            std::this_thread::sleep_for(std::chrono::milliseconds(targetFrameTime - elapsedTime));
        }

        // Update logic
        renderer.player1.update();
        keyboardInput.update();
        if (keyboardInput.isUpScroll()) {
            renderer.zoomOut();
        } else if (keyboardInput.isDownScroll()) {
            renderer.zoomIn();
        }
        if (keyboardInput.isKeyDown(keyboardInput.keybinds.playerKeybinds.up)) {
            renderer.player1.velocityY = -1; // Move up
        } else if (keyboardInput.isKeyDown(keyboardInput.keybinds.playerKeybinds.down)) {
            renderer.player1.velocityY = 1; // Move down
        } else {
            renderer.player1.velocityY = 0; // No movement
        }
        if (keyboardInput.isKeyDown(keyboardInput.keybinds.playerKeybinds.left)) {
            renderer.player1.velocityX = -1; // Move left
        } else if (keyboardInput.isKeyDown(keyboardInput.keybinds.playerKeybinds.right)) {
            renderer.player1.velocityX = 1; // Move right
        } else {
            renderer.player1.velocityX = 0; // No movement
        }

        // Update last frame time
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
}



int main()
{
    std::cout << "\nStarting TunnelFlag...\n";
    renderer.init();





    std::thread physicsThread(&physicsThreadFunction);


    while (!closing) {
        renderer.render();
    }
    physicsThread.join();
    return 0;
}
