#pragma once

namespace Player
{
	enum class PlayerState
	{
		Idle,
		Walk,
		Attack,

		// 走る
		PrepareToRun,
		Running,
		Stopping,

		Fallback,
	};
}