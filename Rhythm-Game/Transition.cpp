#include "Transition.h"

Transition::Transition() {}
Transition::~Transition() {}

Transition::Transition(Transition const&) {}

bool Transition::Fade()
{
	if (entering)
	{
		elapsed+= 1 * GetFrameTime();
		if (elapsed >= 1.0f)
		{
			return true;
		}
		else if (elapsed >= 0.1f)
		{
			color.a = 0;
		}
		else
		{
			color.a++;
		}
	}
}

bool Transition::Slide()
{
	return false;
}

Transition& Transition::GetInstance()
{
	static Transition instance;
	return instance;
}