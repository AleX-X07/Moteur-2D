#include "Play.h"

Play::Play(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
}

Play::~Play() {

}

void Play::displayScene(LoadRessources& _MyRessources) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderFillRect(renderer, nullptr);

	SDL_RenderPresent(renderer);
}

void Play::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	if (_myKeys->myKeys[SDL_SCANCODE_SPACE]) {
		currentScene = quit;
	}
}

