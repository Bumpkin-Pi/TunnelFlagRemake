//
// Created by holly on 13/03/24.
//

#include "renderer.h"
#include "../game/game.h"

#include <iostream>
#include <chrono>
#include <thread>
extern bool closing;
extern Game game;

namespace Renderer {
    Renderer::Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS)
    : screenWidth(screenWidth), screenHeight(screenHeight) {
        camera.x = CameraX;
        camera.y = CameraY;
        camera.z = CameraZ;
        setMaxFPS(maxFPS);

        // Initialize SDL and create window/renderer
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_SetWindowTitle(window, "Tunnel Flag");


        // Load player texture
        SDL_Texture* texture = IMG_LoadTexture(renderer, "../textures/player1.png"); //TODO: fix relative dirs.
        if (!texture) {
            std::cerr << "Failed to load player texture: " << SDL_GetError() << std::endl;
            // Handle error
        }

    }
    void Renderer::init() {

    }

    Renderer::~Renderer() {
        std::cout << "Quitting SDL\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    void Renderer::render() {
        auto startTime = std::chrono::high_resolution_clock::now();

        frameCounter++;

        clearScreen();
        // Draw some shit idk

        renderPlayers();
        showScreen();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (elapsedTime < frameDelay) {std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - elapsedTime));}

        // if (frameCounter % 100 == 0) { // Average fps over 100 frames debug code.
        //     // Calculate FPS
        //     double fps = 100000.0 / (std::chrono::duration_cast<std::chrono::milliseconds>(endTime - HstartTime).count());
        //     std::cout << "FPS: " << fps << std::endl;
        //     HstartTime = std::chrono::high_resolution_clock::now();
        // }
    }

    void Renderer::renderPlayers() { // Loops through players and renders them all.
        for (auto& pair : game.playerMap) {
            pair.second.render(renderer, camera.x, camera.y, camera.z, screenWidth, screenHeight);
        }
    }


    void Renderer::clearScreen() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    void Renderer::showScreen() {
        SDL_RenderPresent(renderer);
    }


    // void Renderer::setPlayerMapPtr(std::unordered_map<int, Player> *playerMapPtr) {
    //     this->playerMapPtr = playerMapPtr;
    // }

    void Renderer::setCameraPos(float x, float y) {camera.x = x;camera.y = y;}
    void Renderer::setCameraZoom(float z) {
        if (z < zoomMax && z > zoomMin) {camera.z = z;}}
    void Renderer::setCameraPosAndZoom(float x, float y, float z) {camera.x = x;camera.y = y;camera.z = z;}
    void Renderer::setResolution(int x, int y) {screenWidth = x;screenHeight = y;}
    void Renderer::setMaxFPS(int maxFPS) {this->maxFPS = maxFPS; frameDelay = 1000 / maxFPS;}
    float Renderer::getCameraPosx() const {return camera.x;}
    float Renderer::getCameraPosy() const {return camera.y;}
    float Renderer::getCameraZoom() const {return camera.z;}
    int Renderer::getResolutionx() const {return screenWidth;}
    int Renderer::getResolutiony() const {return screenHeight;}
    int Renderer::getMaxFPS() const {return maxFPS;}


    void Renderer::zoomIn() {
        if (camera.z * 0.9 >= zoomMin) {
            camera.z *= 0.9;
        }
    }

    void Renderer::zoomOut() {
        if (camera.z * 1.11111 <= zoomMax) {
            camera.z *= 1.11111;
        }
    }
};