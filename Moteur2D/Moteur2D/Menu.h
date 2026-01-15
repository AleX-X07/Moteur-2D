#pragma once

#include "Scene.h"

class Menu : public Scene
{
public:

	Menu(SDL_Renderer* _rend);
	~Menu();


	void displayScene() override;
};
	

