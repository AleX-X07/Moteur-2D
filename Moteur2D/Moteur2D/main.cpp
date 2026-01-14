#include <iostream>
#include <SDL3/SDL.h>

#include "GamingLoop.h"
#include "Entity.h"
#include "Camera.h"

int main() {
	int screenWidth = 640;
	int screenHeight = 480;

	int levelWidth = 1920;
	int levelHeight = 1080;

	Camera camera(screenWidth, screenHeight, levelWidth, levelHeight);

	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Lost Meow", screenWidth, screenHeight, NULL, &window, &renderer);
	
	//Delta time
	float dt = 1;

	// FPS
	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	Uint64 frameStart;
	int frameTime;
	Uint64 last_time = SDL_GetTicks();

	int w, h;

	Entity Box = Entity(renderer);
	Box.setColor(0, 255, 0, 255);
	Entity Ground = Entity(nullptr, renderer, 0, 590, 1920, 80, 0, false);
	Ground.setColor(255, 0, 0, 255);
	Entity Ground1 = Entity(nullptr, renderer, 0, 580, 500, 10, 0, false);
	Ground1.setColor(0, 0, 255, 255);
	
	//GameLoop
	bool loopTrue = true;
	while (loopTrue) {

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				loopTrue = false;
			}
		}

		float dt = (SDL_GetTicks() - last_time) / 1000.0f;
		last_time = SDL_GetTicks();
		frameStart = SDL_GetTicks();


		const bool* keys = SDL_GetKeyboardState(NULL);
		
		SDL_GetWindowSize(window, &w, &h);
		
		Box.update(keys, dt);

		if (!Box.isColliding(Ground) && !Box.isColliding(Ground1)) {
			Box.downToGround();
			Box.setOnGround(false);
		}
		else {
			Box.setOnGround(true);
		}

		camera.setCameraOnPlayer(Box);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, NULL);

		Box.renderPlayer(camera);
		Ground.renderPlayer(camera);
		Ground1.renderPlayer(camera);
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < FRAME_DELAY) { // Delay for 60FPS
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
                                 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}