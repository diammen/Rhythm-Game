#pragma once
#include "GameManager.h"
class gMainMenu
{
private:
	// variables
	int menuSelect;
	int lastSelected;
	vector<text> menuText;
public:
	gMainMenu();
	void update();
	void draw();
	static GameManager& instance();
};