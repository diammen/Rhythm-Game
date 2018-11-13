#pragma once
#include <iostream>
#include "raylib.h"
using std::string;

class text
{
public:
	Vector2 position;
	string content;
	int size;
	Color color;
	bool selected;

	void draw();
	text();
	text(Vector2 pos, const string & songName, int fontSize, Color color);
};