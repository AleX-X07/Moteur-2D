#pragma once
#include <SDL3/SDL.h>

#include "LoadRessources.h"

class Scene
{
public:

	SDL_Renderer* renderer;

	Scene();
	virtual ~Scene();
	virtual void displayScene(LoadRessources& _MyRessources) = 0;
};

