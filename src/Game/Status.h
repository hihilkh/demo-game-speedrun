#pragma once

#include "MyPG.h"

namespace Game
{
	class Status
	{
	private:
		ML::Vec2 initialPos;
		int initalMapIndex;

	public:
		Status();
		~Status();

		typedef shared_ptr<Status> SP;
		typedef weak_ptr<Status> WP;

		ML::Vec2 GetInitialPos() const { return initialPos; }
		int GetInitialMapIndex() const { return initalMapIndex; }
	};
}