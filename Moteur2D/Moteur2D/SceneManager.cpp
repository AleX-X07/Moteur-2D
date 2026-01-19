#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
	currentState = SceneState::menu;

	myMenu = new Menu(renderer,window);
	myPlay = new Play(renderer,window);

	MyRessources = new LoadRessources(rend);
	MyRessources->loadAllTexture();
}

SceneManager::~SceneManager() {

	delete myMenu;
	delete myPlay;
	myMenu = nullptr;
	myPlay = nullptr;

	delete MyRessources;
	MyRessources = nullptr;
}

void SceneManager::manageState(SDL_Event& event, keys* _myKeys) {
	if (currentState == SceneState::menu) {
		myMenu->nextScene(currentState, event, _myKeys);
	}
	else if (currentState == SceneState::play) {
		myPlay->nextScene(currentState, event, _myKeys);
	}
}

void SceneManager::displayState() {
	switch (currentState)
	{
	case(SceneState::menu):
	{
		myMenu->displayScene(*MyRessources);
	}
	break;
	case(SceneState::play):
	{
		myPlay->displayScene(*MyRessources);
	}
	break;
	}
}

void SceneManager::updateState(const bool* keys, float dt) {
	if (currentState == SceneState::play) {
		static_cast<Play*>(myPlay)->update(keys, dt);
	}
}