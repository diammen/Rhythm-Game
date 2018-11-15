#include "TextState.h"

TextState::TextState() {}
TextState::~TextState() {}

TextState::TextState(TextState const&) {}

TStates TextState::getState()
{
	return state;
}

void TextState::setState(TStates newState)
{
	state = newState;
}

TextState& TextState::GetInstance()
{
	static TextState instance;
	return instance;
}