﻿#pragma once

#include <vector>
#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace GE::Animation
{
	class AnimationDecision;
	class AnimationClipSet;
	class AnimationClip;

	class Animator : public Component
	{
	public:
		Animator(GameObject& gameObject, const std::string& animationFile, std::unique_ptr<AnimationDecision> decision);
		~Animator();	// AnimationDecisionが前方宣言できるために、デストラクタを宣言し、cppで定義する

		void SetImage(Image* image) { this->image = image; }

	protected:
		// TODO : GameEngineでAnimation Phaseを用意する
		void LateUpdate() override;
		void PreDestroy() override;

	private:
		int referenceFps;

		std::unique_ptr<AnimationDecision> decision;
		Image* image;
		std::shared_ptr<AnimationClipSet> clips;
		float currentClipStartTime;
		const AnimationClip* currentClip;

	private:
		void UpdateCurrentClip();
		void SetCurrentClip(const std::string& clipName);
	};
}