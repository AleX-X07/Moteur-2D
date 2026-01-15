#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* rend) {
	renderer = rend;
	currentState = SceneState::menu;
	keys = nullptr;

	myMenu = new Menu(renderer);  
	myPlay = new Play(renderer);
}

SceneManager::~SceneManager() {

	SDL_DestroyRenderer(renderer);

	delete myMenu;
	delete myPlay;
	myMenu = nullptr;
	myPlay = nullptr;

	delete keys;
	keys = nullptr;
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
			myMenu->displayScene();
			if (keys[SDL_SCANCODE_SPACE])
			{
				currentState = SceneState::play;
			}
			else
			{
				cout << "1";
			}
		} 
		break;
		case(SceneState::play) :
		{
			myPlay->displayScene();
			if (keys[SDL_SCANCODE_ESCAPE])
			{
				currentState = SceneState::menu;
			}
			else
			{
				cout << "2";
			}
		}
		break;
	}

}