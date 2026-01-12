#include "Entity.h"

Entity::Entity() {

}

Entity::Entity(SDL_Renderer* _renderer) {
    posX = 1920/2;
    posY = 1080/2;
    sizeX = 50;
    sizeY = 50;
    speed = 1;
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
    speed = 1;
    collide = false;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::~Entity() {

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

void Entity::update(const bool* keys, float dt) {
    float dx = 0, dy = 0;
    // Chek if z,q,s,d or up,down,left,right are pressed
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W]) {
        dy -= 1;
    }
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S]) {
        dy += 1;
    }
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        dx -= 1;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        dx += 1;
    }
    // Update position of player
    rect.x += dx * speed * dt;
    rect.y += dy * speed * dt;
}

void Entity::clampToScreen(int windowX, int windowY) {
    if (rect.x < 0) {
        rect.x = 0;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    if (rect.x + rect.w > windowX) {
        rect.x = windowX - rect.w;
    }
    if (rect.y + rect.h > windowY) {
        rect.y = windowY - rect.h;
    }
}
