#pragma once
#include "raylib.h"
#define LIGHTPINK CLITERAL{ 255, 180, 255, 255 }
class hitRegion
{
public:
	Rectangle rec;
	Vector2 pos;
	bool active;
	Color idleColor;
	Color activeColor;
	Color currentColor;
	int keyBind;

	void update();
	void draw();

	hitRegion();
	hitRegion(Rectangle _rec, int _keyBind);
};