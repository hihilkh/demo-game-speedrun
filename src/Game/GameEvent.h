#pragma once

#include "Event/Event.tpp"

namespace Game
{
	extern Event<> gameReady;
	extern Event<> gameStarted;
	extern Event<> gameEnded;
}