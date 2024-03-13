//
// Created by holly on 13/03/24.
//

#include "renderer.h"

#include <iostream>
#include <chrono>
#include <thread>

namespace Renderer {
    Renderer::Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS) {
        camera.x = CameraX;
        camera.y = CameraY;
        camera.z = CameraZ;
        this->screenWidth = screenWidth;
        this->screenHeight = screenHeight;
        setMaxFPS(maxFPS);
    }
    void Renderer::init() {
        SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight); //Try to get current screen rez
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_SetWindowTitle(window, "Tunnel Flag");
    }

    void Renderer::destroy() const {
        std::cout << "Quitting SDL\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    void Renderer::render() {
        auto startTime = std::chrono::high_resolution_clock::now();

        frameCounter++;

        clearScreen();
        // Draw some shit idk
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

    void Renderer::clearScreen() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    void Renderer::showScreen() {
        SDL_RenderPresent(renderer);
    }



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
};