#pragma once

#include <vector>
#include <string>

namespace GE::Animation
{
	class AnimationClip;

	class AnimationClipSet
	{
	public:
		AnimationClipSet(std::vector<AnimationClip>&& clips);

		const AnimationClip* GetClip(const std::string& clipName) const;
		const AnimationClip* GetFirstClip() const;

	private:
		const std::vector<AnimationClip> clips;
	};
}