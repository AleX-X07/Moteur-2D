#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class LoadRessources
{
public:
	//Surface
	SDL_Renderer* renderer;

	//Texture
	SDL_Texture* player;
	SDL_Texture* ground;
	SDL_Texture* bg_layer1; 
	SDL_Texture* bg_layer2; 
	SDL_Texture* bg_layer3;
	SDL_Texture* bg_layer4;

	// Constructor
	LoadRessources(SDL_Renderer* rend);

	// Load all texture
	void loadTexture(const char* _path, SDL_Texture*& _MyTexture);
	void loadAllTexture();

	// Destructor
	~LoadRessources();
};

