#include "timingText.h"

timingText::timingText() {}

timingText::timingText(Vector2 _position, const string & _content, int _size, Color _color)
{
	position = _position;
	defaultX = position.x;
	content = _content;
	size = _size;
	color = _color;
	tick = 0;
}

void timingText::update(float delta)
{
	deltaTime = delta;
	switch (stateMachine.getState())
	{
	case Idle:
		tick = 0;
		size = 50;
		break;
	case Active:
		pulse();
		position.x = GetScreenWidth() / 2 - MeasureText(content.c_str(), size) / 2;
		position.y = GetScreenHeight() / 2 - 50;

		break;
	}
}

void timingText::draw()
{
	DrawText(content.c_str(), position.x, position.y, size, color);
}

bool timingText::pulse()
{
	if (tick >= 0.2)
	{
		stateMachine.setState(Idle);
		return true;
	}
	else if (tick >= 0.1)
	{
		tick += 1 * deltaTime;
		if (size > 50)
			size -= 5;
	}
	else
	{
		tick += 1 * deltaTime;
		if (size < 60)
			size += 5;
	}
	return false;
}