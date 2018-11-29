#pragma once
#include "text.h"
class box : public text
{
private:
	void highlight();
public:
	Rectangle rec;

	box();
	box(Color _color, Rectangle _rec);

	void setSelected(Color newColor);

	void update(float delta);
	void draw();
};