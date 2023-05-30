#include "GE/GEHeader.h"
#include "TitleScene.h"
#include "GE/SceneManagement/Scene.h"
#include "GE/Render/Image.h"
#include "GE/Tools/ConstructorTest.h"
#include "GE/Input/InputSystem.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"
#include "Prefab/UI/MenuItemPrefab.h"

namespace Scene
{
	std::unique_ptr<GE::SceneManagement::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::SceneManagement::Scene>(titleSceneName);

		GameObject& mainCameraObject = GameObject::Create(*scene, "MainCamera");
		auto& camera = mainCameraObject.AddComponent<Camera2D>();
		camera.SetCullingMask(RenderLayer::nonUI);

		GameObject& uiCameraObject = GameObject::Create(*scene, "UICamera");
		auto& uiCamera = uiCameraObject.AddComponent<Camera2D>();
		uiCamera.SetCullingMask(RenderLayer::ui);
		uiCamera.SetPriority(1);

		GE::Instantiate(Prefab::MenuItemPrefab(), *scene);

		return scene;
	}
}