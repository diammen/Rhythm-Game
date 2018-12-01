#pragma once
enum states
{
	Idle = 0,
	Active,
	Return,
	Finish,
	Beat
};
class textSM
{
protected:
	states state = Idle;
public:
	void setState(states newState);
	states getState();
};