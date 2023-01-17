#pragma once

namespace Player
{
	enum class PlayerState
	{
		Idle,
		Walk,
		Attack,

		// 走る
		Running,
		Stopping,

		Fallback,
	};
}