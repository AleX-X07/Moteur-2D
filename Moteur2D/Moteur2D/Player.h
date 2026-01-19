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
    physics myPhysics;
    bool isGround;
public:
    Player() : GameObject() {};
    //virtual ~Player() override;
}; 

