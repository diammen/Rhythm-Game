#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "raylib.h"
#include "note.h"
using std::string;
using std::vector;

struct hitRegion
{
	Rectangle rec;
	Vector2 pos;
	bool active;
	Color color;
};

vector<note> vReadFile(string filePath);

char calculateRank(int score);

// y-mx = b
// y = position to reach
// m = speed
// x = time to reach target position in seconds
// b = offset
int calculateOffset(int y, int m, int x);