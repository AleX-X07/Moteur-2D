#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy() {
    texture = nullptr;
    renderer = nullptr;
    rect = { 0,0,0,0 };
    physicsEnemy = { 0,0,0,0,0,0,false,0 };
	currentState = EnemyState::movingLeft;
	animationEnemy = { 0,0,0,0,0,0 };
}

Enemy::Enemy(SDL_Texture* _MyTexture, SDL_Renderer* rend, float x, float y, float w, float h, float _speed) {
    texture = _MyTexture;
    renderer = rend;
    rect = { x,y,w,h };
    physicsEnemy = { _speed, 350.0f, 900.0f, 0, 0, 0.3f, false };
    currentState = EnemyState::movingLeft;
    animationEnemy = { 0,0,0.2f,4,127.8f,128.2f };
}

Enemy::~Enemy() {

}

void Enemy::updateAnimationEnemy(float dt){
    animationEnemy.animationTimer += dt;
    if (animationEnemy.animationTimer >= animationEnemy.frameDuration) {
        animationEnemy.animationTimer = 0.0f;
        animationEnemy.currentFrame++;

        if (animationEnemy.currentFrame >= animationEnemy.maxFrames) {
            animationEnemy.currentFrame = 0;
        }
	}
}

void Enemy::updateStateEnemy() {
	previousState = currentState;
    if (isBorderLeft) {
        currentState = EnemyState::movingLeft;
    }
    else {
        currentState = EnemyState::movingRight;
	}   

    if (currentState != previousState) {
        animationEnemy.currentFrame = 0;
        animationEnemy.animationTimer = 0.0f;
    }
}


void Enemy::render(Camera& camera) {
    SDL_FRect screenRect = camera.worldToScreen(rect);
    if (texture) {
        int animationRow = 0;
        switch (currentState) {
        case EnemyState::movingRight:
            animationRow = 1;
            break;
        case EnemyState::movingLeft:
            animationRow = 2;
            break;
        }

        SDL_FRect srcRectEnemy = {
           animationEnemy.currentFrame * animationEnemy.spriteWidth,  
           animationRow * animationEnemy.spriteHeight, 
           animationEnemy.spriteWidth,                 
           animationEnemy.spriteHeight                 
        };

        SDL_RenderTexture(renderer, texture, &srcRectEnemy, &screenRect);
    }
    
}

void Enemy::update(const bool* keys, float dt) {
    if (isBorderLeft) {
        physicsEnemy.velocityX = -physicsEnemy.speed;
    }
    else {
        physicsEnemy.velocityX = physicsEnemy.speed;
    }
    rect.x += physicsEnemy.velocityX * dt;
    if (!physicsEnemy.onGround) {
        physicsEnemy.velocityY += physicsEnemy.gravity * dt;
        rect.y += physicsEnemy.velocityY * dt;
    }
    updateAnimationEnemy(dt);
    updateStateEnemy();

}

void Enemy::colliders(std::vector<GameObject*>& colliders) {
    physicsEnemy.onGround = false;

    for (auto c : colliders) {
        if (!isColliding(*c)) {
            continue;
        }

        //x, y, w, h
        // left, right, top, bottom
        SDL_FRect playerDirection = { rect.x, rect.x + rect.w, rect.y, rect.y + rect.h };
        SDL_FRect blockSide = { c->getRect().x, c->getRect().x + c->getRect().w, c->getRect().y, c->getRect().y + c->getRect().h };
        SDL_FRect overlap = { playerDirection.y - blockSide.x, blockSide.y - playerDirection.x, playerDirection.h - blockSide.w, blockSide.h - playerDirection.w };
        
        if (rect.x <= c->getRect().x) {
            isBorderLeft = false;
        }
        else if (rect.x + rect.w >= c->getRect().x + c->getRect().w) {
            isBorderLeft = true;
        }

        // Collision with the ground
        if (overlap.w < overlap.x && overlap.w < overlap.y && overlap.w < overlap.h) {
            if (physicsEnemy.velocityY >= 0) {
                rect.y = blockSide.w - rect.h;
                physicsEnemy.onGround = true;
                physicsEnemy.velocityY = 0;
            }
        }
        else if (overlap.h < overlap.x && overlap.h < overlap.y && overlap.h < overlap.w) {
            if (physicsEnemy.velocityY < 0) {
                rect.y = blockSide.h;
                physicsEnemy.velocityY = 0;
            }
        }

        // Collision horizontal
        else if (overlap.x < overlap.w && overlap.x < overlap.h) {
            if (physicsEnemy.velocityX > 0 || (playerDirection.y > blockSide.x && playerDirection.x < blockSide.x)) {
                rect.x = blockSide.x - rect.w;
                physicsEnemy.velocityX = 0;
            }
        }
        else if (overlap.y < overlap.w && overlap.y < overlap.h) {
            if (physicsEnemy.velocityX < 0 || (playerDirection.y < blockSide.y && playerDirection.y > blockSide.y)) {
                rect.x = blockSide.y;
                physicsEnemy.velocityX = 0;
            }
        }

    }
}
