//
// Created by holly on 10/03/24.
//

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <SDL2/SDL.h>
#include <iostream>



namespace Keyboard {


    struct PlayerKeybinds {
        SDL_Scancode up = SDL_SCANCODE_W;
        SDL_Scancode down = SDL_SCANCODE_S;
        SDL_Scancode left = SDL_SCANCODE_A;
        SDL_Scancode right = SDL_SCANCODE_D;
    };

    struct Keybinds {
        PlayerKeybinds playerKeybinds;
        SDL_Scancode cameraToPlayer = SDL_SCANCODE_SPACE;
    };

    class KeyboardInput {
    private:
        const Uint8* state = SDL_GetKeyboardState(NULL);
        bool leftClick=false,rightClick=false,upScroll=false,downScroll=false;

    public:
        Keybinds keybinds;
        void update();

        bool isLeftClick() const;
        bool isRightClick() const;
        bool isKeyDown(SDL_Scancode key) const;
        bool isKeyPressed (SDL_Scancode key) const;
        bool isUpScroll () const;
        bool isDownScroll () const;
    };



} // namespace Keyboard

#endif //KEYBOARD_H
