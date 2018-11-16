#pragma once
#include "text.h"
class timingText : public text
{
private:
	bool pulse();
public:
	timingText();
	timingText(Vector2 pos, const string & _content, int fontSize, Color color);

	void update(float delta);
	void draw();
};