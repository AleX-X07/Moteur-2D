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
	SDL_Texture* enemy;
	SDL_Texture* bg_layer1; 
	SDL_Texture* bg_layer2; 
	SDL_Texture* bg_layer3;
	SDL_Texture* bg_layer4;
	SDL_Texture* play_button;
	SDL_Texture* exit_button;

	// Constructor
	LoadRessources(SDL_Renderer* rend);

	// Load all texture
	void loadTexture(const char* _path, SDL_Texture*& _MyTexture);
	void loadAllTexture();

	// Destructor
	~LoadRessources();
};

