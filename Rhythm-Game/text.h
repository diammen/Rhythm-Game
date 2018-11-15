#pragma once
#include <iostream>
#include "raylib.h"
#include "textStateMachine.h"
using std::string;

class text
{
public:
	Vector2 position;
	string content;
	Color color;
	textSM stateMachine;
	int size;
	int frameCounter;
	bool selected;


	void update();
	void draw();
	text();
	text(Vector2 pos, const string & songName, int fontSize, Color color);
};