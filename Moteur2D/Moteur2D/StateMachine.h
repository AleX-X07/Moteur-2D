#pragma once

class StateMachineScreen
{
public:
	enum ScreenState {
		Menu,
		Play,
		Pause,
		GameOver,
		Quit,
	};

	ScreenState currentState;

	StateMachineScreen();

	virtual void setState() = 0;

	ScreenState getState();
};

