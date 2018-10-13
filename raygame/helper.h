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

class note
{
public:
	Rectangle rec;
	Rectangle col;
	Vector2 pos;
	bool active;
	int totalNotes;
	float timeStamp;

	// ctors & dtors
	note();
	~note();
};

note * readFile(string filePath);