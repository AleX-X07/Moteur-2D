#pragma once
#include <vector>

class GameObject;

const int screenWidth = 1920;
const int screenHeight = 1080;

const int levelWidth = 1500;
const int levelHeight = 1080;

extern std::vector<GameObject*> myGameObject;

struct keys // struct for the keys
{
	const bool* myKeys;

	keys();
	~keys();
	void initKeys(const bool* _keys);
};

struct Physics 
{
    float speed;
    float jumpForce;
    float gravity;
    float velocityX;
    float velocityY;
    float cooldownJump;
    bool onGround;
};

struct Animation {
	int currentFrame;
	float animationTimer;
	float frameDuration;
	int maxFrames;
	float spriteWidth;
	float spriteHeight;
};
