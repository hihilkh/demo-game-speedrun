#pragma once

#include "MyPG.h"

namespace Game
{
	class GameStatus
	{
	private:
		ML::Vec2 initialPos;
		int initalMapIndex;

	public:
		GameStatus();
		~GameStatus();

		typedef shared_ptr<GameStatus> SP;
		typedef weak_ptr<GameStatus> WP;

		ML::Vec2 GetInitialPos() const { return initialPos; }
		int GetInitialMapIndex() const { return initalMapIndex; }
	};
}