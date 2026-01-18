#include "Menu.h"
Menu::Menu(SDL_Renderer* _rend) {
	renderer = _rend;
}

Menu::~Menu() {
	
}

void Menu::displayScene(LoadRessources& _MyRessources) {
	
	SDL_RenderClear(renderer);

	if (_MyRessources.bg_layer4) {  // Vérifiez que la texture existe
		SDL_RenderTexture(renderer, _MyRessources.bg_layer4, nullptr, nullptr);
	}

	SDL_RenderPresent(renderer);
}
