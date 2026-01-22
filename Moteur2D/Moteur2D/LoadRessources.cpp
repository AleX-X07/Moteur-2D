#include "LoadRessources.h"

// Constructor
LoadRessources::LoadRessources(SDL_Renderer* rend) : renderer(rend) {
    // Initialize of all texture to nullptr
    player = nullptr;
    ground = nullptr;
    enemy = nullptr;
    bg_layer1 = nullptr;
    bg_layer2 = nullptr;
    bg_layer3 = nullptr;
    bg_layer4 = nullptr;

    background_menu = nullptr;

}

// Load one texture
void LoadRessources::loadTexture(const char* _path, SDL_Texture*& _MyTexture)
{
    SDL_Surface* surface;

    surface = IMG_Load(_path);
    _MyTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

// Load all texture
void LoadRessources::loadAllTexture() {
    
    loadTexture("assets/sprite_Kitty.png", player);
    loadTexture("assets/dirt.png", ground);
    loadTexture("assets//sprite_Kitty.png", enemy);
    loadTexture("assets/BG_layer1.png", bg_layer1);
    loadTexture("assets/BG_layer2.png", bg_layer2);
    loadTexture("assets/BG_layer3.png", bg_layer3);
    loadTexture("assets/BG_layer4.png", bg_layer4);
    loadTexture("assets/Menu/play.png", play_button);
    SDL_SetTextureScaleMode(play_button, SDL_SCALEMODE_NEAREST);
    loadTexture("assets/Menu/exit.png", exit_button);
    SDL_SetTextureScaleMode(exit_button, SDL_SCALEMODE_NEAREST);
    loadTexture("assets/Menu/menu_bg.jpg", background_menu);
    SDL_SetTextureScaleMode(background_menu, SDL_SCALEMODE_NEAREST);

    mesTexture = { player, ground, enemy, bg_layer1, bg_layer2, bg_layer3, bg_layer4, play_button, exit_button, background_menu };

}

// Destructor
LoadRessources::~LoadRessources() {
    // Destroy all texture
    for (auto t : mesTexture) {
        if (t) {
            SDL_DestroyTexture(t);
        }
    }
}