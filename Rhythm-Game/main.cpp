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
#include "MainMenu.h"
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

	gMainMenu scene1;
	gInGame scene2;
	gGameOver scene3;

	InitWindow(screenWidth, screenHeight, "ray!mania");

	InitAudioDevice();

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
		case GameOver:
			scene3.update();
			break;
		case Exit:
			exit = true;
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
		case GameOver:
			scene3.draw();
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