#pragma once
#include "GameManager.h"
class gOptions
{
private:
public:
	gOptions();
	void update();
	void draw();
	static GameManager& instance();
};