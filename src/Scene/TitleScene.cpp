#include "GE/GEHeader.h"
#include "TitleScene.h"
#include "GE/Scene/Scene.h"

#include "Prefab/Camera/MainCameraPrefab.h"
#include "Prefab/Camera/UICameraPrefab.h"
#include "Prefab/UI/MenuItemPrefab.h"

namespace Scene
{
	std::unique_ptr<GE::Scene::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene::Scene>(titleSceneName);

		GE::Instantiate(Prefab::Camera::MainCameraPrefab(), *scene);
		GE::Instantiate(Prefab::Camera::UICameraPrefab(), *scene);
		GE::Instantiate(Prefab::UI::MenuItemPrefab(), *scene);

		return scene;
	}
}