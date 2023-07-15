#pragma once

#include "PlayerStateHandler.h"
#include "GE/Utils/TypeDef.h"
#include "GE/DataType/Vector2.h"

namespace GE
{
	class Transform2D;
}

namespace Player
{
	class PlayerFallbackStateHandler : public PlayerStateHandler
	{
	public:
		explicit PlayerFallbackStateHandler(PlayerModel& model);

		void OnEnter() override;
		void OnUpdate() override;
		bool CheckHasDoneState() override;

	private:
		float normalizedFallbackTime;
		Transform2D* playerImageTransform;
		Vector2 fallbackVelocity;
	};
}