#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

#include "Entity.h"
#include "Camera.h"
#include "LoadRessources.h"
#include "Parallax.h"
#include "Scene.h"
#include "Play.h"
#include "Menu.h"
#include "SceneManager.h"

int main() {
	int screenWidth = 1920;
	int screenHeight = 1080;

	int levelWidth = 1920*2;
	int levelHeight = 1080;

	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Lost Meow", screenWidth, screenHeight, NULL, &window, &renderer);

	////Ressources
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
	auto Ground2 = Entity(MyRessources.ground, renderer, 500, 800, 150, 40, 0, false);
	Ground2.setColor(0, 0, 255, 255);
	auto Ground3 = Entity(MyRessources.ground, renderer, 700, 830, 200, 30, 0, false);
	Ground3.setColor(0, 0, 255, 255);
	auto Ground4 = Entity(MyRessources.ground, renderer, 1000, 780, 200, 120, 0, false);
	Ground4.setColor(0, 0, 255, 255);
	
	std::vector<Entity*> grounds = { &Ground, &Ground1, &Ground2, &Ground3, &Ground4 };

	//Scene
	

	SceneManager mySM = SceneManager(renderer);

	//GameLoop
	bool loopTrue = true;
	while (loopTrue) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) 
				loopTrue = false;
		}

		float dt = (SDL_GetTicks() - last_time) / 1000.0f;
		last_time = SDL_GetTicks();
		frameStart = SDL_GetTicks();

		const bool* keys = SDL_GetKeyboardState(nullptr);
		
		SDL_GetWindowSize(window, &w, &h);
		
		
		Player.collisionHorizontal(grounds);
		Player.collision(grounds);

		Player.update(keys, dt);
		Player.updateState(keys);
		Player.updateAnimation(dt);
		parallax.update(Player.rect.x, Player.rect.y);

		camera.setCameraOnPlayer(Player);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, nullptr);

		parallax.render();

		Player.clampToScreen(levelWidth, levelHeight);
		Player.render(camera);
		Ground.render(camera);
		Ground1.render(camera);
		Ground2.render(camera);
		Ground3.render(camera);
		Ground4.render(camera);

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY)  // Delay for 60FPS
			SDL_Delay(FRAME_DELAY - frameTime);

		/*mySM.initKeys(keys);
		mySM.manageState();*/

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}