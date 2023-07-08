#include "GameStatus.h"

namespace Game
{
	//int GameStatus::MapIndex = 1;
	ML::Vec2 GameStatus::PlayerInitialPos = ML::Vec2(0.0f, 0.0f);
	GameState GameStatus::CurrentGameState = GameState::Initialize;
	int GameStatus::ClearGameTimeMillisecond = -1;
	//unsigned long GameStatus::FrameCount = 0;
}