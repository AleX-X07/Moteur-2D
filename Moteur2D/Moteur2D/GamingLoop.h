#pragma once
#include <SDL3/SDL.h>

class GamingLoop
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	int windowX = 1920;
	int windowY = 1080;

public:

	bool loopTrue = true;

	GamingLoop();
	~GamingLoop();

	void setWindowXY(int _x, int _y);
	void displayWindow();
};

