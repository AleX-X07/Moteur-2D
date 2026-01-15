#include "Scene.h"


Scene::Scene() {
	renderer = nullptr;
}

Scene::~Scene() {
	SDL_DestroyRenderer(renderer);
}