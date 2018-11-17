#pragma once
#include "text.h"
class timingText : public text
{
private:
	bool pulse();
public:
	timingText();
	timingText(const string & _content, int fontSize, Color color);

	void setSelected(string newText, Color newColor);

	void update(float delta);
	void draw();
};