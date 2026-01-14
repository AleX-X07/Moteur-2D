#pragma once
#include <iostream>
#include "StateMachine.h"

class Menu : public StateMachineScreen
{
	int a;

	void setState() override;
	void displayMenu();
};

