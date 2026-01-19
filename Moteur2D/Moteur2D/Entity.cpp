#include "Entity.h"
#include "Camera.h"

Entity::Entity() {

}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer) {
    speed = 200.0f;
    jumpForce = 350.0f;
    gravity = 900.0f;
    velocityY = 0.0f;
    velocityX = 0.0f;
    collide = false;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { 0, 850, 50, 50 };
}

Entity::Entity(SDL_Texture* _MyTexture, SDL_Renderer* _renderer, float x, float y, float w, float h, int _speed, bool _collide) {
    speed = _speed;
    jumpForce = 350.0f;
    gravity = 900.0f;
    velocityY = 0.0f;
    velocityX = 0.0f;
    collide = _collide;
    MyTexture = _MyTexture;
    renderer = _renderer;
    rect = { x, y, w, h };
}

Entity::~Entity() {

}

void Entity::getPosition(float& x, float& y) const {
    x = rect.x;
    y = rect.y;
}

bool Entity::isColliding(const Entity& entity) const {
    if (rect.x + rect.w < entity.rect.x ||
        rect.x > entity.rect.x + entity.rect.w ||
        rect.y + rect.h < entity.rect.y ||
        rect.y > entity.rect.y + entity.rect.h)
        return false;
    return true;
}

void Entity::downToGround() {
    velocityY += gravity * dt;
    rect.y += velocityY * dt;
}

void Entity::setOnGround(bool value) {
    onGround = value;
    if (onGround)
        velocityY = 0.0f;
}

void Entity::updateState(const bool* keys) {
    previousState = currentState;
    bool _movingLeft = keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A];
    bool _movingRight = keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D];

    if (onGround) {
        if (_movingLeft && !_movingRight) {
            currentState = PlayerState::movingLeft;
        }
        else if (_movingRight && !_movingLeft) {
            currentState = PlayerState::movingRight;
        }
        else {
            currentState = PlayerState::idle;
        }
    }
    else { // Seulement si on n'est PAS au sol
        if (_movingLeft && !_movingRight) {
            if (velocityY < 0)
                currentState = PlayerState::jumpingLeft;
            else
                currentState = PlayerState::fallingLeft;
        }
        else if (_movingRight && !_movingLeft) {
            if (velocityY < 0)
                currentState = PlayerState::jumpingRight;
            else
                currentState = PlayerState::fallingRight;
        }
        else {
            if (velocityY < 0)
                currentState = PlayerState::jumpingRight;
            else
                currentState = PlayerState::fallingRight;
        }
    }

    if (currentState != previousState) {
        currentFrame = 0;
        animationTimer = 0.0f;
    }
    
}

PlayerState Entity::getCurrentState() const{
    return currentState;
}

void Entity::updateAnimation(float dt){
    animationTimer += dt;
    if (animationTimer >= frameDuration) {
        animationTimer = 0.0f;
        currentFrame++;

        if (currentFrame >= maxFrames) {
            currentFrame = 0;
        }

    }
}

void Entity::collision(const std::vector<Entity*>& colliders) {
    onGround = false;
    
    for (auto c : colliders) {
        if (!SDL_HasRectIntersectionFloat(&rect, &c->rect))
            continue;

        //x, y, w, h
        // left, right, top, bottom
        SDL_FRect playerDirection = { rect.x, rect.x + rect.w, rect.y, rect.y + rect.h };
        SDL_FRect blockSide = { c->rect.x, c->rect.x + c->rect.w, c->rect.y, c->rect.y + c->rect.h};
        SDL_FRect overlap = {playerDirection.y - blockSide.x, blockSide.y - playerDirection.x, playerDirection.h - blockSide.w, blockSide.h - playerDirection.w};

        // Collision with the ground
        if (overlap.w < overlap.x && overlap.w < overlap.y && overlap.w < overlap.h) {
            if (velocityY >= 0) {  
                rect.y = blockSide.w - rect.h;
                onGround = true;
                velocityY = 0;
            }
        }
        else if(overlap.h < overlap.x && overlap.h < overlap.y && overlap.h < overlap.w) {
            if (velocityY < 0) {
                rect.y = blockSide.h;
                velocityY = 0;
            }
        }

        // Collision horizontal
        else if (overlap.x < overlap.w && overlap.x < overlap.h) {
            if (velocityX > 0 || (playerDirection.y > blockSide.x && playerDirection.x < blockSide.x)) {
                rect.x = blockSide.x - rect.w;
                velocityX = 0;
            }
        }
        else if (overlap.y < overlap.w && overlap.y < overlap.h) {
            if (velocityX < 0 || (playerDirection.y < blockSide.y && playerDirection.y > blockSide.y)) {
                rect.x = blockSide.y;
                velocityX = 0;
            }
        }
    }
}

void Entity::respawn(){
    if (rect.y >= levelHeight){
        rect.y = 850;
        rect.x = 0;
    }
}

void Entity::render(Camera& camera) {
    SDL_FRect screenRect = camera.worldToScreen(rect);

    if (MyTexture) {
        // Déterminer la ligne du spritesheet selon l'état
        int animationRow = 0;
        switch (currentState) {
        case PlayerState::idle:
            animationRow = 0;
            break;
        case PlayerState::movingRight:
            animationRow = 1;
            break;
        case PlayerState::movingLeft:
            animationRow = 2;
            break;
        case PlayerState::jumpingRight:
            animationRow = 3;
            break;
        case PlayerState::jumpingLeft:
            animationRow = 4;
            break;
        case PlayerState::fallingRight:
            animationRow = 5; 
            break;
        case PlayerState::fallingLeft:
            animationRow = 6;
            break;
        }

        SDL_FRect srcRect = {
            currentFrame * spriteWidth,  // x position
            animationRow * spriteHeight, // y position
            spriteWidth,                 // largeur
            spriteHeight                 // hauteur
        };

        SDL_RenderTexture(renderer, MyTexture, &srcRect, &screenRect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &screenRect);
    }
}

void Entity::update(const bool* keys, float dt) {
    cooldownJump += dt;

    // move left and right
    velocityX = 0;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
        velocityX =-speed;

    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
        velocityX = speed;

    // jump
    if (keys[SDL_SCANCODE_SPACE] && onGround && cooldownJump > 0.3) {
        velocityY = -jumpForce;
        cooldownJump = 0;
        onGround = false;
    }

    if (!onGround) {
        velocityY += gravity * dt;
        rect.y += velocityY * dt;
    }

    // Update horizontal position
    rect.x += velocityX * dt;

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

void Entity::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}