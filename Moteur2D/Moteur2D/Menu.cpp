#include "Menu.h"

void Menu::setState() {
	if (a == 1) {
		currentState = Play;
	}
	else if (a == 2) {
		currentState = Quit;
	}
}

void Menu::displayMenu() {
	std::cout << "Vous êtes dans le menu.\n";
	std::cout << "1. pour jouer / 2. pour quitter.";
	std::cin >> a;
}