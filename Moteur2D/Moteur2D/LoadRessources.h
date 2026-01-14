#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class LoadRessources
{
public:
	//Surface
	SDL_Renderer* renderer;

	//Texture
	SDL_Texture* player;
	SDL_Texture* ground;

	// Constructor
	LoadRessources(SDL_Renderer* rend);

	// Load all texture
	void loadAllTexture();

	// Destructor
	~LoadRessources();
};

