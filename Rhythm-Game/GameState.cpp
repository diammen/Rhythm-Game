#include "GameState.h"

GameState::GameState() {}
GameState::~GameState() {}

GameState::GameState(GameState const&) {}

GStates GameState::getState()
{
	return state;
}

void GameState::setState(GStates newState)
{
	state = newState;
}

GameState& GameState::GetInstance()
{
	static GameState instance;
	return instance;
}