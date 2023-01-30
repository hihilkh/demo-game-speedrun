#pragma once

#include "Event/Event.tpp"

namespace Game
{
	extern Event<> mainTaskLoaded;
	extern Event<> mapLoaded;
	extern Event<> gameStarted;
	extern Event<> gameEnded;
}