#pragma once

#include "Scene.h"
#include "global.h"

class Menu : public Scene
{
public:

	SDL_FRect rect;

	Menu(SDL_Renderer* _rend);
	~Menu();


	void displayScene(LoadRessources& _MyRessources) override;
};
	

