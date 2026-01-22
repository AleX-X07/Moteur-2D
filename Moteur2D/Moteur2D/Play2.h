#pragma once
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "Scene.h"
#include "Camera.h"
#include "Parallax.h"

class Play2 : public Scene {
private:
    Player* myPlayer;
    std::vector<GameObject*> gameObject;
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

