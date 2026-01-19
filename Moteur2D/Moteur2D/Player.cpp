#include "Player.h"

Player::Player() : GameObject() {
	texture = nullptr;
	renderer = nullptr;
	rect = { 0,0,0,0 };
	myPhysics = { 0,0,0,0,0,0 };
	isGround = false;
}

//Player::~Player() {
//
//}
