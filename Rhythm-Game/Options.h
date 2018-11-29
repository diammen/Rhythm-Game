#pragma once
#include "GameManager.h"
class gOptions
{
private:
	int menuSelect;
	int lastSelected;
	int letterCount;
	int key;

	vector<text> menuText;
	vector<text> inputField;
	vector<box> boxes;
public:
	gOptions();
	void update();
	void draw();
	static GameManager& instance();
};