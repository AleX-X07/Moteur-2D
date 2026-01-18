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

public:
    Play(SDL_Renderer* _rend);
    ~Play();

    void createGameObjects(LoadRessources& _MyRessources);
    void displayScene(LoadRessources& _MyRessources) override;
	void update(const bool* keys, float dt);

};