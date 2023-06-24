#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <functional>

namespace GE::Render
{
	class Image;
}

namespace Utils
{
	/// <summary>
	/// <para>用語：</para>
	/// <para>fade in：image(ゲームの画面ではない)が見えるようになる</para>
	/// <para>fade out：imageが見えないようになる</para>
	/// </summary>
	class ImageFade : public Component
	{
	private:
		enum class State
		{
			FadedIn,
			FadedOut,

			FadingIn,
			FadingOut,
		};

	public:
		ImageFade(GameObject& gameObject, float fadeTime, bool isInitialFadedIn);

		void SetIsEnable(bool isEnable) override;

		void SetFadeTime(float fadeTime) { totalFadeTime = fadeTime; }
		bool GetIsFading() const;

		void FadeIn(std::function<void()> onFinished = nullptr);
		void FadeOut(std::function<void()> onFinished = nullptr);

	protected:
		void Awake() override;
		void Update() override;

	private:
		void Fade(bool isFadeIn, std::function<void()> onFinished = nullptr);
		void UpdateByState();
		void FinishedFading();
		float CalculateCurrentAlpha() const;

	private:
		GE::Render::Image* image;
		State state;
		float totalFadeTime;
		float startFadingTime;
		std::function<void()> onFinished;
	};
}