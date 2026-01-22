#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

#include "SceneManager.h"
#include "globals.h"
#include "setTime.h"

int main() {

	// Creation Window
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Lost Meow", screenWidth, screenHeight, NULL, &window, &renderer);

	//SceneManager
	SceneManager sM = SceneManager(renderer,window);
	keys myKeys;

	setTime time = setTime(120); // Lock frame rate at 120fps

	//GameLoop
	bool loopTrue = true;
	while (loopTrue) {

		time.calculTime();
		
		const bool* keys = SDL_GetKeyboardState(nullptr);

		myKeys.initKeys(keys);

		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			sM.manageState(event, &myKeys);

			if (sM.currentState == SceneState::quit) {
				loopTrue = false;
			}
		}

		sM.updateState(keys, time.dt);
		sM.displayState();

		time.waitForTime();


	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}