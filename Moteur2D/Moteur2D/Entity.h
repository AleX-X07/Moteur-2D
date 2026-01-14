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
	float jumpForce;

	// Object collision
	bool collide;

	//Object texture
	SDL_Texture* MyTexture;
	SDL_Renderer* renderer;
	SDL_Color color;

	float cooldownJump;
	bool onGround;

	// Physics variables
	float velocityY;
	float gravity;

	Uint64 last_time = SDL_GetTicks();
	float dt = (SDL_GetTicks() - last_time) / 1000.0f;

public:

	SDL_FRect rect;

	//Constructor/Destructor
	Entity();
	Entity(SDL_Renderer* renderer);
	Entity(SDL_Texture* MyTexture, SDL_Renderer* renderer, float x, float y, float w, float h, int speed, bool collide);
	~Entity();

	void getPosition(float& x, float& y) const;
	bool isColliding(const Entity& entity) const;
	void downToGround();
	void setOnGround(bool value);

	// Render/Update
	void render();
	void update(const bool* keys, float dt);
	void clampToScreen(int windowX, int windowY);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	//StateMachine
};