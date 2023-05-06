#include "FromGameEngine.h"
#include "Core/GameEngine.h"
#include <string>

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