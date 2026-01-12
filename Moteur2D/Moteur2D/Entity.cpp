#include "Entity.h"

Entity::Entity() {
    rect = { posX, posY, sizeX, sizeY };
}

Entity::~Entity() {

}

void Entity::setRect() {

}

void Entity::render(SDL_Renderer* renderer) {
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