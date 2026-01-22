#include "Play2.h"

Play2::Play2(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
	myPlayer = nullptr;
	camera = new Camera();
	int w;
	int h;
	SDL_GetWindowSize(win, &w, &h);
	playerParallax = new Parallax(rend, w, h);
}

Play2::~Play2() {
	delete myPlayer;
	for (auto gameObject : gameObject) {
		delete gameObject;
	}
	delete camera;
	delete playerParallax;
}

void Play2::createGameObjects(LoadRessources& _MyRessources) {
	myPlayer = new Player(renderer, _MyRessources.player, 50, 820, 50, 50, 200.0f);

	GameObject* Ground = new GameObject(renderer, _MyRessources.ground, 0, 880, 200, 250);
	gameObject.push_back(Ground);

	GameObject* Ground1 = new GameObject(renderer, _MyRessources.ground, 300, 820, 100, 300);
	gameObject.push_back(Ground1);

}

void Play2::displayScene(LoadRessources& _MyRessources) {
	if (!isCreatedGRound) {
		createGameObjects(_MyRessources);
		playerParallax->addLayer(_MyRessources.bg_layer1, 0.1f);
		playerParallax->addLayer(_MyRessources.bg_layer2, 0.3f);
		playerParallax->addLayer(_MyRessources.bg_layer3, 0.5f);
		playerParallax->addLayer(_MyRessources.bg_layer4, 0.8f);
		isCreatedGRound = true;
	}
	SDL_RenderClear(renderer);
	playerParallax->render(*camera);

	for (auto gameObject : gameObject) {
		gameObject->render(*camera);
	}
	myPlayer->render(*camera);
	SDL_RenderPresent(renderer);
}

void Play2::update(const bool* keys, float dt) {
	if (myPlayer) {
		playerParallax->update(myPlayer->getRect().x, myPlayer->getRect().y);
		myPlayer->update(keys, dt);
		myPlayer->colliders(gameObject);
		myPlayer->updateState(keys);
		camera->setCameraOnPlayer(*myPlayer);
	}
}

void Play2::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	if (_myKeys->myKeys[SDL_SCANCODE_ESCAPE]) {
		currentScene = menu;
	}
	if (myPlayer->getRect().x <= 0) {
		currentScene = play;
	}
}
