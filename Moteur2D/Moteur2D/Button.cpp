#include "Button.h"

Button::Button(SDL_Window* _window, SDL_Renderer* _renderer, SDL_Texture* _Texture, float x, float y, float scale) {
	window = _window;
	Texture = _Texture;
	renderer = _renderer;

	float w, h;
	SDL_GetTextureSize(Texture, &w, &h);

	int wW, hW;
	SDL_GetWindowSize(window, &wW, &hW);

	float centeredX = (wW / 2) - (w * scale / 2);
	float centeredY = (hW / 2) - (h * scale / 2);

	centeredX += x;
	centeredY += y;

	buttonRect = { centeredX, centeredY, w * scale, h * scale };
}

Button::~Button() {

}

bool Button::isClicked(SDL_Event& event) {

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

void Button::render() {
	if (Texture) {
		SDL_RenderTexture(renderer, Texture, nullptr, &buttonRect);
	}
}