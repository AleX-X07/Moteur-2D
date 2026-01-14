#pragma once
#include <SDL3/SDL.h>

#include "Entity.h"

class Camera
{
public:
	SDL_FRect sizeC;

	float screenWidth;
	float screenHeight;

	float levelWidth;
	float levelHeight;

	float zoom = 2.0f;

public:

	Camera(float sw, float sh, float lw, float lh);

	void setCameraOnPlayer(Entity& player);
	SDL_FRect worldToScreen(SDL_FRect& worldRect);
};

