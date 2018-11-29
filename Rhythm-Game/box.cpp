#include "box.h"

box::box() {}

box::box(Color _color, Rectangle _rec)
{
	color = _color;
	rec = _rec;
}

void box::setSelected(Color newColor)
{
	tick = 0;
	stateMachine.setState(Active);
	color = newColor;
}

void box::update(float delta)
{
	deltaTime = delta;
	switch (stateMachine.getState())
	{
	case Idle:
		color = GRAY;
		break;
	}
}

void box::draw()
{
	DrawRectanglePro(rec, Vector2{ 8, 2 }, 0, color);
}

void box::highlight()
{
	color = LIGHTGRAY;
}