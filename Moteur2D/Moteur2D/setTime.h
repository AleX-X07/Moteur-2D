#pragma once
#include <iostream>
#include <SDL3/SDL.h>

struct setTime
{
	float dt;
	Uint64 frameStart;
	Uint64 last_time;
	int FPS;
	int FRAME_DELAY;
	int frameTime;

	setTime(int _FPS);
	void calculTime();
	void waitForTime();
};