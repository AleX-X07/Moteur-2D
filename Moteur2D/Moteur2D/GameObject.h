#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>

#include "globals.h"

class Camera;

class GameObject {
protected:
	SDL_FRect rect;
	SDL_Texture* texture;
	SDL_Renderer* renderer;

public:
	GameObject(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h);

	GameObject();
	virtual ~GameObject();

	bool isColliding(GameObject& gameObject);

	SDL_FRect& getRect();

	virtual void colliders();
	virtual void render(Camera& camera);
	virtual void update(const bool* keys, float dt);
};
