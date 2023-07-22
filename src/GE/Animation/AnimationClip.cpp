#include "AnimationClip.h"
#include "GE/Debug/Log.h"
#include "GE/Utils/EnumUtils.h"

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

		const std::pair<const int, GE::Animation::AnimationKey>* nextKeyPair = nullptr;
		for (auto pair = keysInFrame.rbegin(); pair != keysInFrame.rend(); ++pair) {
			if (targetFrame >= pair->first) {
				switch (pair->second.animType) {
					case AnimationKey::AnimationType::Constant:
						return pair->second.imgSrcRect;
					case AnimationKey::AnimationType::Linear:
						if (!nextKeyPair) {
							// 次のキーがない
							return pair->second.imgSrcRect;
						}

						RectPixel from = pair->second.imgSrcRect;
						RectPixel to = nextKeyPair->second.imgSrcRect;
						float progress = (float)(targetFrame - pair->first) / (nextKeyPair->first - pair->first);
						return RectPixel(
							Vector2Int::Lerp(from.pos, to.pos, progress),
							Vector2Int::Lerp(from.size, to.size, progress));
				}

				DEBUG_LOG_ERROR("AnimationKey::AnimationType::" << GE::Enum::ToString(pair->second.animType) << "まだ支援しない。AnimationKey::AnimationType::Constantとみなす。");
				return pair->second.imgSrcRect;
			} else {
				nextKeyPair = &*pair;
			}
		}

		return RectPixel();
	}
}