#pragma once
#include <vector>

#include "Entity.h"
#include "Scene.h"
#include "Camera.h"
#include "Parallax.h"

class Play2 : public Scene {
private:
    Entity* Player;
    std::vector<Entity*> grounds;
    Camera* camera;
    bool isCreatedGRound = false;
    Parallax* playerParallax;

public:
    Play2(SDL_Renderer* rend, SDL_Window* win);
    ~Play2();

    void createGameObjects(LoadRessources& _MyRessources);
    void displayScene(LoadRessources& _MyRessources) override;
    void update(const bool* keys, float dt);
    void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) override;
};

