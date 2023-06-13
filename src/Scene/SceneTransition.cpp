#include "GE/GEHeader.h"
#include "SceneTransition.h"
#include "Utils/ImageFade.h"
#include "GE/Render/Image.h"
#include "GE/Core/GEConfig.h"
#include "Common/RenderPriority.h"

namespace Scene
{
	namespace
	{
		const std::string overlayImagePath = "./data/Image/White.png";
		const float defaultFadeTime = 0.5f;
		Utils::ImageFade* fadeInstance;

		Utils::ImageFade& GetFadeInstance()
		{
			if (fadeInstance) {
				return *fadeInstance;
			}

			GameObject& obj = GameObject::CreatePersistent("SceneTransition");

			// OverlayImage
			GE::Render::Image& image = obj.AddComponent<GE::Render::Image>(overlayImagePath);
			const GE::GEConfig& config = GE::GetGEConfig();
			image.SetImageSize(Vector2((float)config.screenWidth, (float)config.screenHeight));
			image.SetRenderLayer(RenderLayer::ui);
			image.SetRenderPriority(RenderPriority::overlay);
			image.SetColor(Color::black);

			// SceneTransition
			fadeInstance = &(obj.AddComponent<Utils::ImageFade>(defaultFadeTime, true));
			return *fadeInstance;
		}
	}

	bool FadeOutAndChangeScene(const std::string& sceneName)
	{
		return FadeOutAndChangeScene(sceneName, defaultFadeTime);
	}

	bool FadeOutAndChangeScene(const std::string& sceneName, float fadeOutTime)
	{
		Utils::ImageFade& instance = GetFadeInstance();
		if (instance.GetIsFading()) {
			DEBUG_LOG_WARNING("SceneTransitionまだ行っている。今ChangeSceneできない。");
			return false;
		}

		instance.SetFadeTime(fadeOutTime);

		// 画面のFadeOut = overlayImageのFadeIn
		instance.FadeIn([&sceneName] { GE::LoadScene(sceneName); });

		return true;
	}

	bool FadeIn(std::function<void()> onFinished)
	{
		return FadeIn(defaultFadeTime, onFinished);
	}

	bool FadeIn(float fadeInTime, std::function<void()> onFinished)
	{
		Utils::ImageFade& instance = GetFadeInstance();
		if (instance.GetIsFading()) {
			DEBUG_LOG_WARNING("SceneTransitionまだ行っている。今FadeInできない。");
			return false;
		}

		instance.SetFadeTime(fadeInTime);

		// 画面のFadeIn = overlayImageのFadeOut
		instance.FadeOut(onFinished);

		return true;
	}
}