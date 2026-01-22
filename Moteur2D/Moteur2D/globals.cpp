#include "globals.h"

keys::keys(){
	myKeys = nullptr;
}

keys::~keys() {

}

void keys::initKeys(const bool* _keys) {
	myKeys = _keys;
}


