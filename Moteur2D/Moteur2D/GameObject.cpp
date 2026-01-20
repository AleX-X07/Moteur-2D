#include "GameObject.h"
#include "Camera.h"

GameObject::GameObject() {
	texture = nullptr;
	renderer = nullptr;
	rect = { 0,0,0,0 };
}
GameObject::GameObject(SDL_Renderer* ren, SDL_Texture* tex, float x, float y, float w, float h) {
	texture = tex;
	renderer = ren;
	rect = { x,y,w,h };
}

GameObject::~GameObject() {

}

bool GameObject::isColliding(GameObject& gameObject) {
	if (rect.x + rect.w < gameObject.rect.x ||
		rect.x > gameObject.rect.x + gameObject.rect.w ||
		rect.y + rect.h < gameObject.rect.y ||
		rect.y > gameObject.rect.y + gameObject.rect.h)
		return false;
	return true;
}

void GameObject::render(Camera& camera) {
	SDL_FRect screenRect = camera.worldToScreen(rect);

	if (texture) {
		SDL_RenderTexture(renderer, texture, nullptr, &screenRect);
	}
}

void GameObject::update(float dt) {

}