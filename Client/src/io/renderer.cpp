//
// Created by holly on 13/03/24.
//

#include "io/renderer.h"
#include "game/game.h"

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
        SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_SetWindowTitle(window, "Tunnel Flag");

        // Load player texture
//        SDL_Texture* texture = IMG_LoadTexture(renderer, "../textures/player1.png"); //TODO: fix relative dirs.
//        if (!texture) {
//            std::cerr << "Failed to load player texture: " << SDL_GetError() << std::endl;
//             Handle error
//        }

    }
    Renderer::~Renderer() {
        std::cout << "Quitting SDL\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void Renderer::render(Map& map) {
        auto startTime = std::chrono::high_resolution_clock::now();

        frameCounter++;

        clearScreen();
        // Draw some shit idk
        renderMarchingSquares(map);
//        renderGridPoints(map);
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
    void Renderer::renderGridPoints(Map& map) const {
        // Define colors based on the key
        SDL_Color colors[] = {
                {255, 255, 255, 255}, // white  0
                {255, 0, 0, 255},     // red    1
                {0, 0, 255, 255}      // blue   2 (unused)
        };
        int realStartX = 0; // Origin of map. This will probably always just be 0,0.
        int realStartY = 0;

        // Render points on the screen based on the grid
        for (size_t row = 0; row < map.getMap().size(); ++row) {
            for (size_t col = 0; col < map.getMap()[row].size(); ++col) {
                int pixelX = realToPixelX((realStartX + col) * 25);
                int pixelY = realToPixelY((realStartY + row) * 25);
                SDL_Color color = colors[map.getMap()[row][col]]; // Choose color based on value of point
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(renderer, pixelX, pixelY);
            }
        }
    }
    void Renderer::renderMarchingSquares(Map& map) const {
        int gridSize = map.getTileSize(); // No clue if this will be changed. Probably a bad place to define it either way.
        renderMapBackground(realToPixelX(0), realToPixelY(0), (map.getColumns()-1)*gridSize*camera.z, (map.getRows()-1)*gridSize*camera.z);
        SDL_Rect destRect = { 0, 0, static_cast<int>(gridSize*camera.z +0.5), static_cast<int>(gridSize*camera.z +0.5) }; // Rect to draw all tiles (is just shuffled around each point and redrawn).
        // Iterate through the grid
        for (size_t row = 0; row < map.getMap().size() - 1; ++row) {
            for (size_t col = 0; col < map.getMap()[row].size() - 1; ++col) {
                // Get the value of each corner
                short topLeft = map.getMap()[row][col];
                short topRight = map.getMap()[row][col + 1];
                short bottomLeft = map.getMap()[row + 1][col];
                short bottomRight = map.getMap()[row + 1][col + 1];

                destRect.x = realToPixelX(col*gridSize);
                destRect.y = realToPixelY(row*gridSize);

                // Work out which texture to use.
                SDL_Texture* texture = nullptr;
                switch (topLeft << 3 | topRight << 2 | bottomRight << 1 | bottomLeft) { // Funky binary bullshitery.
                    case 0b0000: texture = textures->map0000; break;
                    case 0b0001: texture = textures->map0001; break;
                    case 0b0010: texture = textures->map0010; break;
                    case 0b0011: texture = textures->map0011; break;
                    case 0b0100: texture = textures->map0100; break;
                    case 0b0101: texture = textures->map0101; break;
                    case 0b0110: texture = textures->map0110; break;
                    case 0b0111: texture = textures->map0111; break;
                    case 0b1000: texture = textures->map1000; break;
                    case 0b1001: texture = textures->map1001; break;
                    case 0b1010: texture = textures->map1010; break;
                    case 0b1011: texture = textures->map1011; break;
                    case 0b1100: texture = textures->map1100; break;
                    case 0b1101: texture = textures->map1101; break;
                    case 0b1110: texture = textures->map1110; break;
                    case 0b1111: texture = textures->map1111; break;
                    default: break;
                }

                // If texture is found, work. Else; Give up.
                if (texture) {
                    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
                }
            }
        }
    }
    void Renderer::renderMapBackground(int startX, int startY, int width, int height) const {
        SDL_Rect backgroundRect = {startX, startY, width, height};
        backgroundRect.x = startX;
        backgroundRect.y = startY;
        backgroundRect.w = width;
        backgroundRect.h = height;
        SDL_SetRenderDrawColor(renderer, 94, 95, 100, 255);
        SDL_RenderFillRect(renderer, &backgroundRect);
    }


    void Renderer::clearScreen() const {
        SDL_SetRenderDrawColor(renderer, 0, 100, 100, 255); // 33, 33, 33 for same as background.
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
    void Renderer::setCameraZoom(float z) {if (z < zoomMax && z > zoomMin) {camera.z = z;}}
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

    float Renderer::realToPixelX(float realX) const {
        int cameraCenterX = screenWidth / 2;
        return ((realX - camera.x) * camera.z) + cameraCenterX;
    }
    float Renderer::realToPixelY(float realY) const {
        int cameraCenterY = screenHeight / 2;
        return ((realY - camera.y) * camera.z) + cameraCenterY;
    }


};