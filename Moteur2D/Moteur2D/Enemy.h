#pragma once

#include "GameObject.h"
#include "globals.h"

class Enemy : public GameObject {
private:
	Physics physicsEnemy;
public:
	Enemy();
	Enemy(SDL_Texture* _MyTexture, SDL_Renderer* rend, float x, float y, float w, float h, float _speed);
	virtual ~Enemy();
	void render(Camera& camera) override;
	void update(const bool* keys, float dt) override;
	void colliders(std::vector<GameObject*>& colliders) override;
};

