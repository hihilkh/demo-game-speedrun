#include "Animator.h"
#include "AnimationSystem.h"
#include "GE/Render/Image.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Time.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"
#include "GE/Core/GEConfig.h"
#include "AnimationClipSetLoader.h"
#include "AnimationDecision.h"
#include "AnimationClipSet.h"
#include "AnimationClip.h"

namespace GE::Animation
{
	Animator::Animator(GameObject& gameObject, const std::string& animationFile) :
		Animator(gameObject, animationFile, nullptr)
	{
	}

	Animator::Animator(GameObject& gameObject, const std::string& animationFile, std::unique_ptr<AnimationDecision> decision) :
		Component(gameObject),
		decision(std::move(decision)),
		image(nullptr),
		clips(AnimationClipSetLoader::Load(animationFile)),
		currentClipStartTime(0.0f),
		currentClip(nullptr)
	{
		const GEConfig& config = GetGEConfig();
		referenceFps = config.targetFps;

		if (!decision) {
			currentClip = clips->GetFirstClip();
		}
	}

	Animator::~Animator() = default;

	void Animator::Start()
	{
		AnimationSystem::AddAnimator(*this);
	}

	void Animator::PreDestroy()
	{
		AnimationSystem::RemoveAnimator(*this);
	}

	void Animator::EndOfFrame()
	{
		if (image) {
			if (!image->gameObject.IsValid()) {
				// このimageはもうすぐ破棄される
				image = nullptr;
			}
		}
	}

	void Animator::OnAnimationUpdate()
	{
		UpdateCurrentClip();

		if (!currentClip) {
			return;
		}

		float totalDeltaTime = Time::GetTime() - currentClipStartTime;
		int currentFrame = (int)(totalDeltaTime * referenceFps);

		// TODO : Animatorではなく、AnimationClipまたは他のクラスで実際の振る舞いを制御する
		if (image) {
			image->SetSrcRect(currentClip->GetImgSrcRect(currentFrame));
		}
	}

	void Animator::UpdateCurrentClip()
	{
		if (decision) {
			std::string clipName = decision->DecideCurrentClip();
			SetCurrentClip(clipName);
		}
	}

	void Animator::SetCurrentClip(const std::string& clipName)
	{
		if (clipName == "") {
			currentClip = nullptr;
			return;
		}

		if (currentClip) {
			if (currentClip->GetName() == clipName) {
				return;
			}
		}
		currentClip = clips->GetClip(clipName);
	}
}