#pragma once
#include "GameManager.h"
class gOptions
{
private:
	int menuSelect;
	int lastSelected;
	vector<text> menuText;
public:
	gOptions();
	void update();
	void draw();
	static GameManager& instance();
};