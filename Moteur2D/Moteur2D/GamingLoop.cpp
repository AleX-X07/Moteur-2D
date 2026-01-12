#include "GamingLoop.h"

GamingLoop::GamingLoop() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Moteur2D", windowX, windowY, NULL, &window, &renderer);
}

GamingLoop::~GamingLoop() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}
void GamingLoop::setWindowXY(int _x, int _y) {
	windowX = _x;
	windowY = _y;
}

void GamingLoop::gamingLoop() {
	while (loopTrue) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, NULL);
		SDL_RenderPresent(renderer);
	}
}