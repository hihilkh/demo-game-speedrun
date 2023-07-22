#include "AnimationClipSet.h"
#include "AnimationClip.h"

namespace GE::Animation
{
	AnimationClipSet::AnimationClipSet(std::vector<AnimationClip>&& clips) :
		clips(std::move(clips))
	{
	}

	const AnimationClip* AnimationClipSet::GetClip(const std::string& clipName) const
	{
		auto clip = std::find_if(
			clips.begin(), clips.end(),
			[&clipName](const AnimationClip& clip) {return clip.GetName() == clipName; }
		);

		if (clip == clips.end()) {
			return nullptr;
		} else {
			return &*clip;
		}
	}
}