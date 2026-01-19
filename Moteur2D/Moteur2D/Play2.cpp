#include "Play2.h"

Play2::Play2(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
	Player = nullptr;
	camera = new Camera();
	int w;
	int h;
	SDL_GetWindowSize(win, &w, &h);
	playerParallax = new Parallax(rend, w, h);
}

Play2::~Play2() {
	delete Player;
	for (auto ground : grounds) {
		delete ground;
	}
	delete camera;
	delete playerParallax;
}

void Play2::createGameObjects(LoadRessources& _MyRessources) {
	Player = new Entity(_MyRessources.player, renderer);
	Player->setColor(0, 255, 0, 255);
	Player->rect.x = 50;
	Player->rect.y = 820;

	auto Ground = new Entity(_MyRessources.ground, renderer, 0, 880, 200, 250, 0, false);
	grounds.push_back(Ground);

	auto Ground1 = new Entity(_MyRessources.ground, renderer, 300, 820, 100, 300, 0, false);
	grounds.push_back(Ground1);

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

	for (auto ground : grounds) {
		ground->render(*camera);
	}
	Player->render(*camera);
	SDL_RenderPresent(renderer);
}

void Play2::update(const bool* keys, float dt) {
	if (Player) {
		playerParallax->update(Player->rect.x, Player->rect.y);
		Player->update(keys, dt);
		Player->collision(grounds);
		Player->updateState(keys);
		Player->updateAnimation(dt);
		Player->clampToScreen(levelWidth + 50, levelHeight + 50);
		camera->setCameraOnPlayer(*Player);
		Player->respawn();
	}
}

void Play2::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	if (_myKeys->myKeys[SDL_SCANCODE_ESCAPE]) {
		currentScene = menu;
	}
}
