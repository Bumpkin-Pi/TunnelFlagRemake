//
// Created by holly on 13/03/24.
//

#ifndef DRAW_H
#define DRAW_H
#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#else
#endif
#include <chrono>
#include <vector>
#include "loadTextures.h"
#include "game/map.h"

namespace Renderer {
    /*
     * General renderer namespace, containing classes and structs required for drawing
     */

    // Simple struct containing the x,y coords of the camera, as well as the z(zoom)
    struct Camera {
        float x=0,y=0,z=1.0; //Z for zoom
    };

    // Handles pretty much all SDL functions.
    class Renderer {
    private:
        Camera camera;
        int screenWidth=0,screenHeight=0; // Screen resolution.
        int maxFPS = 60; // Max FPS.
        int frameDelay = 1000 / maxFPS; // milliseconds per frame
        float zoomMax = 10, zoomMin = 0.005; // Boundaries for how the camera zoom can be changed.
        std::chrono::high_resolution_clock::time_point HstartTime = std::chrono::high_resolution_clock::now(); //Time used for 100frames average calc
        int frameCounter = 0; // Indexes for ever frame rendered.



        void clearScreen() const;     // Clear screen buffer
        void renderGridPoints(const Map& map) const; // Renders values of map (for debuging only)
        void renderMarchingSquares(const Map& map) const;
        void renderPlayers() const;   // Draw players to buffer
        void showScreen() const;      // Show buffer

    public:
        // std::unordered_map<int, Player>* playerMapPtr;

        Textures* textures;
        SDL_Window *window = nullptr;       //SDL window and renderer objects
        SDL_Renderer *renderer = nullptr;


        Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS);
        ~Renderer();

        // Render a frame. (Calls all other rendering functions in order)
        void render(const Map& map);


        void setScreenRes(int height, int width);                           // Setters
        void setCameraPos(float x, float y);
        void setCameraZoom(float z);
        void setCameraPosAndZoom(float x, float y, float z);
        void setMaxFPS(int maxFPS);
        // Camera zoom in to 0.9 with minimum of Renderer.zoomMin
        void zoomIn();
        // Camera zoom out to 1/0.9 (1.11111) with max of Renderer.zoomMax
        void zoomOut();
        // void setPlayerMapPtr(std::unordered_map<int, Player>* playerMapptr);

        float getCameraPosx() const;                                            // Getters
        float getCameraPosy() const;
        float getCameraZoom() const;
        int getResolutionx() const;
        int getResolutiony() const;
        int getMaxFPS() const;
        int getScreenWidth() const;
        int getScreenHeight() const;

        float realToPixelX(float realX) const;
        float realToPixelY(float realY) const;
    };


};



#endif //DRAW_H
