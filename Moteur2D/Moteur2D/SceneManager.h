#pragma once

#include "LoadRessources.h"
#include "Scene.h"
#include "Menu.h"
#include "Play.h"
#include "LoadRessources.h"

class SceneManager
{
public:

	SDL_Renderer* renderer;

	const bool* keys;

	enum class SceneState {
		menu,
		play,
	};

	SceneState currentState;

	Scene* myMenu;
	Scene* myPlay;

	LoadRessources* MyRessources;

	SceneManager(SDL_Renderer* rend);
	~SceneManager();

	void initKeys(const bool* _keys);
	void manageState();
};


