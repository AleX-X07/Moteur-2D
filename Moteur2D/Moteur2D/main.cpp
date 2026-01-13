#include <iostream>
#include <SDL3/SDL.h>

#include "GamingLoop.h"
#include "Entity.h"

int main() {
	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Lost Meow", 1920, 1080, SDL_WINDOW_FULLSCREEN, &window, &renderer);
	
	//Delta time
	float dt = 1;

	int w, h;

	Entity Box = Entity(renderer);
	Box.setColor(0, 255, 0, 255);
	Entity Ground = Entity(nullptr, renderer, 0, 600, 1920, 80, 0, false);
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

		const bool* keys = SDL_GetKeyboardState(NULL);
		
		SDL_GetWindowSize(window, &w, &h);
		
		if (!Box.isColliding(Ground) && !Box.isColliding(Ground1)) {
			Box.downToGround();
			Box.setOnGround(false);
		}
		else {
			Box.setOnGround(true);
		}

		Box.clampToScreen(w, h);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, NULL);

		Box.update(keys, dt);	
		Box.render();
		Ground.render();
		Ground1.render();
		SDL_RenderPresent(renderer);
	}
                                 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}