#pragma once

const int screenWidth = 1920;
const int screenHeight = 1080;

const int levelWidth = 1500;
const int levelHeight = 1080;


struct keys // struct for the keys
{
	const bool* myKeys;

	keys();
	~keys();
	void initKeys(const bool* _keys);
};

struct physics 
{
    float speed;
    float jumpForce;
    float gravity;
    float velocityX;
    float velocityY;
    float cooldownJump;
};
