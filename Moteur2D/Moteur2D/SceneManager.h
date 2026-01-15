#pragma once

#include "Scene.h"
#include "Menu.h"
#include "Play.h"

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

	SceneManager(SDL_Renderer* rend);
	~SceneManager();

	void initKeys(const bool* _keys);
	void manageState();
};


