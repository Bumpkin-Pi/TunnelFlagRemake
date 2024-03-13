//
// Created by holly on 13/03/24.
//

#ifndef DRAW_H
#define DRAW_H
#include <SDL2/SDL.h>
#include <chrono>

namespace Renderer {
    struct Camera {
        float x=0,y=0,z=1; //Z for zoom
    };

    class Renderer {
    private:
        Camera camera;
        int screenWidth,screenHeight;
        int maxFPS = 60;
        int frameDelay = 1000 / maxFPS; // milliseconds per frame
        float zoomMax = 10, zoomMin = 0.1;
        std::chrono::high_resolution_clock::time_point HstartTime = std::chrono::high_resolution_clock::now(); //Time used for 100fps average calc
        int frameCounter = 0;


        SDL_Window *window = nullptr;       //SDL window and renderer objects
        SDL_Renderer *renderer = nullptr;

        void clearScreen();
        void showScreen();

    public:


        Renderer(float CameraX, float CameraY, float CameraZ, int screenWidth, int screenHeight, int maxFPS);
        void init();
        void destroy() const;

        void render();



        void setCameraPos(float x, float y);
        void setCameraZoom(float z);
        void setCameraPosAndZoom(float x, float y, float z);
        void setResolution(int x, int y);
        void setMaxFPS(int maxFPS);

        float getCameraPosx() const;
        float getCameraPosy() const;
        float getCameraZoom() const;
        int getResolutionx() const;
        int getResolutiony() const;
        int getMaxFPS() const;

    };


};



#endif //DRAW_H
