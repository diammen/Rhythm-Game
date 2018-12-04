#include "note.h"

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

void note::translate(int startPos, int endPos, float time)
{
	pos.y = (endPos - startPos) * time;
}