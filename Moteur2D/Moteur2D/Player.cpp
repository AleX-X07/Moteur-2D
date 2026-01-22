#include "Player.h"
#include "Camera.h"

Player::Player() : GameObject() {

	texture = nullptr;
	renderer = nullptr;
	rect = { 0,0,0,0 };
	myPhysics = { 0,0,0,0,0,0,false,0 };
	currentState = PlayerStateOpti::idle;
    myAnimation = { 0,0,0,0,0,0 };
}

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h, float _speed) : GameObject() {
	texture = tex;
	renderer = ren;
	rect = { x,y,w,h };
	myPhysics = { _speed, 350.0f, 900.0f, 0, 0, 0.3f, false, 0 };
	currentState = PlayerStateOpti::idle;
    myAnimation = { 0,0,0.2f,4,127.8f,128.2f };
}


Player::~Player() {

}

void Player::respawn() {
    rect.y = 850;
    rect.x = 50;
}

void Player::clampToScreen() {
    if (rect.x < 0) {
        rect.x = 0;
    }
    if (rect.y < 0) {
        rect.y = 0;
    }
    if (rect.x + rect.w > screenWidth + rect.w) {
        rect.x = (screenWidth + rect.w) - rect.w;
    }
    if (rect.y + rect.h > screenHeight + rect.h) {
        rect.y = (screenHeight + rect.h) - rect.h;
    }
}

void Player::updateAnimation(float dt) {
    myAnimation.animationTimer += dt;
    if (myAnimation.animationTimer >= myAnimation.frameDuration) {
        myAnimation.animationTimer = 0.0f;
        myAnimation.currentFrame++;

        if (myAnimation.currentFrame >= myAnimation.maxFrames) {
            myAnimation.currentFrame = 0;
        }

    }
}

void Player::updateState(const bool* keys) {
    previousState = currentState;
    bool _movingLeft = keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A];
    bool _movingRight = keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D];

    if (myPhysics.onGround) {
        if (_movingLeft && !_movingRight) {
            currentState = PlayerStateOpti::movingLeft;
        }
        else if (_movingRight && !_movingLeft) {
            currentState = PlayerStateOpti::movingRight;
        }
        else {
            currentState = PlayerStateOpti::idle;
        }
    }
    else { // Seulement si on n'est PAS au sol
        if (_movingLeft && !_movingRight) {
            if (myPhysics.velocityY < 0) {
                currentState = PlayerStateOpti::jumpingLeft;
            }
            else {
                currentState = PlayerStateOpti::fallingLeft;
            }
        }
        else if (_movingRight && !_movingLeft) {
            if (myPhysics.velocityY < 0) {
                currentState = PlayerStateOpti::jumpingRight;
            }
            else {
                currentState = PlayerStateOpti::fallingRight;
            }
        }
        else {
            if (myPhysics.velocityY < 0) {
                currentState = PlayerStateOpti::jumpingRight;
            }
            else {
                currentState = PlayerStateOpti::fallingRight;
            }
        }
    }

    if (currentState != previousState) {
        myAnimation.currentFrame = 0;
        myAnimation.animationTimer = 0.0f;
    }

}

void Player::colliders(std::vector<GameObject*>& gameObject) {
    myPhysics.onGround = false;

    for (auto c : gameObject) {
        if (!isColliding(*c)) {
            continue;
        }

        SDL_FRect& cRect = c->getRect();

        //x, y, w, h
        // left, right, top, bottom
        SDL_FRect playerDirection = { rect.x, rect.x + rect.w, rect.y, rect.y + rect.h };
        SDL_FRect blockSide = { cRect.x, cRect.x + cRect.w, cRect.y, cRect.y + cRect.h };
        SDL_FRect overlap = { playerDirection.y - blockSide.x, blockSide.y - playerDirection.x, playerDirection.h - blockSide.w, blockSide.h - playerDirection.w };

        // Collision with the ground
        if (overlap.w < overlap.x && overlap.w < overlap.y && overlap.w < overlap.h) {
            if (myPhysics.velocityY >= 0) {
                rect.y = blockSide.w - rect.h;
                myPhysics.onGround = true;
                myPhysics.velocityY = 0;
            }
        }
        else if (overlap.h < overlap.x && overlap.h < overlap.y && overlap.h < overlap.w) {
            if (myPhysics.velocityY < 0) {
                rect.y = blockSide.h;
                myPhysics.velocityY = 0;
            }
        }

        // Collision horizontal
        else if (overlap.x < overlap.w && overlap.x < overlap.h) {
            if (myPhysics.velocityX > 0 || (playerDirection.y > blockSide.x && playerDirection.x < blockSide.x)) {
                rect.x = blockSide.x - rect.w;
                myPhysics.velocityX = 0;
            }
        }
        else if (overlap.y < overlap.w && overlap.y < overlap.h) {
            if (myPhysics.velocityX < 0 || (playerDirection.y < blockSide.y && playerDirection.y > blockSide.y)) {
                rect.x = blockSide.y;
                myPhysics.velocityX = 0;
            }
        }
    }
}

void Player::render(Camera& camera) {

    SDL_FRect screenRect = camera.worldToScreen(rect);

    if (texture) {
        // Déterminer la ligne du spritesheet selon l'état
        int animationRow = 0;
        switch (currentState) {
        case PlayerStateOpti::idle:
            animationRow = 0;
            break;
        case PlayerStateOpti::movingRight:
            animationRow = 1;
            break;
        case PlayerStateOpti::movingLeft:
            animationRow = 2;
            break;
        case PlayerStateOpti::jumpingRight:
            animationRow = 3;
            break;
        case PlayerStateOpti::jumpingLeft:
            animationRow = 4;
            break;
        case PlayerStateOpti::fallingRight:
            animationRow = 5;
            break;
        case PlayerStateOpti::fallingLeft:
            animationRow = 6;
            break;
        }

        SDL_FRect srcRect = {
            myAnimation.currentFrame * myAnimation.spriteWidth,  // x position
            animationRow * myAnimation.spriteHeight, // y position
            myAnimation.spriteWidth,                 // largeur
            myAnimation.spriteHeight                 // hauteur
        };

        SDL_RenderTexture(renderer, texture, &srcRect, &screenRect);
    }
}

void Player::update(const bool* keys, float dt) {
    myPhysics.nowTimeJump += dt;

    // move left and right
    myPhysics.velocityX = 0;
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A]) {
        myPhysics.velocityX = -myPhysics.speed;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        myPhysics.velocityX = myPhysics.speed;
    }

    // jump
    if (keys[SDL_SCANCODE_SPACE] && myPhysics.onGround && myPhysics.nowTimeJump > myPhysics.cooldownJump) {
        myPhysics.velocityY = -myPhysics.jumpForce;
        myPhysics.nowTimeJump = 0;
        myPhysics.onGround = false;
    }

    if (!myPhysics.onGround) {
        myPhysics.velocityY += myPhysics.gravity * dt;
        rect.y += myPhysics.velocityY * dt;
    }

    // Update horizontal position
    rect.x += myPhysics.velocityX * dt;

    if (rect.y >= levelHeight) {
        respawn();
    }
    clampToScreen();
    updateAnimation(dt);
}

void Player::collideEnemies(std::vector<GameObject*>& _enemies){
    for (auto e : _enemies) {
        if (isColliding(*e)) {
            respawn();
        }
    }
}
