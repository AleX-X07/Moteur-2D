#include "Entity.h"
#include "Camera.h"

Entity::Entity() {

}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer) {
    posX = 1920/2;
    posY = 1080 / 2;
    sizeX = 50;
    sizeY = 50;
    speed = 200.0f;
    jumpForce = 400.0f;  // Force initiale du saut
    gravity = 800.0f;     // Gravité appliquée
    velocityY = 0.0f;
    velocityX = 0.0f;
    collide = false;
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
    jumpForce = 400.0f;
    gravity = 800.0f;
    velocityY = 0.0f;
    velocityX = 0.0f;
    collide = _collide;
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

bool Entity::isColliding(const Entity& entity) const{
    if(rect.x + rect.w < entity.rect.x ||
       rect.x > entity.rect.x + entity.rect.w ||
       rect.y + rect.h < entity.rect.y ||
       rect.y > entity.rect.y + entity.rect.h) 
        return false;
    return true;
}

void Entity::downToGround(){
    velocityY += gravity * dt; 
    rect.y += velocityY * dt;
}

void Entity::setOnGround(bool value){
	onGround = value;
    if (onGround)
        velocityY = 0.0f;
}

void Entity::collision(const std::vector<Entity*>& colliders){
    onGround = false;
    for (auto c : colliders) {
        if (!SDL_HasRectIntersectionFloat(&rect, &c->rect))
            continue;

        float playerLeft = rect.x;
        float playerRight = rect.x + rect.w;
        float blockLeft = c->rect.x;
        float blockRight = c->rect.x + c->rect.w;

        // Check horizontal overlap
        bool horizontalOverlap = playerRight > blockLeft && playerLeft < blockRight;
        if (!horizontalOverlap)
            continue;

        float playerTop = rect.y;
        float playerBottom = rect.y + rect.h;
        float blockTop = c->rect.y;
        float blockBottom = c->rect.y + c->rect.h;

        // Vertical collision resolution
        if (velocityY > 0) {
            // Landing on top of platform
            rect.y = blockTop - rect.h;
            onGround = true;
        }
        else if (velocityY < 0) {
            // Hit ceiling
            rect.y = blockBottom;
        }
        velocityY = 0;
    }
}

void Entity::collisionHorizontal(const std::vector<Entity*>& colliders){
    for (auto c : colliders) {
        if (!SDL_HasRectIntersectionFloat(&rect, &c->rect))
            continue;

        float playerTop = rect.y;
        float playerBottom = rect.y + rect.h;
        float blockTop = c->rect.y;
        float blockBottom = c->rect.y + c->rect.h;

        // Check vertical overlap
        bool verticalOverlap = playerBottom > blockTop && playerTop < blockBottom;
        if (!verticalOverlap)
            continue;

        float playerLeft = rect.x;
        float playerRight = rect.x + rect.w;
        float blockLeft = c->rect.x;
        float blockRight = c->rect.x + c->rect.w;

        // Horizontal collision resolution
        if (velocityX > 0) {
            // Hit right wall
            rect.x = blockLeft - rect.w;
        }
        else if (velocityX < 0) {
            // Hit left wall
            rect.x = blockRight;
        }
        velocityX = 0;
    }
}



void Entity::render(Camera& camera) {
    SDL_FRect screenRect = camera.worldToScreen(rect);
    if (MyTexture) 
        SDL_RenderTexture(renderer, MyTexture, nullptr, &screenRect);
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &screenRect);
    }
}

void Entity::update(const bool* keys, float dt) {
    float dx = 0;
    float dy = 0;
    cooldownJump += dt;
    // move left and right
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) 
        dx -= 1;
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) 
        dx += 1;
    // jump
    if (keys[SDL_SCANCODE_SPACE] && onGround && cooldownJump > 0.3) {
        velocityY = -jumpForce; //saut
        cooldownJump = 0;
        onGround = false;
    }

    if (!onGround) {
        velocityY += gravity * dt;
        rect.y += velocityY * dt;
    }
    // Update position of player
    rect.x += dx * speed * dt;

}

void Entity::clampToScreen(int windowX, int windowY) {
    if (rect.x < 0) 
        rect.x = 0;
    if (rect.y < 0) 
        rect.y = 0;
    if (rect.x + rect.w > windowX) 
        rect.x = windowX - rect.w;
    if (rect.y + rect.h > windowY) 
        rect.y = windowY - rect.h;
}

void Entity::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    color.r = r;
    color.g = g;
    color.b = b;
	color.a = a;
}