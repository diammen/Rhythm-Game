#pragma once
#include <raylib.h>
#include "helper.h"
class Transition
{
private:
	Transition();
	Transition(Transition const&);
	void operator=(Transition const&) {}
	Rectangle rec;
	Color color;
	float elapsed;
	float duration;
public:
	bool entering;
	bool Fade();
	bool Slide();
	static Transition& GetInstance();
	~Transition();
};