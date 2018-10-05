#pragma once
#include <vector>
#include <string>
using std::string;

struct hitRegion
{
	Rectangle rec;
	Vector2 pos;
	bool active;
	Color color;
};

struct note
{
	Rectangle rec;
	Rectangle col;
	Vector2 pos;
	bool active;
	int totalNotes;
};

note * readFile(string filePath);