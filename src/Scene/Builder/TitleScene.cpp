#include "GE/GEHeader.h"
#include "TitleScene.h"
#include "GE/Scene/Scene.h"
#include "GE/Render/Image.h"

#include "Prefab/UI/MenuItemPrefab.h"
#include "UI/MenuItem.h"
#include "TitleScene/TitleSceneDirector.h"

namespace Scene
{
	std::unique_ptr<GE::Scene> TitleScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene>(titleSceneName);

		// タイトルロゴ
		GameObject& logoObj = GameObject::Create(*scene, "Logo");
		logoObj.GetTransform().SetPosY(100.0f);

		auto& logoImage = logoObj.AddComponent<GE::Render::Image>("./data/Image/Title.png");
		logoImage.SetRenderLayer(RenderLayer::ui);

		// MenuItems
		std::vector<UI::MenuItem*> menuItems;
		menuItems.reserve(2);
		float currentMenuItemPosY = -50.0f;
		float menuItemSpacing = -80.0f;
		for (int i = 0; i < menuItems.capacity(); ++i) {
			UI::MenuItem& menuItem = GE::Instantiate(Prefab::UI::MenuItemPrefab(), *scene);
			menuItem.GetTransform().SetPosY(currentMenuItemPosY);
			currentMenuItemPosY += menuItemSpacing;
			menuItems.push_back(&menuItem);
		}

		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::TitleScene::Director>(std::move(menuItems));

		return scene;
	}
}