#pragma once
#include <SDL3/SDL.h>

#include "Entity.h"
#include "globals.h"

class Camera
{
public:
	SDL_FRect sizeC;

	float zoom = 2.0f;

public:

	Camera();

	void setCameraOnPlayer(Entity& player);
	SDL_FRect worldToScreen(SDL_FRect& worldRect) const;
};

