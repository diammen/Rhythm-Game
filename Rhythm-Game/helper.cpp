#include "helper.h"

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


		//visuals
		temp.rec.x = 325 + 50 * (temp.rec.x - 1);
		temp.rec.y = -20;

		temp.pos.x = temp.rec.x;
		temp.pos.y = temp.rec.y;

		temp.col.x = temp.rec.x;

		temp.totalNotes = size;
		
		temp.active = false;
		temp.hit = false;
		notes.push_back(temp);
	}

	songFile.clear();
	songFile.flush();
	songFile.close();

	return notes;
}

void loadTheme(string filePath)
{
	using namespace std;

	fstream file;


}

char calculateRank(int score)
{
	if (score >= 95000) return 'S';
	else if (score >= 90000) return 'A';
	else if (score >= 80000) return 'B';
	else if (score >= 70000) return 'C';
	else if (score >= 60000) return 'D';
	else return 'F';
}

int calculateOffset(int y, int m, int x)
{
	int b = y - m * x;
	return b;
}