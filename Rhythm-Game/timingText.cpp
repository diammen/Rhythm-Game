#include "timingText.h"

timingText::timingText() {}

timingText::timingText(const string & _content, int _size, Color _color)
{
	position = Vector2{ 0,-50 };
	defaultX = position.x;
	content = _content;
	size = _size;
	color = _color;
	elapsed = 0;
	duration = 0;
}

void timingText::setSelected(string newText, Color newColor)
{
	elapsed = 0;
	stateMachine.setState(Active);
	content = newText;
	color = newColor;
}

void timingText::setFinish(string newText, Color newColor)
{
	elapsed = 0;
	stateMachine.setState(Finish);
	content = newText;
	color = newColor;
}

void timingText::setBeat()
{
	elapsed = 0;
	stateMachine.setState(Beat);
}

void timingText::update(float delta)
{
	deltaTime = delta;
	switch (stateMachine.getState())
	{
	case Idle:
		elapsed = 0;
		size = 50;
		break;
	case Active:
		pulse();
		position.x = GetScreenWidth() / 2 - MeasureText(content.c_str(), size) / 2;
		position.y = GetScreenHeight() / 2 - 50;
		break;
	case Beat:
		pulse();
		position.x = 100;
		position.y = 400;
		break;
	case Finish:
		trackFinished();
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
	if (elapsed >= 0.2)
	{
		stateMachine.setState(Idle);
		return true;
	}
	else if (elapsed >= 0.1)
	{
		elapsed += 2 * deltaTime;
		if (size > 50)
			size -= 5;
	}
	else
	{
		elapsed += 2 * deltaTime;
		if (size < 60)
			size += 5;
	}
	return false;
}

bool timingText::trackFinished()
{
	if (elapsed >= 1)
	{
		stateMachine.setState(Idle);
		trackDone = true;
		return true;
	}
	else if (elapsed >= 0.5)
	{
		elapsed += 1 * deltaTime;
	}
	else
	{
		elapsed += 1 * deltaTime;
		if (size < 50)
			size += 1;
	}
	return false;
}