#pragma once
#include <raylib.h>
class Transition
{
private:
	Transition();
	Transition(Transition const&);
	void operator=(Transition const&) {}
	Rectangle rec;
	Color color;
	int tick;
public:
	bool entering;
	bool Fade();
	bool Slide();
	static Transition& GetInstance();
	~Transition();
};