#include "GameManager.h"

GameManager::GameManager()
{

	screenWidth = 800;
	screenHeight = 450;
	speed = 200;				// base speed of a note is 200 pixels per second
	offset = 0;					// offset on note position based on speed
	combo = 0;
	highestCombo = 0;			// highest combo achieved in the song
	perfectCount = 0;			// number of perfects achieved in the song
	greatCount = 0;				// number of greats achieved in the song
	missCount = 0;				// number of misses in the song
	beatCount = 0;
	key1 = KEY_A;
	key2 = KEY_S;
	key3 = KEY_K;
	key4 = KEY_L;

	spdMod = 1.0f;			// speed multiplier
	bpm = 186;				// beats per minute
	crotchet = 0;				// time duration of a beat
	lastBeat = 0;				// previous beat on song position

	score = 0.0f;
	maxScore = 0.0f;
	hitAccuracy = 0.0f;

	timePlayed = 0.0f;

	start = false;

	song1 = vReadFile("TheDay.txt");
	song2 = vReadFile("GreatDays.txt");
	songTest = vReadFile("test.txt");

	//music = LoadMusicStream("GreatDays.ogg");

}

GameManager::~GameManager() {}

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}