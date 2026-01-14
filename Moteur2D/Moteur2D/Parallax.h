#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "Entity.h"

struct ParallaxLayer {
    SDL_Texture* texture;
    float speed;
    float offsetX;
    float offsetY;
};

class Parallax {
public:
    std::vector<ParallaxLayer> layers;
    SDL_Renderer* renderer;
    float screenWidth;
    float screenHeight;
    Parallax(SDL_Renderer* rend, float sw, float sh);
    void addLayer(SDL_Texture* texture, float scrollSpeed);
    void update(float playerX, float playerY);
    void render();  // Prend le joueur au lieu de la caméra
    ~Parallax();
};