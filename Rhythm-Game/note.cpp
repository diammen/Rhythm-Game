#include "note.h"
#include "helper.h"

note::note()
{
	rec.width = 40;
	rec.height = 20;
	col.width = 40;
	col.height = 20;

	startPos.x = 0;
	startPos.y = 0;

	elapsed = 0;
	duration = 2;

	active = false;
}

note::~note()
{

}

void note::translate(float speed, float targetY)
{
	//pos.y += speed * GetFrameTime();
	if (pos.y != targetY) 
	{
		elapsed += GetFrameTime();
		pos.y = lerp(startPos.y, targetY, (elapsed / duration) > 1 ? 1 : (elapsed / duration));
	}
}