#pragma once

#include "GE/Animation/AnimationDecision.h"

namespace Player
{
	class PlayerModel;

	class PlayerAnimationDecision : public GE::Animation::AnimationDecision
	{
	public:
		PlayerAnimationDecision(PlayerModel& model);
		std::string DecideCurrentClip() override;

	private:
		PlayerModel& model;
	};
}