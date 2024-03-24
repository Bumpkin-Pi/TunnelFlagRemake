//
// Created by holly on 13/03/24.
//

#include "entity.h"
#include "../io/renderer.h"

Entity::Entity(SDL_Texture* sprite, float x, float y, int width, int height)
        : sprite(sprite), x(x), y(y), width(width), height(height), vx(0), vy(0){
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
}
// Entity::~Entity() {
//     SDL_DestroyTexture(sprite);
// }

void Entity::render(SDL_Renderer *renderer, const float camerax, const float cameray, const float camerazoom, const int screenWidth, const int screenHeight) {
    // Calculate camera center
    int cameraCenterX = screenWidth / 2;
    int cameraCenterY = screenHeight / 2;

    // Calculate scaled entity dimensions
    int scaledWidth = static_cast<int>(width * camerazoom);
    int scaledHeight = static_cast<int>(height * camerazoom);

    // Calculate entity position relative to the camera center
    int relativeX = static_cast<int>(x - width / 2 - camerax);
    int relativeY = static_cast<int>(y - height / 2 - cameray);

    // Adjust entity position based on camera center
    int screenX = cameraCenterX + (relativeX * camerazoom);
    int screenY = cameraCenterY + (relativeY * camerazoom);

    // Set the destination rectangle
    SDL_Rect destRect = {screenX, screenY, scaledWidth, scaledHeight};

    // Render the entity
    SDL_RenderCopy(renderer, sprite, nullptr, &destRect);
}

void Entity::update() {
    x += vx;
    y += vy;
}

void Entity::setPos(float x, float y) {
    this->x = x;
    this->y = y;
}
void Entity::setWidthAndHeight(int width, int height) {
    this->width = width;
    this->height = height;
}
void Entity::setVelocity(float x, float y) {this->vx=x,this->vy=y;}
void Entity::setVelocityX(float x) {this->vx=x;}
void Entity::setVelocityY(float y) {this->vy=y;}


float Entity::getPosx() const {return x;}
float Entity::getPosy() const {return y;}
float Entity::getVelocityX() const {return vx;}
float Entity::getVelocityY() const {return vy;}

int Entity::getHeight() {return height;}
int Entity::getWidth() {return width;}


SDL_Texture *Entity::getSprite() const {return sprite;}
void Entity::setSprite(SDL_Texture *tex) {sprite = tex;}


