#pragma once

#include "MyPG.h"

namespace Game
{
	enum class GameState
	{
		Initialize,
		Started,
		Ended,
	};

	class GameStatus
	{
	public:
		static int MapIndex;
		static ML::Vec2 PlayerInitialPos;	// TODO : プレイヤー位置をマップに入れる
		static GameState CurrentGameState;
	};
}