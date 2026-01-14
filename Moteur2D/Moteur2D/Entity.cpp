#include "Entity.h"

Entity::Entity() {

}

Entity::Entity(SDL_Renderer* _renderer) {
    posX = 1920/2;
    posY = 1080/2;
    sizeX = 50;
    sizeY = 50;
    speed = 100.0f;
    collide = false;
    MyTexture = nullptr;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer, float x, float y, float w, float h, int _speed, bool _collide) {
    posX = x;
    posY = y;
    sizeX = w;
    sizeY = h;
    speed = _speed;
    collide = _collide;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer, float x, float y, float w, float h, int _speed, bool _collide) {
    posX = x;
    posY = y;
    sizeX = w;
    sizeY = h;
    speed = _speed;
    collide = false;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { posX, posY, sizeX, sizeY };
}

Entity::~Entity() {

}

void Entity::getPosition(float& x, float& y) const{
    x = rect.x;
	y = rect.y;
}

bool Entity::isColliding(const Entity& entity) const
{
    if(rect.x + rect.w < entity.rect.x ||
       rect.x > entity.rect.x + entity.rect.w ||
       rect.y + rect.h < entity.rect.y ||
       rect.y > entity.rect.y + entity.rect.h) {
        return false;
	}
    return true;
}

void Entity::downToGround(){
    rect.y += 10;
}

void Entity::setOnGround(bool value){
	onGround = value;
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
    // move left and right
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        dx -= 1;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        dx += 1;
    }
    // jump
    if (keys[SDL_SCANCODE_SPACE] && onGround) {
        for (int X = 0; X < 10; X++) {
            dy -= 10;
        }
        onGround = false;
    }
    // Update position of player
    rect.x += dx * speed * dt;
	rect.y += dy;

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

void Entity::setColor(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
	color.a = a;
}
