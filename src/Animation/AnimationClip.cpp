#include "AnimationClip.h"
#include <numeric>

namespace Animation
{
	AnimationClip::AnimationClip(const initializer_list<AnimationKey>& animKeys) : animKeys(animKeys)
	{
		if (this->animKeys.empty()) {
			animLength = 0;
		}
		else {
			animLength = this->animKeys.back().lastFrame;
		}
	}

	AnimationClip::~AnimationClip()
	{
	}

	ML::Box2D AnimationClip::GetImageSrc(int frame)
	{
		if (animLength == 0) {
			return ML::Box2D();
		}

		// TODO : もっと効率的な方法？
		for (AnimationKey& key : animKeys) {
			if (frame < key.lastFrame) {
				return key.imageSrc;
			}
		}

		return animKeys.back().imageSrc;
	}
}