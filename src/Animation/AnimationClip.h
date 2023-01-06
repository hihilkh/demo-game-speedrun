#pragma once

#include "AnimationKey.h"

namespace Animation
{
	class AnimationClip
	{
	private:
		//AnimationClip(const AnimationClip&) = delete;

	public:
		AnimationClip(bool isLoop, const initializer_list<AnimationKey>& animKeys);
		~AnimationClip();

	private:
		vector<AnimationKey> animKeys;
		int animLength;
		bool isLoop;

	public:
		int GetAnimLength() const { return animLength; }
		bool GetIsLoop() const { return isLoop; }
		ML::Box2D GetImageSrc(int frame);
	};
}