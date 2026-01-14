#include "StateMachine.h"

StateMachineScreen::StateMachineScreen() {

}

ScreenState StateMachineScreen::getState() {
	return currentState;
}