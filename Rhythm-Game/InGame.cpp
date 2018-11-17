#include "InGame.h"

gInGame::gInGame()
{
	timeText = new timingText("Perfect!", 50, GREEN);

	maxScore = 100000;

	hitRegions.push_back(hitRegion(Rectangle{ 325,400,40,20 }, KEY_A));
	hitRegions.push_back(hitRegion(Rectangle{ 375,400,40,20 }, KEY_S));
	hitRegions.push_back(hitRegion(Rectangle{ 425,400,40,20 }, KEY_K));
	hitRegions.push_back(hitRegion(Rectangle{ 475,400,40,20 }, KEY_L));
}

GameManager& gInGame::instance()
{
	return GameManager::GetInstance();
}

void gInGame::update()
{
	instance().timePlayed = GetMusicTimePlayed(instance().music) / GetMusicTimeLength(instance().music) * (instance().screenWidth);
	if (instance().start)
	{
		PlayMusicStream(instance().music);
	}
	else
	{
		PauseMusicStream(instance().music);
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		instance().start = !instance().start;
	}
	// beat counter
	if (GetMusicTimePlayed(instance().music) > instance().lastBeat + instance().crotchet)
	{
		instance().lastBeat += instance().crotchet;
		instance().beatCount++;
	}
	UpdateMusicStream(instance().music);
	// sync collisions and move notes
	for (int i = 0; i < instance().note.size(); ++i)
	{
		if (!instance().note[i].active && !instance().note[i].hit && GetMusicTimePlayed(instance().music) >= instance().note[i].timeStamp)
			instance().note[i].active = true;

		instance().note[i].rec.y = instance().note[i].pos.y;
		instance().note[i].col.y = instance().note[i].pos.y;

		if (instance().note[i].pos.y > instance().screenHeight && instance().note[i].active)
		{
			instance().note[i].active = false;
			instance().note[i].hit = true;
			if (instance().combo > instance().highestCombo) instance().highestCombo = instance().combo;
			instance().combo = 0;
			instance().missCount++;
			timeText->setSelected("Miss", RED);
		}
		if (instance().note[i].active && !instance().note[i].hit)
			instance().note[i].translate(instance().speed);

		if (instance().note[i].hit)
			instance().note[i].pos.y = instance().offset;
	}
	// activate one hit region based on input
	for (int i = 0; i < hitRegions.size(); ++i)
	{
		hitRegions[i].update();
	}
	// check for collision between notes and hit regions
	for (int i = 0; i < instance().note.size(); ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (hitRegions[j].active)
			{
				// if timing is perfect
				if (abs(instance().note[i].col.y - hitRegions[j].pos.y) < 7 && instance().note[i].col.x == hitRegions[j].pos.x)
				{
					instance().note[i].active = false;
					instance().note[i].hit = true;
					timeText->setSelected("Perfect!", GREEN);

					instance().combo++;
					instance().perfectCount++;
					instance().hitAccuracy = 1.0f;
					instance().score += (float)maxScore * instance().hitAccuracy / instance().note.size();
					break;
				}
				// if timing is not perfect
				else if (CheckCollisionRecs(instance().note[i].rec, hitRegions[j].rec))
				{
					instance().note[i].active = false;
					instance().note[i].hit = true;
					timeText->setSelected("Great!", SKYBLUE);

					instance().combo++;
					instance().greatCount++;
					instance().hitAccuracy = 0.80f;
					instance().score += (float)maxScore * instance().hitAccuracy / instance().note.size();
					break;
				}
			}
		}
	}
	// round score to 100k
	if (instance().score >= 999999)
	{
		instance().score = 100000;
	}
	timeText->update(GetFrameTime());
	SetMusicLoopCount(instance().music, 0);
	if (!IsMusicPlaying(instance().music))
	{
		if (instance().combo > instance().highestCombo) instance().highestCombo = instance().combo;
		GameState::GetInstance().setState(GameOver);
	}
}

void gInGame::draw()
{
	for (int i = 0; i < hitRegions.size(); ++i)
	{
		hitRegions[i].draw();
	}
	// draw notes
	for (int i = 0; i < instance().note.size(); ++i)
	{
		if (instance().note[i].active)
		{
			DrawRectanglePro(instance().note[i].rec, Vector2{ 0,0 }, 0, WHITE);
		}
	}
	timeText->draw();
	DrawRectangle(0, instance().screenHeight - 10, (int)instance().timePlayed, 10, LIGHTBLUE);

	DrawText(FormatText("SCORE: %i", (int)instance().score), 5, 5, 20, WHITE);
	DrawText(FormatText("COMBO: %i", instance().combo), 5, 30, 20, WHITE);
	DrawText(FormatText("Beat Count: %i", instance().beatCount), 5, 55, 20, WHITE);
	DrawText(FormatText("Beat Position: %f", instance().lastBeat), 5, 80, 20, WHITE);
}