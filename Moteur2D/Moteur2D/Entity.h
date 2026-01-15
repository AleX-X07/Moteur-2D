#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>

class Camera;

enum class PlayerState {
	idle,
	movingLeft,
	movingRight,
	jumpingLeft,
	jumpingRight,
	fallingLeft,
	fallingRight
};

class Entity {
private:
	float sizeX;
	float sizeY;
	float posX;
	float posY;

	int speed;
	float jumpForce;
	bool collide;

	SDL_Texture* MyTexture;
	SDL_Renderer* renderer;
	SDL_Color color;

	float cooldownJump;
	bool onGround;

	float velocityY;
	float velocityX;
	float gravity;

	Uint64 last_time = SDL_GetTicks();
	float dt = (SDL_GetTicks() - last_time) / 1000.0f;

	PlayerState currentState = PlayerState::idle;
	PlayerState previousState = PlayerState::idle;

	int currentFrame = 0;
	float animationTimer = 0.0f;
	float frameDuration = 0.2f;
	int maxFrames = 4;
	float spriteWidth = 127.8f;
	float spriteHeight = 127.8f;

public:

	SDL_FRect rect;

	Entity();
	Entity(SDL_Texture* MyTexture, SDL_Renderer* renderer);
	Entity(SDL_Texture* MyTexture, SDL_Renderer* renderer, float x, float y, float w, float h, int speed, bool collide);
	~Entity();

	void getPosition(float& x, float& y) const;
	bool isColliding(const Entity& entity) const;
	void downToGround();
	void setOnGround(bool value);

	void updateState(const bool* keys);
	PlayerState getCurrentState() const;
	void updateAnimation(float dt);

	void collision(const std::vector<Entity*>& colliders);
	void collisionHorizontal(const std::vector<Entity*>& colliders);

	// Render/Update
	void render(Camera& camera);
	void update(const bool* keys, float dt);
	void clampToScreen(int windowX, int windowY);
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
};