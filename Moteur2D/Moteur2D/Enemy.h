#pragma once

#include "GameObject.h"
#include "globals.h"

enum class EnemyState {
	movingLeft,
	movingRight,
};

class Enemy : public GameObject {
private:
	Physics physicsEnemy;
	Animation animationEnemy;
	EnemyState currentState = EnemyState::movingLeft;
	EnemyState previousState = EnemyState::movingLeft;

	bool isBorderLeft = true;
public:
	Enemy();
	Enemy(SDL_Texture* _MyTexture, SDL_Renderer* rend, float x, float y, float w, float h, float _speed);
	virtual ~Enemy();

	void updateAnimationEnemy(float dt);
	void updateStateEnemy() override;

	void render(Camera& camera) override;
	void update(const bool* keys, float dt) override;
	void colliders(std::vector<GameObject*>& colliders) override;
};
