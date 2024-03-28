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
    Renderer::~Renderer() {
        std::cout << "Quitting SDL\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    void Renderer::render(const std::vector<std::vector<short>>& map) {
        auto startTime = std::chrono::high_resolution_clock::now();

        frameCounter++;

        clearScreen();
        // Draw some shit idk
        renderGridPoints(map);
        renderPlayers();
        showScreen();
        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        if (elapsedTime < frameDelay) {std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - elapsedTime));}

    }

    void Renderer::renderPlayers() const { // Loops through players and renders them all.
        for (auto& pair : game.playerMap) {
            pair.second.render(renderer, camera.x, camera.y, camera.z, screenWidth, screenHeight);
        }
    }
    void Renderer::renderGridPoints(const std::vector<std::vector<short>>& grid) const {
        // Define colors based on the key
        SDL_Color colors[] = {
            {255, 255, 255, 255}, // white
            {255, 0, 0, 255},     // red
            {0, 0, 255, 255}      // blue
        };

        // Calculate initial position
        int startX = static_cast<int>((-camera.x / 25) / camera.z);
        int startY = static_cast<int>((-camera.y / 25) / camera.z);

        // Render points on the screen based on the grid
        for (size_t row = 0; row < grid.size(); ++row) {
            for (size_t col = 0; col < grid[row].size(); ++col) {
                // Calculate position of the point
                int x = static_cast<int>((startX + col) * 25 * camera.z + screenWidth / 2);
                int y = static_cast<int>((startY + row) * 25 * camera.z + screenHeight / 2);

                // Get the color based on the value of the short
                short value = grid[row][col];
                SDL_Color color = colors[value];

                // Set the color
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

                // Render the point
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }

    void Renderer::clearScreen() const {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }
    void Renderer::showScreen() const {
        SDL_RenderPresent(renderer);
    }


    // void Renderer::setPlayerMapPtr(std::unordered_map<int, Player> *playerMapPtr) {
    //     this->playerMapPtr = playerMapPtr;
    // }
    void Renderer::setScreenRes(int height, int width) {
        screenHeight = height;
        screenWidth = width;
        SDL_SetWindowSize(window, height, width);
    }

    void Renderer::setCameraPos(float x, float y) {camera.x = x;camera.y = y;}
    void Renderer::setCameraZoom(float z) {
        if (z < zoomMax && z > zoomMin) {camera.z = z;}}
    void Renderer::setCameraPosAndZoom(float x, float y, float z) {camera.x = x;camera.y = y;camera.z = z;}
    void Renderer::setMaxFPS(int maxFPS) {this->maxFPS = maxFPS; frameDelay = 1000 / maxFPS;}
    float Renderer::getCameraPosx() const {return camera.x;}
    float Renderer::getCameraPosy() const {return camera.y;}
    float Renderer::getCameraZoom() const {return camera.z;}
    int Renderer::getResolutionx() const {return screenWidth;}
    int Renderer::getResolutiony() const {return screenHeight;}
    int Renderer::getMaxFPS() const {return maxFPS;}
    int Renderer::getScreenHeight() const {return screenHeight;}
    int Renderer::getScreenWidth() const {return screenWidth;}


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