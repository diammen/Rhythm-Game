#include "Theme.h"

theme::theme() {}

theme::~theme() {}

theme& theme::GetInstance()
{
	static theme instance;
	return instance;
}