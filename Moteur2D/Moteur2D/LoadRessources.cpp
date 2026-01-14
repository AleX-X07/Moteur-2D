#include "LoadRessources.h"

// Constructor
LoadRessources::LoadRessources(SDL_Renderer* rend) : renderer(rend) {
    // Initialize of all texture to nullptr
    player = nullptr;
}

// Load all texture
void LoadRessources::loadAllTexture() {
    SDL_Surface* surface;

    // Background Home
    surface = IMG_Load("assets/Kitty.png");
    player = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    //SDL_SetTextureScaleMode(player, SDL_SCALEMODE_NEAREST);
}

// Destructor
LoadRessources::~LoadRessources() {
    // Destroy all texture
    if (player) {
        SDL_DestroyTexture(player);
    }
}