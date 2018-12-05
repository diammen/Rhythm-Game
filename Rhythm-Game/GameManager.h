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
#include "box.h"
#include "hitRegion.h"
#include "GameState.h"
#include "Transition.h"
using std::vector;
#define LIGHTPINK CLITERAL{ 255, 180, 255, 255 }
#define LIGHTBLUE CLITERAL{ 180, 255, 255, 255 }
// holds global variables
class GameManager
{	
	GameManager();
	GameManager(GameManager const&);
	void operator=(GameManager const&) {}
public:
	int screenWidth = 800;
	int screenHeight = 450;
	int offset;					// offset on note position based on speed
	int combo;
	int highestCombo;			// highest combo achieved in the song
	int perfectCount;			// number of perfects achieved in the song
	int greatCount;				// number of greats achieved in the song
	int missCount;				// number of misses in the song
	int beatCount;
	int key1;
	int key2;
	int key3;
	int key4;
	int keys[4];

	float speed;					// base speed of a note is 200 pixels per second
	float spdMod;				// speed multiplier
	float bpm;					// beats per minute
	float crotchet;				// time duration of a beat
	float lastBeat;				// previous beat on song position

	float score;
	float maxScore;
	float hitAccuracy;

	float timePlayed;

	bool start;

	vector<note> song1;
	vector<note> song2;
	vector<note> songTest;
	vector<note> note;

	Music music;

	static GameManager& GetInstance();
	~GameManager();
};