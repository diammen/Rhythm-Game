#include "GameOver.h"

gGameOver::gGameOver() {}

GameManager& gGameOver::instance()
{
	return GameManager::GetInstance();
}

void gGameOver::update()
{
	if (IsKeyPressed(KEY_R))
	{
		GameState::GetInstance().setState(MainMenu);
		reset();
	}
}

void gGameOver::draw()
{
	DrawText(FormatText("FINAL SCORE: %i", (int)instance().score), 50, GetScreenHeight() / 2 - 200, 40, WHITE);
	DrawText(FormatText("HIGHEST COMBO: %i", instance().highestCombo), 50, GetScreenHeight() / 2 - 150, 40, WHITE);
	DrawText(FormatText("PERFECTS: %i", instance().perfectCount), 50, GetScreenHeight() / 2 - 100, 40, WHITE);
	DrawText(FormatText("GREATS: %i", instance().greatCount), 50, GetScreenHeight() / 2 - 50, 40, WHITE);
	DrawText(FormatText("MISSES: %i", instance().missCount), 50, GetScreenHeight() / 2, 40, WHITE);
	DrawText("Press R to return to the main menu.", GetScreenWidth() / 2 - MeasureText("Press R to return to the main menu.", 30) / 2, 400, 30, WHITE);

	DrawText(FormatText("%c", calculateRank(instance().score)), GetScreenWidth() / 2 - MeasureText(FormatText("%c", calculateRank(instance().score)), 50) / 2 + 250, GetScreenHeight() / 2 - 200, 150, BLUE);
}

void gGameOver::reset()
{
	instance().score = 0;
	instance().combo = 0;
	instance().perfectCount = 0;
	instance().greatCount = 0;
	instance().missCount = 0;
	instance().bpm = 186;
	instance().speed = 200;
}