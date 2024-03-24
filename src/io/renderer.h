//
// Created by holly on 13/03/24.
//

#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>
#include <chrono>
#include <unordered_map>
#include <SDL2/SDL_image.h>

#include "../game/entity.h"
#include "../game/player.h"


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
        float zoomMax = 10, zoomMin = 0.5; // Boundaries for how the camera zoom can be changed.
        std::chrono::high_resolution_clock::time_point HstartTime = std::chrono::high_resolution_clock::now(); //Time used for 100fps average calc
        int frameCounter = 0; // Indexes for ever frame rendered.


        void clearScreen();     // Clear screen buffer
        void renderPlayers();   // Draw players to buffer
        void showScreen();      // Show buffer

    public:
        // std::unordered_map<int, Player>* playerMapPtr;

        SDL_Window *window = nullptr;       //SDL window and renderer objects
        SDL_Renderer *renderer = nullptr;


        Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS);
        ~Renderer();

        // Initialise SDL window.
        void init();
        // Render a frame. (Calls all other
        void render();


        void setScreenRes(float height, float width);                           // Setters
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

    };


};



#endif //DRAW_H
