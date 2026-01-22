#include "Play.h"

Play::Play(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
	myPlayer = nullptr;
	camera = new Camera();
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	playerParallax = new Parallax(rend, w ,h);
}

Play::~Play() {
	delete myPlayer;
	for (auto gameObject : gameObject) {
		delete gameObject;
	}
	delete camera;
	delete playerParallax;
}

void Play::createGameObjects(LoadRessources& _MyRessources) {
	myPlayer = new Player(renderer, _MyRessources.player, 50, 820, 50, 50, 200.0f);

	Enemy1 = new Enemy(_MyRessources.enemy, renderer, 850, 780, 50, 50, 50.0f);

	auto Ground = new GameObject(renderer, _MyRessources.ground, 0, 880, 200 ,250);
	gameObject.push_back(Ground);

	auto Ground1 = new GameObject(renderer, _MyRessources.ground, 300, 820, 100, 300);
	gameObject.push_back(Ground1);

	auto Ground2 = new GameObject(renderer, _MyRessources.ground, 500, 800, 150, 50);
	gameObject.push_back(Ground2);

	auto Ground3 = new GameObject(renderer, _MyRessources.ground, 700, 830, 200, 40);
	gameObject.push_back(Ground3);

	auto Ground4 = new GameObject(renderer, _MyRessources.ground, 1000, 780, 200, 120);
	gameObject.push_back(Ground4);

	auto Ground5 = new GameObject(renderer, _MyRessources.ground, 1100, 730, 200, 150);
	gameObject.push_back(Ground5);

	auto Ground6 = new GameObject(renderer, _MyRessources.ground, 890, 670, 140, 40);
	gameObject.push_back(Ground6);

	auto Ground7 = new GameObject(renderer, _MyRessources.ground, 830, 620, 100, 40);
	gameObject.push_back(Ground7);

	auto Ground8 = new GameObject(renderer, _MyRessources.ground, 1050, 580, 200, 20);
	gameObject.push_back(Ground8);

	auto Ground9 = new GameObject(renderer, _MyRessources.ground, 1350, 550, 200, 600);
	gameObject.push_back(Ground9);
}

void Play::displayScene(LoadRessources& _MyRessources) {
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

	for (auto ground : gameObject) {
		ground->render(*camera);
	}
	myPlayer->render(*camera);
	Enemy1->render(*camera);
	SDL_RenderPresent(renderer);
}

void Play::update(const bool* keys, float dt) {

	if (myPlayer) {
		playerParallax->update(myPlayer->getRect().x, myPlayer->getRect().y);
		myPlayer->update(keys, dt);
		myPlayer->colliders(gameObject);
		myPlayer->updateState(keys);
		camera->setCameraOnPlayer(*myPlayer);

		Enemy1->update(keys, dt);
		Enemy1->colliders(gameObject);

	}
}

void Play::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	if (_myKeys->myKeys[SDL_SCANCODE_ESCAPE]) 
		currentScene = menu;
	if (myPlayer->getRect().x >= levelWidth)
		currentScene = play2;
}