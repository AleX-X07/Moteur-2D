#pragma once

#include "LoadRessources.h"
#include "Scene.h"
#include "Menu.h"
#include "Play.h"

class SceneManager
{
public:

	SDL_Renderer* renderer;
	SDL_Window* window;

	SceneState currentState;

	Scene* myMenu;
	Scene* myPlay;

	LoadRessources* MyRessources;

	SceneManager(SDL_Renderer* rend, SDL_Window* win);
	~SceneManager();

	void manageState(SDL_Event& event, keys* _myKeys);
	void displayState();
};