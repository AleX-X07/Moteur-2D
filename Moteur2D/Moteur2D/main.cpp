#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

#include "Entity.h"
#include "Camera.h"
#include "LoadRessources.h"
#include "Parallax.h"
#include "SceneManager.h"
#include "globals.h"

int main() {
	int screenWidth = 1920;
	int screenHeight = 1080;

	int levelWidth = 1920;
	int levelHeight = 1080;

	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Lost Meow", screenWidth, screenHeight, NULL, &window, &renderer);

	//Ressources
	LoadRessources MyRessources(renderer);
	MyRessources.loadAllTexture();

	Camera camera(screenWidth, screenHeight, levelWidth, levelHeight);

	Parallax parallax(renderer, screenWidth, screenHeight);
	parallax.addLayer(MyRessources.bg_layer1, 0.1f); // Proche = rapide
	parallax.addLayer(MyRessources.bg_layer2, 0.3f); // Moyen
	parallax.addLayer(MyRessources.bg_layer3, 0.5f); // Lointain = lent
	parallax.addLayer(MyRessources.bg_layer4, 0.8f); // Lointain = lent

	//Delta time
	float dt = 1;

	// FPS
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	Uint64 frameStart;
	int frameTime;
	Uint64 last_time = SDL_GetTicks();

	int w;
	int h;

	auto Player = Entity(MyRessources.player, renderer);

	Player.setColor(0, 255, 0, 255);

	auto Ground = Entity(MyRessources.ground, renderer, 0, 880, 200, 250, 0, false);
	Ground.setColor(255, 0, 0, 255);
	auto Ground1 = Entity(MyRessources.ground, renderer, 300, 820, 100, 300, 0, false);
	Ground1.setColor(0, 0, 255, 255);
	auto Ground2 = Entity(MyRessources.ground, renderer, 500, 800, 150, 50, 0, false);
	Ground2.setColor(0, 0, 255, 255);
	auto Ground3 = Entity(MyRessources.ground, renderer, 700, 830, 200, 40, 0, false);
	Ground3.setColor(0, 0, 255, 255);
	auto Ground4 = Entity(MyRessources.ground, renderer, 1000, 780, 200, 120, 0, false);
	Ground4.setColor(0, 0, 255, 255);
	auto Ground5 = Entity(MyRessources.ground, renderer, 1100, 730, 200, 150, 0, false);
	Ground5.setColor(0, 0, 255, 255);
	auto Ground6 = Entity(MyRessources.ground, renderer, 890, 670, 140, 40, 0, false);
	Ground6.setColor(0, 0, 255, 255);
	auto Ground7 = Entity(MyRessources.ground, renderer, 830, 620, 100, 40, 0, false);
	Ground7.setColor(0, 0, 255, 255);
	auto Ground8 = Entity(MyRessources.ground, renderer, 1050, 580, 200, 20, 0, false);
	Ground8.setColor(0, 0, 255, 255);
	auto Ground9 = Entity(MyRessources.ground, renderer, 1350, 550, 200, 600, 0, false);
	Ground9.setColor(0, 0, 255, 255);

	std::vector<Entity*> grounds = { &Ground, &Ground1, &Ground2, &Ground3, &Ground4, &Ground5, &Ground6, &Ground7, &Ground8, &Ground9 };

	//SceneManager
	SceneManager sM = SceneManager(renderer,window);
	keys myKeys;

	//GameLoop
	bool loopTrue = true;
	while (loopTrue) {

		float dt = (SDL_GetTicks() - last_time) / 1000.0f;
		last_time = SDL_GetTicks();
		frameStart = SDL_GetTicks();
		
		const bool* keys = SDL_GetKeyboardState(nullptr);

		myKeys.initKeys(keys);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			sM.manageState(event, &myKeys);

			if (sM.currentState == SceneState::quit) {
				loopTrue = false;
			}
		}

		sM.displayState();

		/*SDL_GetWindowSize(window, &w, &h);
		
		Player.collisionHorizontal(grounds);
		Player.collision(grounds);

		Player.update(keys, dt);
		Player.updateState(keys);
		Player.updateAnimation(dt);
		parallax.update(Player.rect.x, Player.rect.y);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, nullptr);

		parallax.render();

		for (auto& ground : grounds) {
			ground->render(camera);
		}

		camera.setCameraOnPlayer(Player);
		Player.clampToScreen(levelWidth, levelHeight);
		Player.render(camera);
		

		SDL_RenderPresent(renderer);*/

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY)  // Delay for 60FPS
			SDL_Delay(FRAME_DELAY - frameTime);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}