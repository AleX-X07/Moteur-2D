#pragma once

#include "Scene.h"

class Play : public Scene
{
public:

	Play(SDL_Renderer* _rend);
	~Play();

	void displayScene(LoadRessources& _MyRessources) override;
};