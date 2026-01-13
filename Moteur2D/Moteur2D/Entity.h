#pragma once
#include <SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>

class Entity
{
	//Size object
	float sizeX;
	float sizeY;

	//Position object
	float posX;
	float posY;

	// Speed object
	int speed;

	// Object collision
	bool collide;

	//Object texture
	SDL_Texture* MyTexture;
	SDL_Renderer* renderer;
	SDL_Color color = { 255,255,255,255 };

public: 

	SDL_FRect rect;

	//Constructor/Destructor
	Entity();
	Entity(SDL_Renderer* renderer);
	Entity(SDL_Texture* MyTexture, SDL_Renderer* renderer);
	Entity(SDL_Texture* MyTexture, SDL_Renderer* renderer, float x, float y, float w, float h, int speed, bool collide);
	~Entity();

	// Render/Update
	void render();
	void update(const bool* keys, float dt);
	void clampToScreen(int windowX, int windowY);
	//StateMachine
};

