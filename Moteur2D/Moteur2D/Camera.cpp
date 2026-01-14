#include "Camera.h"
Camera::Camera(float sw, float sh, float lw, float lh) {

	screenWidth = sw;
	screenHeight = sh;
	levelWidth = lw;
	levelHeight = lh;
	sizeC = { 0,0,sw,sh }; 
}

void Camera::setCameraOnPlayer(Entity& player) {
	// Center on player
	sizeC.x = (player.rect.x + player.rect.w / 2) - screenWidth / 2;
	sizeC.y = (player.rect.y + player.rect.h / 2) - screenHeight / 2;

	// Lock screen in world
	if (sizeC.x < 0) {
		sizeC.x = 0;
	}
	if (sizeC.y < 0) {
		sizeC.y = 0;
	}
	if (sizeC.x + sizeC.w > levelWidth) {
		sizeC.x = levelWidth - sizeC.w;
	}
	if (sizeC.y + sizeC.h > levelHeight) {
		sizeC.y = levelHeight - sizeC.h;
	}
}

SDL_FRect Camera::worldToScreen(SDL_FRect& worldRect)  {
	return {
		worldRect.x - sizeC.x,
		worldRect.y - sizeC.y,
		worldRect.w,
		worldRect.h
	};
}