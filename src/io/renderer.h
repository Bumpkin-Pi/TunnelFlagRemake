//
// Created by holly on 13/03/24.
//

#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>
#include <chrono>
#include <SDL2/SDL_image.h>

#include "../game/entity.h"

namespace Renderer {
    struct Camera {
        float x=0,y=0,z=1.0; //Z for zoom
    };

    class Renderer {
    private:
        Camera camera;
        int screenWidth=0,screenHeight=0;
        int maxFPS = 60;
        int frameDelay = 1000 / maxFPS; // milliseconds per frame
        float zoomMax = 10, zoomMin = 0.5;
        std::chrono::high_resolution_clock::time_point HstartTime = std::chrono::high_resolution_clock::now(); //Time used for 100fps average calc
        int frameCounter = 0;




        void clearScreen();
        void showScreen();

    public:
        Entity player1{nullptr, 0, 0, 0, 0};

        SDL_Window *window = nullptr;       //SDL window and renderer objects
        SDL_Renderer *renderer = nullptr;


        Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS);
        ~Renderer();

        void init();

        void render();



        void setCameraPos(float x, float y);
        void setCameraZoom(float z);
        void setCameraPosAndZoom(float x, float y, float z);
        void setResolution(int x, int y);
        void setMaxFPS(int maxFPS);
        void zoomIn();
        void zoomOut();

        float getCameraPosx() const;
        float getCameraPosy() const;
        float getCameraZoom() const;
        int getResolutionx() const;
        int getResolutiony() const;
        int getMaxFPS() const;

    };


};



#endif //DRAW_H
