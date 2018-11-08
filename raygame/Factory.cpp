#include "Factory.h"

Factory::Factory() {}
Factory::~Factory() {}

Factory::Factory(Factory const&) {}

Factory& Factory::GetInstance()
{
	static Factory instance;
	return instance;
}

text& Factory::makeText(string content, Vector2 pos)
{
	_text.push_back(text());
	_text.back().content = content;
	_text.back().position = pos;
	return _text.back();
}

void Factory::update()
{

}

void Factory::draw()
{

}