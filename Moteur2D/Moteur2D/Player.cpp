#include "Player.h"

Player::Player() : GameObject() {

	texture = nullptr;
	renderer = nullptr;
	rect = { 0,0,0,0 };
	myPhysics = { 0,0,0,0,0,0,false };
	currentState = PlayerState::idle;
}

Player::Player(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h, float _speed) : GameObject() {
	texture = tex;
	renderer = ren;
	rect = { x,y,w,h };
	myPhysics = { _speed, 350.0f, 900.0f, 0, 0, 0, false };
	currentState = PlayerState::idle;
}


Player::~Player() {

}

void Player::render(Camera& camera) {

}

void Player::update(float dt) {

}