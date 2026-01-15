#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* rend) {
	renderer = rend;
	currentState = SceneState::menu;
	keys = nullptr;

	myMenu = new Menu(renderer);  
	myPlay = new Play(renderer);

	MyRessources = new LoadRessources(rend);
	MyRessources->loadAllTexture();
}

SceneManager::~SceneManager() {

	delete myMenu;
	delete myPlay;
	myMenu = nullptr;
	myPlay = nullptr;

	keys = nullptr;

	delete MyRessources;  
	MyRessources = nullptr;
}

void SceneManager::initKeys(const bool* _keys) 
{
	keys = _keys;
}

void SceneManager::manageState() {
	switch (currentState)
	{
		case(SceneState::menu) :
		{
			myMenu->displayScene(*MyRessources);
			if (keys[SDL_SCANCODE_SPACE])
			{
				currentState = SceneState::play;
			}
		} 
		break;
		case(SceneState::play) :
		{
			myPlay->displayScene(*MyRessources);
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				currentState = SceneState::menu;
			}
		}
		break;
	}
}