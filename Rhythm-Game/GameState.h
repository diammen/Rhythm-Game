#pragma once
#include <raylib.h>
enum GStates
{
	MainMenu = 0,
	InGame,
	GameOver
};
class GameState
{
private:
	GameState();
	GameState(GameState const&);
	void operator=(GameState const&) {}
	GStates state = MainMenu;

public:
	GStates getState();
	void setState(GStates newState);
	static GameState& GetInstance();
	~GameState();
};

void gMainMenu();

void gInGame();

void gGameOver();