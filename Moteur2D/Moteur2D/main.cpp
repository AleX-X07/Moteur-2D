#include <iostream>
#include "GamingLoop.h"
#include "Entity.h"
GamingLoop MyGamingLoop;
Entity test;
int main() {
	while (MyGamingLoop.loopTrue) {
		MyGamingLoop.displayWindow();
		test.render();
		test.update();
	}
	SDL_Quit();
	return 0;
}