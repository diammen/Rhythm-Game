#pragma once
#include <iostream>
#include "raylib.h"
#include "textStateMachine.h"
using std::string;

class text
{
private:
	bool moveForward();
	bool moveBack();
protected:
	float tick;
	textSM stateMachine;
public:
	Vector2 position;
	string content;
	Color color;

	int size;
	int defaultX;
	float deltaTime;

	states state();
	void setSelected();
	void setReturn();
	void reset();

	virtual void update(float delta);
	virtual void draw();
	text();
	text(Vector2 pos, const string & _content, int fontSize, Color color);
};