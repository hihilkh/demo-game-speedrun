#pragma once

#include <string>

namespace GE::Animation
{
	class AnimationDecision
	{
	public:
		virtual ~AnimationDecision() = default;

		virtual std::string DecideCurrentClip() = 0;
	};
}