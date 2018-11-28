#include "Options.h"

gOptions::gOptions()
{
	menuText.push_back(text(Vector2{ 100,50 }, FormatText("Far Left: %c", instance().key1), 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,100 }, FormatText("Middle Left: %c", instance().key2), 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,150 }, FormatText("Middle Right: %c", instance().key3), 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,200 }, FormatText("Far Right: %c", instance().key4), 40, ORANGE));
}

GameManager& gOptions::instance()
{
	return GameManager::GetInstance();
}

void gOptions::draw()
{
	for (int i = 0; i < menuText.size(); ++i)
	{
		menuText[i].draw();
	}
}