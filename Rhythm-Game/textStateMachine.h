#pragma once
#include "stateMachine.h"

class textSM : public stateMachine
{
public:
	void setState(states newState);
	states getState();
};