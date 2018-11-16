#pragma once
enum states
{
	Idle = 0,
	Active,
	Return,
};
class stateMachine
{
protected:
	states state = Idle;
public:
	virtual void setState(states newState) = 0;
	virtual states getState() = 0;
};