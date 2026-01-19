#include "Play.h"

Play::Play(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
	Player = nullptr;
	camera = new Camera(1920, 1080, 1500, 1080);
	int w, h;
	SDL_GetWindowSize(win, &w, &h);
	playerParallax = new Parallax(rend, w ,h);
}

Play::~Play() {
	delete Player;
	for (auto ground : grounds) {
		delete ground;
	}
	delete camera;
	delete playerParallax;
}

void Play::createGameObjects(LoadRessources& _MyRessources) {
	Player = new Entity(_MyRessources.player, renderer);
	Player->setColor(0, 255, 0, 255);
	Player->rect.x = 50;  
	Player->rect.y = 820;

	auto Ground = new Entity(_MyRessources.ground, renderer, 0, 880, 200, 250, 0, false);
	grounds.push_back(Ground);  

	auto Ground1 = new Entity(_MyRessources.ground, renderer, 300, 820, 100, 300, 0, false);
	grounds.push_back(Ground1); 

	auto Ground2 = new Entity(_MyRessources.ground, renderer, 500, 800, 150, 50, 0, false);
	grounds.push_back(Ground2); 

	auto Ground3 = new Entity(_MyRessources.ground, renderer, 700, 830, 200, 40, 0, false);
	grounds.push_back(Ground3); 

	auto Ground4 = new Entity(_MyRessources.ground, renderer, 1000, 780, 200, 120, 0, false);
	grounds.push_back(Ground4); 

	auto Ground5 = new Entity(_MyRessources.ground, renderer, 1100, 730, 200, 150, 0, false);
	grounds.push_back(Ground5); 

	auto Ground6 = new Entity(_MyRessources.ground, renderer, 890, 670, 140, 40, 0, false);
	grounds.push_back(Ground6); 

	auto Ground7 = new Entity(_MyRessources.ground, renderer, 830, 620, 100, 40, 0, false);
	grounds.push_back(Ground7);  

	auto Ground8 = new Entity(_MyRessources.ground, renderer, 1050, 580, 200, 20, 0, false);
	grounds.push_back(Ground8); 

	auto Ground9 = new Entity(_MyRessources.ground, renderer, 1350, 550, 200, 600, 0, false);
	grounds.push_back(Ground9);  
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
	playerParallax->render();

	for (auto ground : grounds) {
		ground->render(*camera);
	}
	Player->render(*camera);
	SDL_RenderPresent(renderer);
}

void Play::update(const bool* keys, float dt) {
	if (Player) {
		playerParallax->update(Player->rect.x, Player->rect.y);
		Player->update(keys, dt);
		Player->collision(grounds);
		//Player->collisionHorizontal(grounds);
		Player->updateState(keys);
		Player->updateAnimation(dt);
		camera->setCameraOnPlayer(*Player);
	}
}

void Play::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	if (_myKeys->myKeys[SDL_SCANCODE_ESCAPE]) {
		currentScene = menu;
	}
}