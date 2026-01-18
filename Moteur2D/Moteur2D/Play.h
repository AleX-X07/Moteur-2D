#pragma once

#include "Scene.h"

class Play : public Scene
{
public:

	Play(SDL_Renderer* _rend, SDL_Window* win);
	~Play();

	void displayScene(LoadRessources& _MyRessources) override;
	virtual void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) override;
};