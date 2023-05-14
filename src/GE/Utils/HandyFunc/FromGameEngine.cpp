#include "FromGameEngine.h"
#include "GE/Core/GameEngine.h"
#include "GE/Core/GEConfig.h"

namespace GE
{
	const GEConfig& GetGEConfig()
	{
		return GameEngine::GetConfig();
	}

	void LoadScene(const std::string& sceneName)
	{
		return GameEngine::LoadScene(sceneName);
	}
}