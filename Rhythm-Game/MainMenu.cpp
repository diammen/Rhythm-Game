#include "MainMenu.h"

gMainMenu::gMainMenu()
{
	menuSelect = 0;
	lastSelected = 0;

	menuText.push_back(text(Vector2{ 100,50 }, "Great Days", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,100 }, "The Day", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,150 }, "Change Key Bindings", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,200 }, "Exit", 40, ORANGE));
	Transition::GetInstance().entering = true;
}

GameManager& gMainMenu::instance()
{
	return GameManager::GetInstance();
}

void gMainMenu::update()
{
	// change speed modifier based on keyboard input
	Transition::GetInstance().Fade();
	if (IsKeyPressed(KEY_RIGHT))
		instance().spdMod += 0.1f;
	if (IsKeyPressed(KEY_LEFT))
		instance().spdMod -= 0.1f;
	if (instance().spdMod < 1)
		instance().spdMod = 1;
	// when user presses space to advance
	if (IsKeyPressed(KEY_ENTER))
	{
		instance().start = true;
	
		instance().speed *= instance().spdMod; // multiply speed by modifier
		instance().offset = calculateOffset(400, (int)instance().speed, 2); // calculate offset based on new speed
	
		instance().beatCount = 0;
		instance().lastBeat = 0;
	
		if (menuText[0].state() == Active)
		{
			// load first song and start game
			instance().bpm = 170;
			instance().crotchet = 60 / instance().bpm; // calculate time duration of each beat
			instance().music = LoadMusicStream("GreatDays.ogg");
			instance().note.clear();
			instance().note = instance().songTest;
			GameState::GetInstance().setState(InGame);
		}
		else if (menuText[1].state() == Active)
		{
			// load second song and start game
			instance().crotchet = 60 / instance().bpm; // calculate time duration of each beat
			instance().music = LoadMusicStream("TheDayShorter.ogg");
			//SetMusicVolume(instance().music, 3.0f);
			instance().note = instance().song1;
			GameState::GetInstance().setState(InGame);
		}
		else if (menuText[2].state() == Active)
		{
			// go to options
 			GameState::GetInstance().setState(Options);
		}
		else if (menuText[3].state() == Active)
		{
			// exit game
			GameState::GetInstance().setState(Exit);
			return;
		}
		for (int i = 0; i < instance().note.size(); ++i)
		{
			instance().note[i].pos.y = -instance().note[i].timeStamp * instance().speed;
			instance().note[i].pos.y += instance().offset + 5;
			instance().note[i].active = true;
		}
	}
	if (IsKeyPressed(KEY_DOWN))
	{
		menuSelect++; // move up the menu
	
		menuText[lastSelected].setReturn(); // set the previously chosen option back
	
		if (menuSelect > menuText.size() - 1) // clamp menuSelect to amount of options
			menuSelect = (int)menuText.size() - 1;
	
		lastSelected = menuSelect; // set last chosen option to currently selected
	
		menuText[menuSelect].setSelected(); // set chosen option to selected state
	}
	if (IsKeyPressed(KEY_UP))
	{
		menuSelect--; // move down the menu
	
		menuText[lastSelected].setReturn();
	
		if (menuSelect < 0)
			menuSelect = 0;
	
		lastSelected = menuSelect;
	
		menuText[menuSelect].setSelected();
	}
	
	for (int i = 0; i < menuText.size(); ++i) menuText[i].update(GetFrameTime()); // update text objects
}

void gMainMenu::draw()
{
	DrawText("Press enter to advance.", GetScreenWidth() / 2 - MeasureText("Press enter to advance.", 30) / 2, 400, 30, WHITE);
	DrawText(FormatText("Speed Modifier: %.1fx", instance().spdMod), GetScreenWidth() / 2 - MeasureText(FormatText("Speed Modifier: %.1fx", instance().spdMod), 30) / 2, 350, 30, WHITE);
	for (int i = 0; i < menuText.size(); ++i)
	{
		menuText[i].draw();
	}
}