//
// Created by holly on 13/03/24.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Entity {
    /*
     * Generic entity class.
     * Contains basic location and velocity data, as well as a texture pointer, and a drawing method to be called from the Renderer.
     */
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
    void setWidthAndHeight(int width, int height);

    float getPosx() const;
    float getPosy() const;
    int getWidth();
    int getHeight();
    void setSprite(SDL_Texture* tex);
    SDL_Texture* getSprite() const;

};



#endif //ENTITY_H
