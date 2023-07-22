#include "Animator.h"
#include "GE/Render/Image.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Time.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"
#include "GE/Core/GEConfig.h"
#include "AnimationFactory.h"
#include "AnimationDecision.h"

namespace GE::Animation
{
	Animator::Animator(GameObject& gameObject, const std::string& animationFile, std::unique_ptr<AnimationDecision> decision) :
		Component(gameObject),
		decision(std::move(decision)),
		image(nullptr),
		clips(AnimationFactory::GenerateClips(animationFile)),
		currentClipStartTime(0.0f),
		currentClip(nullptr)
	{
		const GEConfig& config = GetGEConfig();
		referenceFps = config.targetFps;
	}

	Animator::~Animator() = default;

	void Animator::LateUpdate()
	{
		UpdateCurrentClip();

		if (!currentClip) {
			return;
		}

		float totalDeltaTime = Time::GetTime() - currentClipStartTime;
		int currentFrame = (int)(totalDeltaTime * referenceFps);
		if (image) {
			image->SetSrcRect(currentClip->GetImgSrcRect(currentFrame));
		}
	}

	void Animator::PreDestroy()
	{
		if (image) {
			if (!image->gameObject.IsValid()) {
				// このimageはもうすぐ破棄される
				image = nullptr;
			}
		}
	}

	void Animator::UpdateCurrentClip()
	{
		std::string clipName = decision->DecideCurrentClip();
		SetCurrentClip(clipName);
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

		auto clip = std::find_if(
			clips.begin(), clips.end(), 
			[&clipName](AnimationClip& clip) {return clip.GetName() == clipName; }
		);

		if (clip == clips.end()) {
			currentClip = nullptr;
		} else {
			currentClip = &*clip;
		}
	}
}