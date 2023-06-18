#include "GE/GEHeader.h"
#include "ImageFade.h"
#include "GE/Render/Image.h"
#include "GE/Core/GEConfig.h"

namespace Utils
{

	ImageFade::ImageFade(GameObject& gameObject, float fadeTime, bool isInitialFadedIn) :
		Component(gameObject),
		image(nullptr),
		state(isInitialFadedIn ? State::FadedIn : State::FadedOut),
		totalFadeTime(fadeTime),
		startFadingTime(-1)
	{
	}

	void ImageFade::Awake()
	{
		SetEnable(true);

		if (GetEnable()) {
			UpdateByState();
		}
	}

	void ImageFade::SetEnable(bool isEnable)
	{
		if (!isEnable) {
			Component::SetEnable(isEnable);
			return;
		}

		if (!image) {
			image = gameObject.GetComponent<GE::Render::Image>();
		}
		
		if (image) {
			Component::SetEnable(isEnable);
		} else {
			DEBUG_LOG_WARNING("imageが見つけられない。ImageFadeが有効になることができない。");
		}
	}

	bool ImageFade::GetIsFading() const
	{
		return state == State::FadingIn || state == State::FadingOut;
	}

	void ImageFade::FadeIn(std::function<void()> onFinished)
	{
		return Fade(true, onFinished);
	}

	void ImageFade::FadeOut(std::function<void()> onFinished)
	{
		return Fade(false, onFinished);
	}
	
	void ImageFade::Fade(bool isFadeIn, std::function<void()> onFinished)
	{
		SetEnable(true);

		if (!GetEnable()) {
			return;
		}

		this->onFinished = onFinished;
		state = isFadeIn ? State::FadingIn : State::FadingOut;
		startFadingTime = Time::GetTime();
	}

	void ImageFade::Update()
	{
		UpdateByState();
	}

	/// <summary>
	/// imageはnullptrではないと仮定する
	/// </summary>
	void ImageFade::UpdateByState()
	{
		image->SetAlpha(CalculateCurrentAlpha());

		switch (state) {
			case State::FadedIn:
			case State::FadedOut:
				FinishedFading();
				break;
			case State::FadingIn:
			case State::FadingOut:
				if (Time::GetTime() - startFadingTime >= totalFadeTime) {
					state = (state == State::FadingIn) ? State::FadedIn : State::FadedOut;
				}
				break;
		}
	}

	void ImageFade::FinishedFading()
	{
		SetEnable(false);
		if (onFinished) {
			onFinished();
			onFinished = nullptr;
		}
	}

	float ImageFade::CalculateCurrentAlpha() const
	{
		float from = 0.0f;
		float to = 1.0f;

		switch (state) {
			case State::FadedIn:	return 1.0f;
			case State::FadedOut:	return 0.0f;
			case State::FadingIn:	from = 0.0f;	to = 1.0f;	break;
			case State::FadingOut:	from = 1.0f;	to = 0.0f;	break;
		}

		if (totalFadeTime == 0) {
			return to;
		}

		float currentFadingTime = Time::GetTime() - startFadingTime;
		if (currentFadingTime > totalFadeTime) {
			return to;
		} else {
			return std::lerp(from, to, currentFadingTime / totalFadeTime);
		}
	}
}