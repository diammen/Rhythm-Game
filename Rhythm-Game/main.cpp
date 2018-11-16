/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "raylib.h"
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helper.h"
#include "note.h"
#include "text.h"
#include "timingText.h"
#include "hitRegion.h"
#include "GameState.h"

#define LIGHTPINK CLITERAL{ 255, 180, 255, 255 }
#define LIGHTBLUE CLITERAL{ 180, 255, 255, 255 }

int main()
{
	using namespace std;
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	int textSize = 50;
	int frameCounter = 0;
	int speed = 200;				// base speed of a note is 200 pixels per second
	int offset = 0;					// offset on note position based on speed
	int totalNotes = 0;
	int combo = 0;
	int highestCombo = 0;			// highest combo achieved in the song
	int perfectCount = 0;			// number of perfects achieved in the song
	int greatCount = 0;				// number of greats achieved in the song
	int missCount = 0;				// number of misses in the song
	int beatCount = 0;
	int menuSelect = 0;				// current selection in main menu
	int lastSelected = 0;

	float spdMod = 1.0f;			// speed multiplier
	float bpm = 186;				// beats per minute
	float crotchet = 0;				// time duration of a beat
	float lastBeat = 0;				// previous beat on song position

	float score = 0.0f;
	float maxScore = 0.0f;
	float hitAccuracy = 0.0f;

	float timePlayed = 0.0f;

	bool start = false;
	bool showPerfect = false;
	bool showGreat = false;
	bool showMiss = false;

	InitWindow(screenWidth, screenHeight, "ray!mania");

	InitAudioDevice();

	// location for each hit region
	Rectangle regionLocation[] = { { 325, 400, 40, 20 },{ 375, 400, 40, 20 },{ 425, 400, 40, 20 },{ 475, 400, 40, 20 } };

	vector<hitRegion> hitRegions;
	hitRegions.push_back(hitRegion(regionLocation[0], KEY_A));
	hitRegions.push_back(hitRegion(regionLocation[1], KEY_S));
	hitRegions.push_back(hitRegion(regionLocation[2], KEY_K));
	hitRegions.push_back(hitRegion(regionLocation[3], KEY_L));

	vector<note> song1 = vReadFile("TheDay.txt");
	vector<note> song2 = vReadFile("GreatDays.txt");
	vector<note> songTest = vReadFile("test.txt");
	vector<note> note;

	vector<text> menuText;
	menuText.push_back(text(Vector2{ 100,50 }, "1. The Day", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,100 }, "2. Great Days", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,150 }, "3. Options", 40, ORANGE));
	menuText.push_back(text(Vector2{ 100,200 }, "4. Exit", 40, ORANGE));

	timingText timeText(Vector2{ 0,-50 }, "Perfect!", 50, GREEN);

	Music music = LoadMusicStream("TheDayShorter.ogg");

	maxScore = 100000;

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		switch (GameState::GetInstance().getState())
		{
		case MainMenu:
			if (IsKeyPressed(KEY_RIGHT))
				spdMod += 0.1f;
			if (IsKeyPressed(KEY_LEFT))
				spdMod -= 0.1f;
			if (spdMod < 1)
				spdMod = 1;
			if (IsKeyPressed(KEY_SPACE))
			{
				GameState::GetInstance().setState(InGame);
				start = true;

				speed *= spdMod;
				offset = calculateOffset(400, speed, 2) - 5;
				crotchet = 60 / bpm;

				beatCount = 0;
				lastBeat = 0;

				if (menuText[0].state() == Active)
				{
					music = LoadMusicStream("TheDayShorter.ogg");
					note.clear();
					note = song1;
					totalNotes = note[0].totalNotes;
				}
				else if (menuText[1].state() == Active)
				{
					bpm = 170;
					music = LoadMusicStream("GreatDays.ogg");
					SetMusicVolume(music, 3.0f);
					note = song2;
					totalNotes = note[0].totalNotes;
				}
				for (int i = 0; i < note.size(); ++i) note[i].pos.y = offset;
			}
			if (IsKeyPressed(KEY_DOWN))
			{
				menuSelect++; // move up the menu

				menuText[lastSelected].setReturn(); // set the previously chosen option back

				if (menuSelect > menuText.size() - 1) // clamp menuSelect to amount of options
					menuSelect = menuText.size() - 1;

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

			for (int i = 0; i < menuText.size(); ++i) menuText[i].update(GetFrameTime());
			break;
		case InGame:
			timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) * (screenWidth);
			if (start)
			{
				PlayMusicStream(music);
			}
			else
			{
				PauseMusicStream(music);
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				start = !start;
			}
			// beat counter
			if (GetMusicTimePlayed(music) > lastBeat + crotchet)
			{
				lastBeat += crotchet;
				beatCount++;
			}
			UpdateMusicStream(music);
			// sync collisions and move notes
			for (int i = 0; i < totalNotes; ++i)
			{
				if (!note[i].active && !note[i].hit && GetMusicTimePlayed(music) >= note[i].timeStamp)
					note[i].active = true;
				note[i].rec.y = note[i].pos.y;
				note[i].col.y = note[i].pos.y;
				if (note[i].pos.y > screenHeight && note[i].active)
				{
					note[i].active = false;
					note[i].hit = true;
					if (combo > highestCombo) highestCombo = combo;
					combo = 0;
					missCount++;
					showMiss = true;
					showGreat = false;
					showPerfect = false;
					timeText.setSelected();
					timeText.content = "Miss";
					timeText.color = RED;

					frameCounter = 0;
				}
				if (note[i].active && !note[i].hit)
					note[i].translate(speed);
				if (note[i].hit)
					note[i].pos.y = offset;

			}
			// activate one hit region based on input
			for (int i = 0; i < hitRegions.size(); ++i)
			{
				hitRegions[i].update();
			}
			// check for collision between notes and hit regions
			for (int i = 0; i < totalNotes; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (hitRegions[j].active)
					{
						// if timing is perfect
						if (abs(note[i].col.y - regionLocation[j].y) < 7 && note[i].col.x == regionLocation[j].x)
						{
							note[i].active = false;
							note[i].hit = true;
							showPerfect = true;
							showGreat = false;
							showMiss = false;
							timeText.setSelected();
							timeText.content = "Perfect!";
							timeText.color = GREEN;

							frameCounter = 0;
							combo++;
							perfectCount++;
							hitAccuracy = 1.0f;
							score += maxScore * hitAccuracy / (float)totalNotes;
							break;
						}
						// if timing is not perfect
						else if (CheckCollisionRecs(note[i].rec, hitRegions[j].rec))
						{
							note[i].active = false;
							note[i].hit = true;
							showGreat = true;
							showPerfect = false;
							showMiss = false;
							timeText.setSelected();
							timeText.content = "Great!";
							timeText.color = SKYBLUE;

							frameCounter = 0;
							combo++;
							greatCount++;
							hitAccuracy = 0.80f;
							score += maxScore * hitAccuracy / (float)totalNotes;
							break;
						}
					}
				}
			}
			// round score to 100k
			if (score >= 999999)
			{
				score = 100000;
			}
			timeText.update(GetFrameTime());
			SetMusicLoopCount(music, 0);
			if (!IsMusicPlaying(music))
			{
				if (combo > highestCombo) highestCombo = combo;
				GameState::GetInstance().setState(GameOver);
			}
			break;
		case GameOver:
			if (IsKeyPressed(KEY_R))
			{
				GameState::GetInstance().setState(MainMenu);
				for (int i = 0; i < 2; ++i)
				{
					menuText[i].reset();
				}
			}
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);

		// draw game board
		switch (GameState::GetInstance().getState())
		{
		case MainMenu:
			DrawText("Press space to play.", GetScreenWidth() / 2 - MeasureText("Press space to play.", 30) / 2, 400, 30, WHITE);
			DrawText(FormatText("Speed Modifier: %.1fx", spdMod), GetScreenWidth() / 2 - MeasureText(FormatText("Speed Modifier: %.1fx", spdMod), 30) / 2, 350, 30, WHITE);
			for (int i = 0; i < menuText.size(); ++i)
			{
				menuText[i].draw();
			}
			break;
		case InGame:
			for (int i = 0; i < 4; ++i)
			{
				hitRegions[i].draw();
			}
			// draw notes
			for (int i = 0; i < totalNotes; ++i)
			{
				if (note[i].active)
				{
					DrawRectanglePro(note[i].rec, Vector2{ 0,0 }, 0, WHITE);
				}
			}
			timeText.draw();
			DrawRectangle(0, screenHeight - 10, (int)timePlayed, 10, LIGHTBLUE);

			DrawText(FormatText("SCORE: %i", (int)score), 5, 5, 20, WHITE);
			DrawText(FormatText("COMBO: %i", combo), 5, 30, 20, WHITE);
			DrawText(FormatText("Beat Count: %i", beatCount), 5, 55, 20, WHITE);
			DrawText(FormatText("Beat Position: %f", lastBeat), 5, 80, 20, WHITE);
			break;
		case GameOver:
			DrawText(FormatText("FINAL SCORE: %i", (int)score), 50, GetScreenHeight() / 2 - 200, 40, WHITE);
			DrawText(FormatText("HIGHEST COMBO: %i", highestCombo), 50, GetScreenHeight() / 2 - 150, 40, WHITE);
			DrawText(FormatText("PERFECTS: %i", perfectCount), 50, GetScreenHeight() / 2 - 100, 40, WHITE);
			DrawText(FormatText("GREATS: %i", greatCount), 50, GetScreenHeight() / 2 - 50, 40, WHITE);
			DrawText(FormatText("MISSES: %i", missCount), 50, GetScreenHeight() / 2, 40, WHITE);
			DrawText("Press R to return to the main menu.", GetScreenWidth() / 2 - MeasureText("Press R to return to the main menu.", 30) / 2, 400, 30, WHITE);

			DrawText(FormatText("%c", calculateRank(score)), GetScreenWidth() / 2 - MeasureText(FormatText("%c", calculateRank(score)), textSize) / 2 + 250, GetScreenHeight() / 2 - 200, 150, BLUE);
			break;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------

	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadMusicStream(music);

	CloseAudioDevice();

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}