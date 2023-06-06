#pragma once

#include <string>

namespace GE
{
	struct GEConfig;
	struct Color;

	namespace Internal
	{
		class Destroyable;
	}

	const GEConfig& GetGEConfig();
	void SetBGColor(const Color& color);
	void LoadScene(const std::string& sceneName);
	void Destroy(Internal::Destroyable& toDestroy);
}