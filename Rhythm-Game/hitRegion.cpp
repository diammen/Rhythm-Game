#include "hitRegion.h"

hitRegion::hitRegion()
{
	rec.height = 20;
	idleColor = PINK;
	activeColor = LIGHTPINK;
	currentColor = idleColor;
	active = false;
}

hitRegion::hitRegion(Rectangle _rec, int _keyBind)
{
	rec = _rec;
	pos.x = rec.x;
	pos.y = rec.y;
	idleColor = PINK;
	activeColor = LIGHTPINK;
	currentColor = idleColor;
	active = false;
	keyBind = _keyBind;
}

void hitRegion::update()
{
	if (IsKeyPressed(keyBind))
	{
		currentColor = activeColor;
		active = true;
	}
	else
	{
		active = false;
	}
	if (IsKeyReleased(keyBind))
	{
		currentColor = idleColor;
	}
}

void hitRegion::draw()
{
	DrawRectanglePro(Rectangle{ pos.x, pos.y, 40, 500 }, Vector2{ 40,0 }, 180, CLITERAL{ 255,255,255,175 }); // guidelines
	DrawRectanglePro(Rectangle{ pos.x, pos.y, 38, 500 }, Vector2{ 39,0 }, 180, CLITERAL{ 50,50,50,255 }); // guidelines
	DrawRectangle(pos.x, pos.y, rec.width, rec.height, currentColor);
}