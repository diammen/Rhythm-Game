#include "Options.h"

gOptions::gOptions()
{
	menuSelect = 0;
	lastSelected = 0;

	menuText.push_back(text(Vector2{ 100,50 }, "Far Left:", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,100 }, "Middle Left:", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,150 }, "Middle Right:", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,200 }, "Far Right:", 40, ORANGE));

	inputField.push_back(text(Vector2{ 500,50 }, FormatText("%c", instance().key1), 40, ORANGE));
	inputField.push_back(text(Vector2{ 500,100 }, FormatText("%c", instance().key2), 40, ORANGE));
	inputField.push_back(text(Vector2{ 500,150 }, FormatText("%c", instance().key3), 40, ORANGE));
	inputField.push_back(text(Vector2{ 500,200 }, FormatText("%c", instance().key4), 40, ORANGE));

	boxes.push_back(box(GRAY, Rectangle{ 500,50,40,40 }));
	boxes.push_back(box(GRAY, Rectangle{ 500,100,40,40 }));
	boxes.push_back(box(GRAY, Rectangle{ 500,150,40,40 }));
	boxes.push_back(box(GRAY, Rectangle{ 500,200,40,40 }));
}

GameManager& gOptions::instance()
{
	return GameManager::GetInstance();
}

void gOptions::update()
{
	if (IsKeyPressed(KEY_DOWN))
	{
		menuSelect++; // move up the menu

		boxes[lastSelected].reset(); // set the previously chosen option back

		if (menuSelect > menuText.size() - 1) // clamp menuSelect to amount of options
			menuSelect = menuText.size() - 1;

		lastSelected = menuSelect; // set last chosen option to currently selected

		boxes[menuSelect].setSelected(LIGHTGRAY); // set chosen option to selected state
	}
	if (IsKeyPressed(KEY_UP))
	{
		menuSelect--; // move down the menu

		boxes[lastSelected].reset();

		if (menuSelect < 0)
			menuSelect = 0;

		lastSelected = menuSelect;

		boxes[menuSelect].setSelected(LIGHTGRAY);
	}
	for (int i = 0; i < boxes.size(); ++i)
	{
		boxes[i].update(GetFrameTime());
	}
}

void gOptions::draw()
{
	for (int i = 0; i < menuText.size(); ++i)
	{
		boxes[i].draw();
		menuText[i].draw();
		inputField[i].draw();
	}
}