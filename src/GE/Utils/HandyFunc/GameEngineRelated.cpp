#include "GameEngineRelated.h"
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

	void Destroy(GameObject& gameObject)
	{
		GameEngine::Destroy(gameObject);
	}
}