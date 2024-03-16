//
// Created by holly on 13/03/24.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Entity {
private:
    float x,y;
    int width,height;
    SDL_Rect rect;
    SDL_Texture* sprite;


public:
    float velocityX;
    float velocityY;
    Entity(SDL_Texture* sprite, float x, float y, int width, int height);
    // ~Entity(); //Textures should be destroyed seperatly because they may be shared between entities.
    void update();
    void render(SDL_Renderer *renderer, int camerax, int cameray, float camerazoom, int screenWidth, int screenHeight);

    void setPos(float x, float y);

    float getPosx() const;
    float getPosy() const;

    void setSprite(SDL_Texture* tex);
    SDL_Texture* getSprite() const;

};

class Player {
    int team;
public:
    Entity entity{nullptr, 0, 0, 10, 10};
    Player(int team, float x, float y);
};

#endif //ENTITY_H
