#pragma once

#include <string>

namespace GE
{
	struct GEConfig;

	namespace Internal
	{
		class Destroyable;
	}

	const GEConfig& GetGEConfig();
	void LoadScene(const std::string& sceneName);
	void Destroy(Internal::Destroyable& toDestroy);
}