#pragma once
#include "text.h"
class timingText : public text
{
private:
	bool pulse();
	bool trackFinished();
public:
	bool trackDone;
	timingText();
	timingText(const string & _content, int fontSize, Color color);

	void setSelected(string newText, Color newColor);
	void setFinish(string newText, Color newColor);
	void setBeat();

	void update(float delta);
	void draw();
};