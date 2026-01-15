#include "Menu.h"
Menu::Menu(SDL_Renderer* _rend) {
	renderer = _rend;
}

Menu::~Menu() {
	
}

void Menu::displayScene(LoadRessources& _MyRessources) {
	rect = { 0, 0, 1920, 1080 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_RenderTexture(renderer, _MyRessources.bg_layer4, nullptr, &rect);

	SDL_RenderFillRect(renderer, nullptr);

	SDL_RenderPresent(renderer);
}
