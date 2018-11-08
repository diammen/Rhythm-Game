#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "raylib.h"
using std::string;
using std::vector;

struct hitRegion
{
	Rectangle rec;
	Vector2 pos;
	bool active;
	Color color;
};

class note
{
public:
	Rectangle rec;
	Rectangle col;
	Vector2 pos;
	bool active;
	int totalNotes;
	float timeStamp;

	void translate(int speed);

	// ctors & dtors
	note();
	~note();
};

vector<note> vReadFile(string filePath);

char calculateRank(int score);