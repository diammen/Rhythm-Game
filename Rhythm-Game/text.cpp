#include "Text.h"
#include "helper.h"

text::text() {}

text::text(Vector2 _position, const string & _content, int _size, Color _color)
{
	position = _position;
	defaultX = position.x;
	content = _content;
	size = _size;
	color = _color;
	elapsed = 0;
	duration = 0.2f;
}

bool text::moveForward()
{
	if (elapsed >= 0.2)
	{
		return true;
	}
	else
	{
		elapsed+= 1 * deltaTime;
		if (position.x < defaultX + 50)
			position.x += 4;
	}
	return false;
}

bool text::moveBack()
{
	if (elapsed >= 0.2)
	{
		return true;
	}
	else
	{
		elapsed+= 1 * deltaTime;
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
	elapsed = 0;
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
		elapsed = 0;
		break;
	case Active:
		moveForward();
		break;
	case Return:
		elapsed = 0;
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