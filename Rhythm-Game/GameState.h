#pragma once
#include <raylib.h>
#include <vector>
enum GStates
{
	MainMenu = 0,
	Options,
	InGame,
	GameOver,
	Exit
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