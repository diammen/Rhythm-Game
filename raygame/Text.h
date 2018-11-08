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
};