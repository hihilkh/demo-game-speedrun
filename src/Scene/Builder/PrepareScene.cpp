#include "GE/GEHeader.h"
#include "PrepareScene.h"
#include "GE/Scene/Scene.h"
#include "PrepareScene/PrepareSceneDirector.h"

namespace Scene
{
	std::unique_ptr<GE::Scene> PrepareScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene>(prepareSceneName);

		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::PrepareScene::Director>();

		return scene;
	}
}