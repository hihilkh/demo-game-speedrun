#pragma once

#include <map>
#include <string>
#include "AnimationKey.h"

namespace GE::Animation
{
	class AnimationClip
	{
		friend class AnimationClipSetLoader;

	public:
		AnimationClip(const std::string& name, bool isLoop);

		RectPixel GetImgSrcRect(int frame) const;
		const std::string& GetName() const { return name; }

	private:
		std::string name;
		std::map<int, AnimationKey> keysInFrame;
		bool isLoop;
		int totalNoOfFrame;

	private:

#pragma region AnimationFactory

		void PostConstruct();

#pragma endregion
	};
}