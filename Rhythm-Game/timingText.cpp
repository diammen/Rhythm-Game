#include "timingText.h"

timingText::timingText() {}

timingText::timingText(const string & _content, int _size, Color _color)
{
	position = Vector2{ 0,-50 };
	defaultX = position.x;
	content = _content;
	size = _size;
	color = _color;
	tick = 0;
}

void timingText::setSelected(string newText, Color newColor)
{
	tick = 0;
	stateMachine.setState(Active);
	content = newText;
	color = newColor;
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
		tick += 2 * deltaTime;
		if (size > 50)
			size -= 5;
	}
	else
	{
		tick += 2 * deltaTime;
		if (size < 60)
			size += 5;
	}
	return false;
}