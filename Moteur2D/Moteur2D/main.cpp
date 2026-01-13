#include <iostream>
#include <SDL3/SDL.h>

#include "GamingLoop.h"
#include "Entity.h"

int main() {
	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("SHOOT'EM UP", 1920, 1080, SDL_WINDOW_FULLSCREEN, &window, &renderer);
	
	//Delta time
	float dt = 1;

	int w, h;

	Entity Box = Entity(renderer);
	Entity Box2 = Entity(texture, renderer);

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
		Box.update(keys, dt);
		SDL_GetWindowSize(window, &w, &h);
		Box.clampToScreen(w, h);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, NULL);
		Box.render();
		SDL_RenderPresent(renderer);
	}
                                 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}