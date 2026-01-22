#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy() {
}

Enemy::Enemy(SDL_Texture* _MyTexture, SDL_Renderer* rend, float x, float y, float w, float h, float _speed){
	texture = _MyTexture;
	renderer = rend;
	rect = { x,y,w,h };
	physicsEnemy = { _speed, 350.0f, 900.0f, 0, 0, 0.3f, false };
}

Enemy::~Enemy() {

}


void Enemy::render(Camera& camera){
	SDL_FRect screenRect = camera.worldToScreen(rect);
	SDL_RenderTexture(renderer, texture, nullptr, &screenRect);
}

void Enemy::update(const bool* keys, float dt){
	physicsEnemy.velocityX = -physicsEnemy.speed;
	rect.x += physicsEnemy.velocityX * dt;
    if (!physicsEnemy.onGround) {
        physicsEnemy.velocityY += physicsEnemy.gravity * dt;
        rect.y += physicsEnemy.velocityY * dt;
    }
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
        SDL_FRect blockSide = { c->getRect().x, c->getRect().x + c->getRect().w, c->getRect().y, c->getRect().y + c->getRect().h};
        SDL_FRect overlap = { playerDirection.y - blockSide.x, blockSide.y - playerDirection.x, playerDirection.h - blockSide.w, blockSide.h - playerDirection.w };

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
