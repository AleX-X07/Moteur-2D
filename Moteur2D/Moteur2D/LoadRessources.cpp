#include "LoadRessources.h"

// Constructor
LoadRessources::LoadRessources(SDL_Renderer* rend) : renderer(rend) {
    // Initialize of all texture to nullptr
    player = nullptr;
    ground = nullptr;
    bg_layer1 = nullptr;
    bg_layer2 = nullptr;
    bg_layer3 = nullptr;
    bg_layer4 = nullptr;
}

// Load all texture
void LoadRessources::loadAllTexture() {
    SDL_Surface* surface;

    // Background Home
    surface = IMG_Load("assets/sprite_Kitty.png");
    player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("assets/ground.png");
    ground = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_SetTextureScaleMode(ground, SDL_SCALEMODE_NEAREST);

    surface = IMG_Load("assets/BG_layer1.png");
    bg_layer1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("assets/BG_layer2.png");
    bg_layer2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("assets/BG_layer3.png");
    bg_layer3 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    surface = IMG_Load("assets/BG_layer4.png");
    bg_layer4 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

// Destructor
LoadRessources::~LoadRessources() {
    // Destroy all texture
    if (player) {
        SDL_DestroyTexture(player);
    }

    if (ground) {
        SDL_DestroyTexture(ground);
    }
    if (bg_layer1) {
        SDL_DestroyTexture(bg_layer1);
    }
    if (bg_layer2) {
        SDL_DestroyTexture(bg_layer2);
    }
    if (bg_layer3) {
        SDL_DestroyTexture(bg_layer3);
    }
    if (bg_layer4) {
        SDL_DestroyTexture(bg_layer4);
    }
}