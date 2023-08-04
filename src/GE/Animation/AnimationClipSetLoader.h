#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace GE::Animation
{
	class AnimationClipSet;

	class AnimationClipSetLoader
	{
	public:
		static std::shared_ptr<AnimationClipSet> Load(const std::string& animationFile);

	private:
		static std::unordered_map<std::string, std::weak_ptr<AnimationClipSet>> loadedClipSets;
	};
}
