#include "GE/GEHeader.h"
#include "GameScene.h"
#include "GE/Scene/Scene.h"
#include "Prefab/Camera/MainCameraPrefab.h"
#include "GameScene/GameSceneDirector.h"
#include "Map/MapManager.h"
#include "Prefab/Character/Player/PlayerPrefab.h"

namespace Scene
{
	std::unique_ptr<GE::Scene> GameScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene>(gameSceneName);

		// ゲームカメラ
		GE::Instantiate(Prefab::Camera::MainCameraPrefab(), *scene);

		// MapManager
		GameObject& mapManagerObj = GameObject::Create(*scene, "MapManager");
		mapManagerObj.AddComponent<Map::MapManager>();

		// Player
		GE::Instantiate(Prefab::Player::PlayerPrefab(), *scene);
		
		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::GameScene::Director>();

		return scene;
	}
}