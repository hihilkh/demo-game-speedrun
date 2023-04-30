#include "HandyFunc.h"
#include "GameEngine.h"

namespace GE
{
	const GEConfig& GetGEConfig()
	{
		return GameEngine::GetConfig();
	}

	void LoadScene(Scene&& scene)
	{
		return GameEngine::LoadScene(std::move(scene));
	}
}