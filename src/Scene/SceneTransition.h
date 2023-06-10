#pragma once

#include <string>
#include <functional>

namespace Scene
{
	bool FadeOutAndChangeScene(const std::string& sceneName);
	bool FadeOutAndChangeScene(const std::string& sceneName, float fadeOutTime);

	bool FadeIn(std::function<void()> onFinished = nullptr);
	bool FadeIn(float fadeInTime, std::function<void()> onFinished = nullptr);
}