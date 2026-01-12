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
	SDL_Color color;

public: 

	SDL_FRect rect;

	//Constructor/Destructor
	Entity();
	Entity(SDL_Texture* MyTexture);
	~Entity();

	void setRect();

	// Render/Update
	void render(SDL_Renderer* renderer);
	void update(float dt);

	//StateMachine

};

