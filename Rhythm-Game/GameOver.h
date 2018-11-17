#pragma once
#include "GameManager.h"
class gGameOver
{
private:
public:
	gGameOver();
	void reset();
	void update();
	void draw();
	static GameManager& instance();
};