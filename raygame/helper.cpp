#include "raylib.h"
#include "helper.h"
#include <fstream>
#include <iostream>
#include <string>

vector<note> vReadFile(string filePath)
{
	using namespace std;

	// open song file
	fstream songFile;

	songFile.open(filePath, ios_base::in);

	if (!songFile.is_open())
	{
		CloseWindow();
	}

	int size = 0;

	string buffer;
	// read note number from file
	songFile >> size;

	vector<note> notes;

	// read note position from file
	for (int i = 0; i < size; ++i)
	{
		note temp;
		songFile >> temp.rec.x >> temp.timeStamp;
		temp.rec.x = 325 + 50 * (temp.rec.x - 1);
		temp.totalNotes = size;
		notes.push_back(temp);
	}

	songFile.clear();
	songFile.flush();
	songFile.close();

	return notes;
}

char calculateRank(int score)
{
	if (score == 100000) return 'S';
	else if (score >= 90000) return 'A';
	else if (score >= 80000) return 'B';
	else if (score >= 70000) return 'C';
	else if (score >= 60000) return 'D';
	else return 'F';
}

note::note()
{
	rec.width = 40;
	rec.height = 20;
	col.width = 40;
	col.height = 20;
	active = true;
}

note::~note()
{

}

void note::translate(int speed)
{
	pos.y += speed * GetFrameTime();
}