#include "Menu.h"
Menu::Menu(SDL_Renderer* rend, SDL_Window* win) {
	renderer = rend;
	window = win;
}

Menu::~Menu() {

}

bool isClicked(SDL_Event& event, SDL_FRect& buttonRect) {
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			float mouseX = event.button.x;
			float mouseY = event.button.y;
			if (mouseX >= buttonRect.x &&
				mouseX <= buttonRect.x + buttonRect.w &&
				mouseY >= buttonRect.y &&
				mouseY <= buttonRect.y + buttonRect.h) {
				return true;
			}
		}
	}
	return false;
}

void Menu::addButton(SDL_Texture* MyTexture, float x, float y, float scale, SceneState _MyButtonType) {
	Button MyButton(window, renderer, MyTexture, x, y, scale);
	MyButton.MyButtonType = _MyButtonType;
	vecButton.emplace_back(MyButton);
}


void Menu::displayScene(LoadRessources& _MyRessources) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	if (!buttonsCreated) {
		addButton(_MyRessources.play_button, 0, -100, 10, play);
		addButton(_MyRessources.exit_button, 0, 100, 7.5, quit);
		buttonsCreated = true;
	}
	
	for (auto b : vecButton) {
		b.render();
	}

	SDL_RenderPresent(renderer);
}

void Menu::nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) {
	for (auto b : vecButton) {
		if (b.isClicked(event)) {
			currentScene = b.MyButtonType;
		}
	}
}