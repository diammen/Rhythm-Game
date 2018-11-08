#pragma once
#include <iostream>
#include "helper.h"
#include "Text.h"

class Factory
{
private:
	Factory();
	Factory(Factory const&);
	void operator=(Factory const&) {}
	vector<text> _text;
public:
	text& makeText (string content, Vector2 pos);
	void update();
	void draw();
	static Factory& GetInstance();
	~Factory();
};