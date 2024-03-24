//
// Created by holly on 10/03/24.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <SDL2/SDL.h>
#include <iostream>



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
        const Uint8* state = SDL_GetKeyboardState(NULL);
        bool leftClick=false,rightClick=false,upScroll=false,downScroll=false;

    public:
        Keybinds keybinds;
        //
        void update();

        // Returns true if left mouse was pressed last update() (not if held)
        bool isLeftClick() const;
        // Returns true if right mouse was pressed last update() (not if held)
        bool isRightClick() const;
        // checks if key was pressed at time of last update().
        bool getState(SDL_Scancode key) const;
        // Returns true if scrollwheel was ticked up last frame.
        bool isUpScroll () const;
        // Returns true if scrollwheel was ticked down last frame.
        bool isDownScroll () const;
    };


} // namespace Keyboard

#endif //KEYBOARD_H
