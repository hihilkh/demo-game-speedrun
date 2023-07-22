#pragma once

#include <vector>
#include <string>
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "AnimationClip.h"

namespace GE::Animation
{
	class Animator : public Component
	{
	public:
		Animator(GameObject& gameObject, const std::string& animationFile);

		void SetImage(Image* image) { this->image = image; }

	protected:
		// TODO : GameEngineでAnimation Phaseを用意する
		void LateUpdate() override;
		void PreDestroy() override;

	private:
		int referenceFps;

		Image* image;
		std::vector<AnimationClip> clips;
		float currentClipStartTime;
		AnimationClip* currentClip;

	private:
		void SetCurrentClip(const std::string& clipName);
	};
}