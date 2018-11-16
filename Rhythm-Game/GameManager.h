#pragma once
#include <raylib.h>
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
using std::vector;
class GameManager
{
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
};