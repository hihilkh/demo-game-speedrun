#include "GE/GEHeader.h"
#include "GameScene.h"
#include "GE/Scene/Scene.h"

#include "GameScene/GameSceneDirector.h"

namespace Scene
{
	std::unique_ptr<GE::Scene> GameScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene>(gameSceneName);

		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::GameScene::Director>();

		return scene;
	}
}