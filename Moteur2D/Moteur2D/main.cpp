#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

#include "Entity.h"
#include "Camera.h"
#include "LoadRessources.h"
#include "Parallax.h"
#include "SceneManager.h"

int main() {
	int screenWidth = 1920;
	int screenHeight = 1080;

	int levelWidth = 1500;
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

	Play playScene(renderer);
	playScene.createGameObjects(MyRessources);
	SceneManager sM = SceneManager(renderer);

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

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		parallax.render();

		playScene.update(keys, dt);
		playScene.displayScene(MyRessources);

		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY)  // Delay for 60FPS
			SDL_Delay(FRAME_DELAY - frameTime);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}