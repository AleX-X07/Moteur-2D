#include "Camera.h"
Camera::Camera(float sw, float sh, float lw, float lh) {

    screenWidth = sw;
    screenHeight = sh;
    levelWidth = lw;
    levelHeight = lh;
    sizeC = { 0,0,sw,sh };
}

void Camera::setCameraOnPlayer(Entity& player) {

    float viewW = screenWidth / zoom;
    float viewH = screenHeight / zoom;

    sizeC.w = viewW;
    sizeC.h = viewH;

    sizeC.x = (player.rect.x + player.rect.w / 2) - viewW / 2;
    sizeC.y = (player.rect.y + player.rect.h / 2) - viewH / 2;

    // Clamp inside world
    if (sizeC.x < 0) sizeC.x = 0;
    if (sizeC.y < 0) sizeC.y = 0;
    if (sizeC.x + sizeC.w > levelWidth) sizeC.x = levelWidth - sizeC.w;
    if (sizeC.y + sizeC.h > levelHeight) sizeC.y = levelHeight - sizeC.h;
}


SDL_FRect Camera::worldToScreen(SDL_FRect& worldRect) {
    return {
        (worldRect.x - sizeC.x) * zoom,
        (worldRect.y - sizeC.y) * zoom,
        worldRect.w * zoom,
        worldRect.h * zoom
    };
}