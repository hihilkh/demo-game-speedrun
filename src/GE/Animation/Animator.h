#pragma once

#include <vector>
#include <string>
#include <memory>
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"

namespace GE::Animation
{
	class AnimationSystem;
	class AnimationDecision;
	class AnimationClipSet;
	class AnimationClip;

	class Animator : public Component
	{
		friend AnimationSystem;

	public:
		Animator(GameObject& gameObject, const std::string& animationFile);
		Animator(GameObject& gameObject, const std::string& animationFile, std::unique_ptr<AnimationDecision> decision);
		~Animator();	// AnimationDecisionが前方宣言できるために、デストラクタを宣言し、cppで定義する

		void SetImage(Image* image) { this->image = image; }

	protected:
		void Start() override;
		void PreDestroy() override;
		void EndOfFrame() override;

	private:
		int referenceFps;

		std::unique_ptr<AnimationDecision> decision;
		Image* image;
		const std::shared_ptr<AnimationClipSet> clips;
		float currentClipStartTime;
		const AnimationClip* currentClip;

	private:
		// AnimationSystemに呼び出される関数
		void OnAnimationUpdate();

		void UpdateCurrentClip();
		void SetCurrentClip(const std::string& clipName);
	};
}