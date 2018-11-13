#include "Text.h"

text::text() {}

text::text(Vector2 _position, const string & songName, int _size, Color _color)
{
	position = _position;
	content = songName;
	size = _size;
	color = _color;
	selected = false;
}

void text::draw()
{
	DrawText(content.c_str(), position.x, position.y, size, color);
}