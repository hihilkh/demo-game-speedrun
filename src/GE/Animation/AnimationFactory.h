#pragma once

#include <vector>
#include <string>

namespace GE::Animation
{
	class AnimationClip;

	class AnimationFactory
	{
	public:
		static std::vector<AnimationClip> GenerateClips(const std::string& animationFile);
	};
}
