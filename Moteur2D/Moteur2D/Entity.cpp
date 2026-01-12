#include "Entity.h"

Entity::Entity() {
    posX = 0;
    posY = 0;
    sizeX = 0;
    sizeY = 0;
    speed = 0;
    collide = false;
    MyTexture = nullptr;
    renderer = nullptr;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::Entity(SDL_Renderer* _renderer) {
    posX = 10;
    posY = 10;
    sizeX = 10;
    sizeY = 10;
    speed = 0;
    collide = false;
    MyTexture = nullptr;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer) {
    posX = 10;
    posY = 10;
    sizeX = 10;
    sizeY = 10;
    speed = 0;
    collide = false;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::~Entity() {

}

void Entity::setRect() {

}

void Entity::render() {
    if (MyTexture) {
        SDL_RenderTexture(renderer, MyTexture, NULL, &rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Entity::update(float dt) {
    float dx = 0; float dy = 0;
    rect.x += dx * speed * dt;
    rect.y += dy * speed * dt;
}