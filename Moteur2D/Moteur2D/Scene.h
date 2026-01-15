#pragma once
#include <SDL3/SDL.h>
#include <iostream>

using namespace std;

class Scene
{
public:

	SDL_Renderer* renderer;

	Scene();
	virtual ~Scene();
	virtual void displayScene() = 0;

};

