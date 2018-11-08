#pragma once
#include <iostream>
#include "raylib.h"

class Sprite
{
public:
	std::string sprType;
	Vector2 pos;
	float rot;
	Rectangle r1, r2;
	Texture2D texture;

	void translate(Vector2 delta);
	void draw();
	Sprite();
	Sprite(const std::string & fileName, const std::string _sprTYpe = "", float scale = 1);
	~Sprite();
};