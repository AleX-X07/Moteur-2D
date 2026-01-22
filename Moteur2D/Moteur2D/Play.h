#pragma once

#include <vector>

#include "globals.h"
#include "Scene.h"
#include "Camera.h"
#include "Parallax.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Play : public Scene{
private:
    Player* myPlayer;
    Enemy* Enemy1;
    std::vector<GameObject*> gameObject;
	Camera* camera;
    bool isCreatedGRound = false;
    Parallax* playerParallax;

public:
    Play(SDL_Renderer* rend, SDL_Window* win);
    ~Play();

    void createGameObjects(LoadRessources& _MyRessources);
    void displayScene(LoadRessources& _MyRessources) override;
	void update(const bool* keys, float dt);
    void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) override;
};