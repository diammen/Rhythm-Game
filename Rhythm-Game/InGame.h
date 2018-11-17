#pragma once
#include "GameManager.h"
class gInGame
{
private:
	vector<hitRegion> hitRegions;
	timingText * timeText;
	int maxScore;
	int noteCount;
public:
	gInGame();
	void update();
	void draw();
	static GameManager& instance();
};