#pragma once
#include <SDL3/SDL.h>

#include "Scene.h"

class Button
{
private:
	SDL_Window* window;
	SDL_Texture* Texture;
	SDL_Renderer* renderer;
	SDL_FRect buttonRect;

public:

	SceneState MyButtonType;

	Button(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* Texture, float x, float y, float scale);
	~Button();
	bool isClicked(SDL_Event& event);
	void render();
};

