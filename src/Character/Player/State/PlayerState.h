#pragma once

namespace Player
{
	enum class PlayerState
	{
		Walk,

		PrepareToRun,
		Run,
		StopRunning,

		Fallback,
	};
}