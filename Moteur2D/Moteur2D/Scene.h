#pragma once
#include <SDL3/SDL.h>

#include "LoadRessources.h"
#include "globals.h"

enum SceneState { // enum for state of scene
	menu,
	play,
	quit,
};


class Scene // Inferface for different scene 
{
public:

	SDL_Renderer* renderer;
	SDL_Window* window;

	Scene();
	virtual ~Scene();
	virtual void displayScene(LoadRessources& _MyRessources) = 0; // Function for display scene
	virtual void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) = 0; // Function for change scene
};