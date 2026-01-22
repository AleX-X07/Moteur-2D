#include "setTime.h"

setTime::setTime(int _FPS) {
	FPS = _FPS;
	FRAME_DELAY = 1000 / FPS;
	last_time = SDL_GetTicks();
}

void setTime::calculTime() {
	dt = (SDL_GetTicks() - last_time) / 1000.0f;
	last_time = SDL_GetTicks();
	frameStart = SDL_GetTicks();
}

void setTime::waitForTime() {

	frameTime = SDL_GetTicks() - frameStart;

	if (frameTime < FRAME_DELAY)
		SDL_Delay(FRAME_DELAY - frameTime);
}