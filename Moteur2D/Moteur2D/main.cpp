#include <iostream>
#include <SDL3/SDL.h>

#include "Entity.h"
#include "Camera.h"
#include "LoadRessources.h"
#include "Parallax.h"

int main() {
	int screenWidth = 1920;
	int screenHeight = 1080;

	int levelWidth = 1920*2;
	int levelHeight = 1080*2;

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
	parallax.addLayer(MyRessources.bg_layer3, 10.0f); // Lointain = lent
	//parallax.addLayer(MyRessources.bg_layer2, 20.0f); // Moyen
	parallax.addLayer(MyRessources.bg_layer1, 80.0f); // Proche = rapide
	
	//Delta time
	float dt = 1;

	// FPS
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	Uint64 frameStart;
	int frameTime;
	Uint64 last_time = SDL_GetTicks();

	int w, h;

	Entity Player = Entity(MyRessources.player, renderer);

	Player.setColor(0, 255, 0, 255);
	Entity Ground = Entity(nullptr, renderer, 0, 590, 1920, 80, 0, false);
	Ground.setColor(255, 0, 0, 255);
	Entity Ground1 = Entity(nullptr, renderer, 0, 550, 500, 10, 0, false);
	Ground1.setColor(0, 0, 255, 255);
	Entity Ground2 = Entity(nullptr, renderer, 300, 510, 50, 10, 0, false);
	Ground2.setColor(0, 0, 255, 255);
	
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
		
		Player.update(keys, dt);
		parallax.update(dt);

		if (!Player.isColliding(Ground) && !Player.isColliding(Ground1) && !Player.isColliding(Ground2)) {
			Player.downToGround();
			Player.setOnGround(false);
		}
		else 
			Player.setOnGround(true);

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