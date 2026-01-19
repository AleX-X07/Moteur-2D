#pragma once

#include "Entity.h"
#include "Scene.h"
#include "Camera.h"
#include <vector>

class Play : public Scene
{
private:
    Entity* Player;
    std::vector<Entity*> grounds;
	Camera* camera;
    bool isCreatedGRound = false;

public:
    Play(SDL_Renderer* rend, SDL_Window* win);
    ~Play();

    void createGameObjects(LoadRessources& _MyRessources);
    void displayScene(LoadRessources& _MyRessources) override;
	void update(const bool* keys, float dt);
    void nextScene(SceneState& currentScene, SDL_Event& event, keys* _myKeys) override;
};