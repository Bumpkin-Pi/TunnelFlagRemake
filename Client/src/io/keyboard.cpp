//
// Created by holly on 10/03/24.
//

#include "io/keyboard.h"
extern bool closing;

namespace Keyboard {

    bool KeyboardInput::isLeftClick() const {
        return this->leftClick;
    }
    bool KeyboardInput::isRightClick() const {
        return this->leftClick;
    }
    bool KeyboardInput::getState(SDL_Scancode key) const {
        return state[key];
    }

    bool KeyboardInput::isUpScroll() const {
        return this->upScroll;
    }
    bool KeyboardInput::isDownScroll() const {
        return this->downScroll;
    }

    bool KeyboardInput::isSpace() const {
        return this->space;
    }




    void KeyboardInput::update() {
        state = SDL_GetKeyboardState(NULL);
        leftClick = false;
        rightClick = false;
        upScroll = false;
        downScroll = false;
        SDL_Event event;
        space = false;
        leftClickHeld = false;
        if (SDL_GetMouseState(&mouseX, &mouseY)){
            if(SDL_BUTTON_LMASK){
                leftClickHeld = true;
            }
        }



        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    this->leftClick = (event.type == SDL_MOUSEBUTTONDOWN);
                }
                if (event.button.button == SDL_BUTTON_RIGHT) {
                    this->rightClick = (event.type == SDL_MOUSEBUTTONDOWN);
                }

            }else if(event.type == SDL_MOUSEWHEEL){
                if(event.wheel.y > 0) // scroll up
                {
                    upScroll = true;
                }
                else if(event.wheel.y < 0) // scroll down
                {
                    downScroll = true;
                }
            }else if( event.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( event.key.keysym.sym )
                {
                    case SDLK_SPACE:
                        space = true;
                        break;
                    default:
                        break;
                }
            }else if (event.type == SDL_QUIT) {
                    closing = true;
            }
        }

    }

    int KeyboardInput::getMouseX() const {
        return mouseX;
    }

    int KeyboardInput::getMouseY() const {
        return mouseY;
    }

    bool KeyboardInput::isLeftClickHeld() const {
        return leftClickHeld;
    }
}