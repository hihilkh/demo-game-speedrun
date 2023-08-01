#include "GE/GEHeader.h"
#include "GameScene.h"
#include "GE/Scene/Scene.h"
#include "GameScene/GameSceneDirector.h"
#include "Map/MapManager.h"
#include "Prefab/Character/Player/PlayerPrefab.h"
#include "TimeUtils/Timer.h"
#include "GameScene/GameTimerController.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"
#include "GE/Core/GEConfig.h"

namespace Scene
{
	std::unique_ptr<GE::Scene> GameScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene>(gameSceneName);

		// MapManager
		GameObject& mapManagerObj = GameObject::Create(*scene, "MapManager");
		mapManagerObj.AddComponent<Map::MapManager>();

		// Player
		GE::Instantiate(Prefab::Player::PlayerPrefab(), *scene);
		
		// Timer
		GameObject& timerObj = GameObject::Create(*scene, "Timer");
		auto& timer = timerObj.AddComponent<TimeUtils::Timer>();

		auto timerFont = Lang::LanguageManager::GetFont(Lang::FontType::DefaultSmall);
		const GE::GEConfig& geConfig = GE::GetGEConfig();

		auto& timerText = timerObj.AddComponent<GE::UI::Text>(
			timerFont,
			Vector2Int(geConfig.screenWidth, geConfig.screenHeight));
		timerText.SetColor(Color::black);
		timerText.SetVerticalAlignment(GE::UI::TextVerticalAlignment::Top);
		timerText.SetHorizontalAlignment(GE::UI::TextHorizontalAlignment::Right);
		timerText.SetOutlineColor(Color::white);
		timerText.SetOutlineSize({ 1, 1 });

		auto& timerController = timerObj.AddComponent<::GameScene::GameTimerController>(timer, timerText);

		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::GameScene::Director>(timerController);

		return scene;
	}
}