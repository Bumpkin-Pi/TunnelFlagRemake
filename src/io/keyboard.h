//
// Created by holly on 10/03/24.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#ifdef __linux__
#include <SDL2/SDL.h>
#elif _WIN32
#include <SDL.h>
#else
#endif




namespace Keyboard {

    // Keybinds for input (This should be refrenced instead of keycodes, so that keybinds can be changed)
    struct Keybinds {
        SDL_Scancode PlayerUp = SDL_SCANCODE_W;
        SDL_Scancode PlayerDown = SDL_SCANCODE_S;
        SDL_Scancode PlayerLeft = SDL_SCANCODE_A;
        SDL_Scancode PlayerRight = SDL_SCANCODE_D;
        SDL_Scancode cameraToPlayer = SDL_SCANCODE_SPACE;
    };


    class KeyboardInput {
    private:
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        bool leftClick=false,rightClick=false,upScroll=false,downScroll=false;

    public:
        Keybinds keybinds;
        //
        void update();

        // Returns true if left mouse was pressed last update() (not if held)
        [[nodiscard]] bool isLeftClick() const;
        // Returns true if right mouse was pressed last update() (not if held)
        [[nodiscard]] bool isRightClick() const;
        // checks if key was pressed at time of last update().
        [[nodiscard]] bool getState(SDL_Scancode key) const;
        // Returns true if scrollwheel was ticked up last frame.
        [[nodiscard]] bool isUpScroll () const;
        // Returns true if scrollwheel was ticked down last frame.
        [[nodiscard]] bool isDownScroll () const;
    };


} // namespace Keyboard

#endif //KEYBOARD_H
