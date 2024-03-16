//
// Created by holly on 10/03/24.
//

#include "keyboard.h"
extern bool closing;

namespace Keyboard {

    bool KeyboardInput::isLeftClick() const {
        return this->leftClick;
    }
    bool KeyboardInput::isRightClick() const {
        return this->leftClick;
    }
    bool KeyboardInput::isKeyDown(SDL_Scancode key) const {
        return state[key];
    }

    bool KeyboardInput::isUpScroll() const {
        return this->upScroll;
    }
    bool KeyboardInput::isDownScroll() const {
        return this->downScroll;
    }


    void KeyboardInput::update() {
        state = SDL_GetKeyboardState(NULL);
        leftClick = false;
        rightClick = false;
        upScroll = false;
        downScroll = false;

        SDL_Event event;

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
            }else if (event.type == SDL_QUIT) {
                closing = true;
            }
        }
    }


} // namespace Keyboard