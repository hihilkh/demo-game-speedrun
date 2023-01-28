#pragma once

#include "MyPG.h"

namespace Game
{
	class GameStatus
	{
	private:
		static int MapIndex;
		static ML::Vec2 InitialPos;	// TODO : プレイヤー位置をマップに入れる

	public:
		static int GetMapIndex() { return MapIndex; }
		static ML::Vec2 GetInitialPos() { return InitialPos; }

		static void SetMapIndex(int mapIndex) { MapIndex = mapIndex; }
		static void SetInitialPos(ML::Vec2 initialPos) { InitialPos = initialPos; }
	};
}