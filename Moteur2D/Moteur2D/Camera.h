#pragma once
#include <SDL3/SDL.h>

#include "globals.h"
#include "Player.h"

class Camera
{
public:
	SDL_FRect sizeC;

	float zoom = 2.0f;

public:

	Camera();

	void setCameraOnPlayer(Player& player);
	SDL_FRect worldToScreen(SDL_FRect& worldRect) const;
	void reset();
};

