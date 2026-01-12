#include <iostream>
#include "GamingLoop.h"
GamingLoop MyGamingLoop;
int main() {
	MyGamingLoop.gamingLoop();
	SDL_Quit();
	return 0;
}