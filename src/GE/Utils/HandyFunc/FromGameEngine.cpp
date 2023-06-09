#include "FromGameEngine.h"
#include "GE/Core/GameEngine.h"
#include "GE/Core/GEConfig.h"

namespace GE
{
	const GEConfig& GetGEConfig()
	{
		return GameEngine::GetConfig();
	}

	void SetBGColor(const Color& color)
	{
		GameEngine::SetBGColor(color);
	}

	void LoadScene(const std::string& sceneName)
	{
		return GameEngine::LoadScene(sceneName);
	}

	void Destroy(GameObject& gameObject)
	{
		return GameEngine::Destroy(gameObject);
	}
}