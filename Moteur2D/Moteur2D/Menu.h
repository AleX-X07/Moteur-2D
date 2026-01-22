#pragma once

#include "Scene.h"
#include "Button.h"

class Menu : public Scene 
{

public:

	std::vector<Button> vecButton;
	bool buttonsCreated = false;  


	Menu(SDL_Renderer* _rend, SDL_Window* win);
	~Menu();

	void addButton(SDL_Texture* MyTexture, float x, float y, float scale, SceneState _MyButtonType);
	void displayScene(LoadRessources& _MyRessources) override;
	void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) override;
};
