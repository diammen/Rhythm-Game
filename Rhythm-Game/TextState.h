#pragma once
#include <raylib.h>
enum TStates
{
	Idle = 0,
	Selected,
	Return
};
class TextState
{
private:
	TextState();
	TextState(TextState const&);
	void operator=(TextState const&) {}
	TStates state = Idle;
public:
	TStates getState();
	void setState(TStates newState);
	static TextState& GetInstance();
	~TextState();
};