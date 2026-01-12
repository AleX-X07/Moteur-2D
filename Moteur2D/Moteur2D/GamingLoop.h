#pragma once
#include <SDL3/SDL.h>

class GamingLoop
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int windowX = 1920;
	int windowY = 1080;

	bool loopTrue = true;

public:

	GamingLoop();
	~GamingLoop();

	void setWindowXY(int _x, int _y);
	void gamingLoop();
};

