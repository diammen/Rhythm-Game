#include "InGame.h"

gInGame::gInGame()
{
	timeText = new timingText("Perfect!", 50, GREEN);

	maxScore = 100000;

	hitRegions.push_back(hitRegion(Rectangle{ 325,400,40,20 }, instance().keys[0]));
	hitRegions.push_back(hitRegion(Rectangle{ 375,400,40,20 }, instance().keys[1]));
	hitRegions.push_back(hitRegion(Rectangle{ 425,400,40,20 }, instance().keys[2]));
	hitRegions.push_back(hitRegion(Rectangle{ 475,400,40,20 }, instance().keys[3]));
}

GameManager& gInGame::instance()
{
	return GameManager::GetInstance();
}

void gInGame::update()
{
	instance().timePlayed = GetMusicTimePlayed(instance().music) / GetMusicTimeLength(instance().music) * (instance().screenWidth);
	for (int i = 0; i < hitRegions.size(); ++i)
	{
		hitRegions[i].keyBind = instance().keys[i];
	}
	if (instance().start)
	{
		PlayMusicStream(instance().music);
	}
	else
	{
		PauseMusicStream(instance().music);
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
		// when it's time for note to go
		if (!instance().note[i].active && !instance().note[i].hit && GetMusicTimePlayed(instance().music) >= instance().note[i].timeStamp)
			instance().note[i].active = true;
		// sync rectangle and collision box to position
		instance().note[i].rec.y = instance().note[i].pos.y;
		instance().note[i].col.y = instance().note[i].pos.y;
		// when note reaches bottom of screen
		if (instance().note[i].pos.y > instance().screenHeight && instance().note[i].active)
		{
			instance().note[i].active = false;
			instance().note[i].hit = true;
			// reset combo
			if (instance().combo > instance().highestCombo) instance().highestCombo = instance().combo; // set new highest combo if appropriate
			instance().combo = 0;
			// increment miss counter
			instance().missCount++;
			timeText->setSelected("Miss", RED);
		}
		// move note
		if (instance().note[i].active && !instance().note[i].hit)
			instance().note[i].translate(instance().speed);
		// if note has been hit, set it aside
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
					timeText->setSelected("Perfect!", GREEN); // display perfect

					// increment counters
					instance().combo++;
					instance().perfectCount++;
					// calculate score
					instance().hitAccuracy = 1.0f;
					instance().score += (float)maxScore * instance().hitAccuracy / instance().note.size();
					break;
				}
				// if timing is not perfect
				else if (CheckCollisionRecs(instance().note[i].rec, hitRegions[j].rec))
				{
					// disable note
					instance().note[i].active = false;
					instance().note[i].hit = true;
					timeText->setSelected("Great!", SKYBLUE); // display great

					// increment counters
					instance().combo++;
					instance().greatCount++;
					// calculate score
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
	// update text object
	timeText->update(GetFrameTime());
	// set music to play once
	SetMusicLoopCount(instance().music, 0);
	// once music stops playing
	if (!IsMusicPlaying(instance().music))
	{
		if (instance().combo > instance().highestCombo) instance().highestCombo = instance().combo;
		instance().start = false;
		GameState::GetInstance().setState(GameOver);
	}
}

void gInGame::draw()
{
	// draw key points
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
	// draw text object
	timeText->draw();
	// draw progress bar
	DrawRectangle(0, instance().screenHeight - 10, (int)instance().timePlayed, 10, LIGHTBLUE);

	// draw score and combo
	DrawText(FormatText("SCORE: %i", (int)instance().score), 10, 5, 30, WHITE);
	DrawText(FormatText("COMBO: %i", instance().combo), 10, 40, 30, WHITE);
	//DrawText(FormatText("Beat Count: %i", instance().beatCount), 5, 55, 20, WHITE);
	//DrawText(FormatText("Beat Position: %f", instance().lastBeat), 5, 80, 20, WHITE);
}