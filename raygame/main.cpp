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
#include "helper.h"

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
	int speed = 4;
	int totalNotes = 0;
	int combo = 0;
	int bpm = 168;
	float score = 0.0f;
	float maxScore = 0.0f;
	float hitAccuracy = 0.0f;


	float timePlayed = 0.0f;

	bool gameOver = true;
	bool start = false;
	bool hit = false;
	bool showPerfect = false;
	bool showGreat = false;
	bool showMiss = false;

	string path = "test.txt";

	InitWindow(screenWidth, screenHeight, "uso!mania");

	InitAudioDevice();

	hitRegion hitRegion[4] = {};

	note * note = readFile(path);

	totalNotes = note[0].totalNotes;
	maxScore = 100000;

	// location for each hit region
	Rectangle regionLocation[] = { {160, 400, 40, 15}, {320, 400, 40, 15}, {480, 400, 40, 10}, {640, 400, 40, 10} };

	Music music = LoadMusicStream("bnhaTheDayShorter.ogg");

	PlayMusicStream(music);

	// initialize notes
	for (int i = 0; i < totalNotes; ++i)
	{
		note[i].rec.y = -15;
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
		hitRegion[i].rec.height = 15;
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
		if (!gameOver)
		{
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
					note[i].pos.y += speed;
				else
					note[i].pos.y = -15;
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
			if (IsKeyPressed(KEY_D))
			{
				hit = true;
				hitRegion[0].active = true;
				hitRegion[0].color = LIGHTPINK;
			}
			else
			{
				hitRegion[0].active = false;
			}
			if (IsKeyReleased(KEY_D))
			{
				hitRegion[0].color = PINK;
			}
			if (IsKeyPressed(KEY_F))
			{
				hit = true;
				hitRegion[1].active = true;
				hitRegion[1].color = LIGHTPINK;
			}
			else
			{
				hitRegion[1].active = false;
			}
			if (IsKeyReleased(KEY_F))
			{
				hitRegion[1].color = PINK;
			}
			if (IsKeyPressed(KEY_J))
			{
				hit = true;
				hitRegion[2].active = true;
				hitRegion[2].color = LIGHTPINK;
			}
			else
			{
				hitRegion[2].active = false;
			}
			if (IsKeyReleased(KEY_J))
			{
				hitRegion[2].color = PINK;
			}
			if (IsKeyPressed(KEY_K))
			{
				hit = true;
				hitRegion[3].active = true;
				hitRegion[3].color = LIGHTPINK;
			}
			else
			{
				hitRegion[3].active = false;
			}
			if (IsKeyReleased(KEY_K))
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
						if (abs(note[i].col.y - regionLocation[j].y) < 4 && note[i].col.x == regionLocation[j].x)
						{
							note[i].active = false;
							showPerfect = true;
							showGreat = false;
							showMiss = false;
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
		}
		else
		{
			PauseMusicStream(music);
			if (IsKeyPressed(KEY_SPACE))
			{
				gameOver = false;
				start = true;
			}
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(GRAY);
		// draw game board
		if (!gameOver)
		{


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
		}
		else
		{
			DrawText("Press space to play.", GetScreenWidth() / 2 - MeasureText("Press space to play.", 30) / 2, GetScreenHeight() / 2 - 50, 30, WHITE);
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