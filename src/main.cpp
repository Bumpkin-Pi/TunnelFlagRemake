#include <iostream>
#include <thread>
#include "keyboard.h"
#include "renderer.h"

// Init vars
int screenWidth = 1680;
int screenHeight = 1050;

bool closing = false;               // Variable to change to close game, all threads should check this variable to close.

Keyboard::KeyboardInput keyboardInput;
Renderer::Renderer renderer(0, 0, 1, screenWidth, screenHeight, 60);

void physicsThreadFunction() {
    while (!closing) {
        keyboardInput.update();
    }}

int main()
{
    std::cout << "\nStarting TunnelFlag...\n";
    renderer.init();

    std::thread physicsThread(&physicsThreadFunction);


    while (!closing) {
        renderer.render();
    }
    physicsThread.join();
    renderer.destroy();
    return 0;
}
