#pragma once

#include "AnimationKey.h"

namespace Animation
{
	class AnimationClip
	{
	private:
		//AnimationClip(const AnimationClip&) = delete;

	public:
		AnimationClip(const initializer_list<AnimationKey>& animKeys);
		~AnimationClip();

	private:
		vector<AnimationKey> animKeys;
		int animLength;

	public:
		int GetAnimLength() const { return animLength; }
		ML::Box2D GetImageSrc(int frame);
	};
}