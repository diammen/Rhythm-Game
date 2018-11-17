#include "Text.h"

text::text() {}

text::text(Vector2 _position, const string & _content, int _size, Color _color)
{
	position = _position;
	defaultX = position.x;
	content = _content;
	size = _size;
	color = _color;
	tick = 0;
}

bool text::moveForward()
{
	if (tick >= 0.2)
	{
		return true;
	}
	else
	{
		tick+= 1 * deltaTime;
		if (position.x < defaultX + 50)
			position.x += 4;
	}
	return false;
}

bool text::moveBack()
{
	if (tick >= 0.2)
	{
		return true;
	}
	else
	{
		tick+= 1 * deltaTime;
		if (position.x > defaultX)
			position.x -= 4;
	}
	return false;
}

states text::state()
{
	return stateMachine.getState();
}

void text::setSelected()
{
	tick = 0;
	stateMachine.setState(Active);
}

void text::setSelected(string newText, Color newColor) {}

void text::setReturn()
{
	stateMachine.setState(Return);
}

void text::reset()
{
	stateMachine.setState(Idle);
}

void text::update(float delta)
{
	deltaTime = delta;
	switch (stateMachine.getState())
	{
	case Idle:
		position.x = defaultX;
		tick = 0;
		break;
	case Active:
		moveForward();
		break;
	case Return:
		tick = 0;
		if (moveBack())
		{
			reset();
		}
		break;
	}
}

void text::draw()
{
	DrawText(content.c_str(), position.x, position.y, size, color);
}