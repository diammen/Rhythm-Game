#include "raylib.h"
#include "helper.h"
#include <fstream>
#include <iostream>
#include <string>
using std::string;

note * readFile(string filePath)
{
	using namespace std;

	// open song file
	fstream songFile;

	songFile.open(filePath, ios_base::in);

	if (!songFile.is_open())
	{
		CloseWindow();
	}

	size_t size = 0;

	string buffer;
	// read note number from file
	songFile >> size;

	note * notes = new note[size];

	// read note position from file
	for (int i = 0; i < size; ++i)
	{
		songFile >> notes[i].rec.x >> notes[i].rec.y;
		notes[i].rec.x *= 160;
		notes[i].totalNotes = size;
	}

	songFile.clear();
	songFile.flush();
	songFile.close();

	return notes;
}