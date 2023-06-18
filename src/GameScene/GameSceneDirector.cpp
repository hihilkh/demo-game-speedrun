#include "GE/GEHeader.h"
#include "GameSceneDirector.h"

#include "GE/Input/InputSystem.h"
#include "Scene/Builder/EndingScene.h"
#include "Scene/SceneTransition.h"
#include "Map/MapManager.h"

namespace GameScene
{
	Director::Director(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void Director::Awake()
	{
		DEBUG_LOG("GameScene");
		Map::MapManager::onMapLoaded.AddListener(&Director::SceneReadyHandler, *this);
	}

	void Director::PreDestroy()
	{
		Map::MapManager::onMapLoaded.RemoveListener(&Director::SceneReadyHandler, *this);
	}

	void Director::Update()
	{
		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			Scene::FadeOutAndChangeScene(Scene::endingSceneName);
		}
	}

	void Director::SceneReadyHandler()
	{
		Scene::FadeIn();
	}
}