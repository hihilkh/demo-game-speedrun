#include "AnimationClip.h"

namespace GE::Animation
{
	AnimationClip::AnimationClip(const std::string& name, bool isLoop) :
		name(name),
		isLoop(isLoop),
		totalNoOfFrame(-1)
	{
	}

	void AnimationClip::PostConstruct()
	{
		if (keysInFrame.rbegin() != keysInFrame.rend()) {
			totalNoOfFrame = keysInFrame.rbegin()->first;
		}
	}

	RectPixel AnimationClip::GetImgSrcRect(int frame) const
	{
		if (totalNoOfFrame < 0) {
			return RectPixel();
		}

		int targetFrame = frame;
		if (isLoop) {
			if (totalNoOfFrame == 0) {
				targetFrame = 0;
			} else {
				targetFrame %= totalNoOfFrame;
			}
		} else {
			if (targetFrame > totalNoOfFrame) {
				targetFrame = totalNoOfFrame;
			}
		}

		for (auto pair = keysInFrame.begin(); pair != keysInFrame.end(); ++pair) {
			int a = pair->first;
			if (targetFrame <= pair->first) {
				return pair->second.imgSrcRect;
			}
		}

		return RectPixel();
	}
}