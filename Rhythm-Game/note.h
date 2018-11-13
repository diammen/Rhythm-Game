#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "raylib.h"
using std::string;
using std::vector;

class note
{
public:
	Rectangle rec;
	Rectangle col;
	Vector2 pos;
	bool active;
	bool hit;
	int totalNotes;
	float timeStamp;

	void translate(int speed);

	// ctors & dtors
	note();
	~note();
};