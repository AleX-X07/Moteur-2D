#include "Menu.h"
Menu::Menu(SDL_Renderer* _rend) {
	renderer = _rend;
}

Menu::~Menu() {
	
}

void Menu::displayScene() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderFillRect(renderer, nullptr);

	SDL_RenderPresent(renderer);
}
