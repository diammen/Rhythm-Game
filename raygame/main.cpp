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

#include "raylib.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "helper.h"
#include "GameState.h"

#define LIGHTPINK CLITERAL{ 255, 180, 255, 255 }

int main()
{
	using namespace std;
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	int textSize = 50;
	int frameCounter = 0;
	int speed = 200;
	int totalNotes = 0;
	int combo = 0;
	int bpm = 168;
	float score = 0.0f;
	float maxScore = 0.0f;
	float hitAccuracy = 0.0f;


	float timePlayed = 0.0f;

	bool start = false;
	bool hit = false;
	bool showPerfect = false;
	bool showGreat = false;
	bool showMiss = false;

	string path = "test.txt";

	InitWindow(screenWidth, screenHeight, "uso mania");

	InitAudioDevice();

	hitRegion hitRegion[4] = {};

	vector<note> note = vReadFile(path);


	totalNotes = note[0].totalNotes;
	maxScore = 100000;

	// location for each hit region
	Rectangle regionLocation[] = { {325, 400, 40, 20}, {375, 400, 40, 20}, {425, 400, 40, 20}, {475, 400, 40, 20} };

	Music music = LoadMusicStream("bnhaTheDayShorter.ogg");

	PlayMusicStream(music);

	Wave wave = LoadWave("bnhaTheDayShorter.ogg");

	// initialize notes
	for (int i = 0; i < totalNotes; ++i)
	{
		note[i].rec.y = -20;
		note[i].pos.y = note[i].rec.y;
		note[i].col.x = note[i].rec.x;
	}

	// initialize hit regions
	for (int i = 0; i < 4; ++i)
	{
		hitRegion[i].active = true;
		hitRegion[i].pos.x = regionLocation[i].x;
		hitRegion[i].pos.y = regionLocation[i].y;
		hitRegion[i].rec = regionLocation[i];
		hitRegion[i].rec.height = 20;
		hitRegion[i].color = PINK;
	}

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		timePlayed = GetMusicTimePlayed(music) / GetMusicTimeLength(music) * (screenWidth - 40);
		switch (GameState::GetInstance().getState())
		{
		case MainMenu:
			PauseMusicStream(music);
			if (IsKeyPressed(KEY_SPACE))
			{
				GameState::GetInstance().setState(InGame);
				start = true;
			}
			break;
		case InGame:
			if (start)
			{
				PlayMusicStream(music);
				start = false;
			}
			UpdateMusicStream(music);

			// sync collisions and move notes
			for (int i = 0; i < totalNotes; ++i)
			{
				if (note[i].active && GetMusicTimePlayed(music) >= note[i].timeStamp)
					note[i].translate(speed);
				else
					note[i].pos.y = -20;
				note[i].rec.y = note[i].pos.y;
				note[i].col.y = note[i].pos.y;
				if (note[i].pos.y > screenHeight && note[i].active == true)
				{
					note[i].active = false;
					combo = 0;
					showMiss = true;
					showGreat = false;
					showPerfect = false;
					frameCounter = 0;
				}
			}
			// activate one hit region based on input
			// Far Left
			if (IsKeyPressed(KEY_A))
			{
				hit = true;
				hitRegion[0].active = true;
				hitRegion[0].color = LIGHTPINK;
			}
			else
			{
				hitRegion[0].active = false;
			}
			if (IsKeyReleased(KEY_A))
			{
				hitRegion[0].color = PINK;
			}
			// Center Left
			if (IsKeyPressed(KEY_S))
			{
				hit = true;
				hitRegion[1].active = true;
				hitRegion[1].color = LIGHTPINK;
			}
			else
			{
				hitRegion[1].active = false;
			}
			if (IsKeyReleased(KEY_S))
			{
				hitRegion[1].color = PINK;
			}
			// Center Right
			if (IsKeyPressed(KEY_K))
			{
				hit = true;
				hitRegion[2].active = true;
				hitRegion[2].color = LIGHTPINK;
			}
			else
			{
				hitRegion[2].active = false;
			}
			if (IsKeyReleased(KEY_K))
			{
				hitRegion[2].color = PINK;
			}
			// Far Right
			if (IsKeyPressed(KEY_L))
			{
				hit = true;
				hitRegion[3].active = true;
				hitRegion[3].color = LIGHTPINK;
			}
			else
			{
				hitRegion[3].active = false;
			}
			if (IsKeyReleased(KEY_L))
			{
				hitRegion[3].color = PINK;
			}
			// check for collision between notes and hit regions
			for (int i = 0; i < totalNotes; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					if (hitRegion[j].active)
					{
						// if timing is perfect
						if (abs(note[i].col.y - regionLocation[j].y) < 6 && note[i].col.x == regionLocation[j].x)
						{
							note[i].active = false;
							showPerfect = true;
							showGreat = false;
							showMiss = false;

							// factory.instance.MakeText("PERFECT!", 0,0, 5);

							frameCounter = 0;
							combo++;
							hitAccuracy = 1.0f;
							score += maxScore * hitAccuracy / (float)totalNotes;
							break;
						}
						// if timing is not perfect
						else if (CheckCollisionRecs(note[i].rec, hitRegion[j].rec))
						{
							note[i].active = false;
							showGreat = true;
							showPerfect = false;
							showMiss = false;
							frameCounter = 0;
							combo++;
							hitAccuracy = 0.75f;
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
			// play text animation
			if (showPerfect || showGreat || showMiss)
			{
				frameCounter += 1;
				if (frameCounter <= 2)
				{
					textSize += 5;
				}
				else if (frameCounter > 2)
				{
					textSize -= 5;
					if (textSize < 50)
					{
						textSize = 50;
					}
				}
				if (frameCounter >= 50)
				{
					textSize = 50;
					frameCounter = 50;
				}
			}
			SetMusicLoopCount(music, 0);
			if (!IsMusicPlaying(music))
			{
				GameState::GetInstance().setState(GameOver);
			}
			break;
		}
		//----------------------------------------------------------------------------------

		// Factory.instance().update();

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(GRAY);

		// Factory.instance().draw();

		// draw game board
		switch (GameState::GetInstance().getState())
		{
		case MainMenu:
			DrawText("Press space to play.", GetScreenWidth() / 2 - MeasureText("Press space to play.", 30) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
			break;
		case InGame:
			for (int i = 0; i < 4; ++i)
			{
				DrawRectanglePro(Rectangle{ hitRegion[i].pos.x, hitRegion[i].pos.y, 40, 500 }, Vector2{ 40,0 }, 180, CLITERAL{ 175,175,175,175 }); // guidelines
				DrawRectangle(hitRegion[i].pos.x, hitRegion[i].pos.y, hitRegion[i].rec.width, hitRegion[i].rec.height, hitRegion[i].color); // hit regions
			}
			// draw notes
			for (int i = 0; i < totalNotes; ++i)
			{
				if (note[i].active)
				{
					DrawRectanglePro(note[i].rec, Vector2{ 0,0 }, 0, WHITE);
				}
			}
			// show feedback depending on timing
			if (showPerfect)
			{
				DrawText("Perfect!", GetScreenWidth() / 2 - MeasureText("Perfect!", textSize) / 2, GetScreenHeight() / 2 - 50, textSize, GREEN);
			}
			if (showGreat)
			{
				DrawText("Great!", GetScreenWidth() / 2 - MeasureText("Great!", textSize) / 2, GetScreenHeight() / 2 - 50, textSize, SKYBLUE);
			}
			if (showMiss)
			{
				DrawText("Miss", GetScreenWidth() / 2 - MeasureText("Miss", textSize) / 2, GetScreenHeight() / 2 - 50, textSize, RED);
			}

			DrawRectangle(20, screenHeight - 20, screenWidth - 40, 12, LIGHTGRAY);
			DrawRectangle(20, screenHeight - 20, (int)timePlayed, 12, DARKBLUE);
			DrawRectangleLines(20, screenHeight - 20, screenWidth - 40, 12, GRAY);
			DrawText(FormatText("SCORE: %i", (int)score), 5, 5, 20, WHITE);
			DrawText(FormatText("COMBO: %i", combo), 5, 30, 20, WHITE);
			break;
		case GameOver:
			DrawText(FormatText("FINAL SCORE: %i", (int)score), GetScreenWidth() / 2 - MeasureText(FormatText("FINAL SCORE: %i", (int)score), textSize) / 2, GetScreenHeight() / 2 - 100, textSize, YELLOW);
			DrawText(FormatText("%c", calculateRank(score)), GetScreenWidth() / 2 - MeasureText(FormatText("%c", calculateRank(score)), textSize) / 2, GetScreenHeight() / 2, 150, BLUE);
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