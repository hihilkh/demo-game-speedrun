#include "Animator.h"
#include "GE/Render/Image.h"
#include "GE/Core/GameObject.h"
#include "GE/Core/Time.h"
#include "GE/Utils/HandyFunc/GameEngineRelated.h"
#include "GE/Core/GEConfig.h"
#include "AnimationFactory.h"

namespace GE::Animation
{
	Animator::Animator(GameObject& gameObject, const std::string& animationFile) :
		Component(gameObject),
		image(nullptr),
		clips(AnimationFactory::GenerateClips(animationFile)),
		currentClipStartTime(0.0f),
		currentClip(nullptr)
	{
		const GEConfig& config = GetGEConfig();
		referenceFps = config.targetFps;

		// TODO
		SetCurrentClip("");
	}

	void Animator::LateUpdate()
	{
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

	void Animator::SetCurrentClip(const std::string& clipName)
	{
		// TODO
		currentClip = &clips[0];
	}
}