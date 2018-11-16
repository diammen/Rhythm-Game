#include "textStateMachine.h"

void textSM::setState(states newState)
{
	state = newState;
}

states textSM::getState()
{
	return state;
}