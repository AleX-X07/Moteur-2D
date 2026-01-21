#include "globals.h"

std::vector<GameObject*> myGameObject;

keys::keys(){
	myKeys = nullptr;
}

keys::~keys() {

}

void keys::initKeys(const bool* _keys) {
	myKeys = _keys;
}


