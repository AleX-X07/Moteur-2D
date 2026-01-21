#pragma once

#include "GameObject.h"

enum class PlayerStateOpti {
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
    PlayerStateOpti currentState;
    Animation myAnimation;

public:
    Player();
    Player(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h, float _speed);
    virtual ~Player();

    void respawn();
    void clampToScreen();
    void updateAnimation(float dt);
    void updateState(const bool* keys);

    virtual void colliders() override;
    virtual void render(Camera& camera) override;
    virtual void update(const bool* keys, float dt) override;
};

