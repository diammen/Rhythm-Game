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
#include "MainMenu.h"
#include "Options.h"
#include "InGame.h"
#include "GameOver.h"

#define LIGHTPINK CLITERAL{ 255, 180, 255, 255 }
#define LIGHTBLUE CLITERAL{ 180, 255, 255, 255 }

int main()
{
	using namespace std;
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;
	bool exit = false;

	InitWindow(screenWidth, screenHeight, "ray!mania");

	InitAudioDevice();

	gMainMenu scene1;
	gInGame scene2;
	gOptions scene3;
	gGameOver scene4;

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!exit && !WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		switch (GameState::GetInstance().getState())
		{
		case MainMenu:
			scene1.update();
			break;
		case InGame:
			scene2.update();
			break;
		case Options:
			scene3.update();
			break;
		case GameOver:
			scene4.update();
			break;
		case Exit:
			exit = true;
			break;
		default:
			break;
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
			scene1.draw();
			break;
		case InGame:
			scene2.draw();
			break;
		case Options:
			scene3.draw();
			break;
		case GameOver:
			scene4.draw();
			break;
		case Exit:
			break;
		}

		EndDrawing();
		//----------------------------------------------------------------------------------

	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	UnloadMusicStream(GameManager::GetInstance().music);

	CloseAudioDevice();

	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}