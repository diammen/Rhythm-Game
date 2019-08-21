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
	Vector2 startPos;
	bool active;
	bool hit;
	int totalNotes;
	float timeStamp;
	float elapsed;
	float duration;
	float lastReportedSonghead;

	void translate(float speed, float targetY);

	// ctors & dtors
	note();
	~note();
};