#include "Play.h"

Play::Play(SDL_Renderer* _rend) {
	renderer = _rend;
}

Play::~Play() {

}

void Play::displayScene(LoadRessources& _MyRessources) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderFillRect(renderer, nullptr);

	SDL_RenderPresent(renderer);
}

