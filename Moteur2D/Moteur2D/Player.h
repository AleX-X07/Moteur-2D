#pragma once

#include "GameObject.h"

enum class PlayerState {
    idle,
    movingLeft,
    movingRight,
    jumpingLeft,
    jumpingRight,
    fallingLeft,
    fallingRight
};

class Player : public GameObject
{
private:
    Physics myPhysics;
    PlayerState currentState;

public:
    Player();
    Player(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h, float _speed);
    virtual ~Player();

    virtual void render(Camera& camera);
    virtual void update(float dt) override;
};

