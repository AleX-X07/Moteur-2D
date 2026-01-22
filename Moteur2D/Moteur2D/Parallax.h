#pragma once
#include <SDL3/SDL.h>
#include <vector>

#include "globals.h"

class Camera;

struct ParallaxLayer {
    SDL_Texture* texture;
    float speed;
    float offsetX;
    float offsetY;
    SDL_FRect rect;
};

class Parallax {
public:
    std::vector<ParallaxLayer> layers;
    SDL_Renderer* renderer;
    Parallax(SDL_Renderer* rend, float sw, float sh);
    void addLayer(SDL_Texture* texture, float scrollSpeed);
    void render(Camera& camera);
    ~Parallax();
};