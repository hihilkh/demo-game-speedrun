#pragma once

#include "GE/Animation/AnimationDecision.h"

namespace Map
{
	class TransportBeltTile;

	class TransportBeltAnimationDecision : public GE::Animation::AnimationDecision
	{
	public:
		TransportBeltAnimationDecision(TransportBeltTile& tile);
		std::string DecideCurrentClip() override;

	private:
		TransportBeltTile& tile;
		std::string clipName;
	};
}