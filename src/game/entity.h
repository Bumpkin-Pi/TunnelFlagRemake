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
    float vx;
    float vy;
    int width,height;
    SDL_Rect rect; // Rect used for drawing. Should not be used for any logic.
    SDL_Texture* sprite; // Pointer to texture.

public:
    Entity(SDL_Texture* sprite, float x, float y, int width, int height);
    // ~Entity(); //Textures should be destroyed seperatly because they may be shared between entities.
    // Updates position based on velocity (vx,vy).
    void update();
    // Draws entity to correct location on screen, based on camera zoom, location, and window resolution.
    void render(SDL_Renderer *renderer, int camerax, int cameray, float camerazoom, int screenWidth, int screenHeight);

    void setPos(float x, float y);                      // Setters
    void setWidthAndHeight(int width, int height);
    void setVelocity(float x, float y);
    void setVelocityX(float x);
    void setVelocityY(float y);
    //Set sprite. Uses pointer so does not require copy of texture.
    void setSprite(SDL_Texture* tex);

    float getPosx() const;                              // Getters
    float getPosy() const;
    float getVelocityX() const;
    float getVelocityY() const;
    int getWidth();
    int getHeight();
    // Returns pointer to entity sprite
    SDL_Texture* getSprite() const;

};



#endif //ENTITY_H
