#include "GE/GEHeader.h"
#include "EndingScene.h"
#include "GE/Scene/Scene.h"
#include "GE/UI/Text.h"
#include "Lang/LanguageManager.h"
#include "Prefab/UI/MenuItemPrefab.h"
#include "UI/MenuItem.h"
#include "EndingScene/EndingSceneDirector.h"
#include "GE/Core/GEConfig.h"

namespace Scene
{
	std::unique_ptr<GE::Scene::Scene> EndingScene::operator()() const
	{
		auto scene = std::make_unique<GE::Scene::Scene>(endingSceneName);

		auto largeFont = Lang::LanguageManager::GetFont(Lang::FontType::DefaultLarge);
		const GE::GEConfig& config = GE::GetGEConfig();

		// congratsText
		GameObject& congratsObj = GameObject::Create(*scene, "Congrats");
		congratsObj.GetTransform().pos.y = 150.0f;
		auto& congratsText = congratsObj.AddComponent<GE::UI::Text>(
			largeFont,
			Vector2Int(config.screenWidth, 100));
		congratsText.SetColor(Color::white);

		// resultText
		GameObject& resultObj = GameObject::Create(*scene, "Result");
		resultObj.GetTransform().pos.y = 50.0f;
		auto& resultText = resultObj.AddComponent<GE::UI::Text>(
			largeFont,
			Vector2Int(config.screenWidth, 100));
		resultText.SetColor(Color(1.0f, 0.8f, 0.2f));

		// MenuItems
		std::vector<UI::MenuItem*> menuItems;
		menuItems.reserve(2);
		float currentMenuItemPosY = -80.0f;
		float menuItemSpacing = -80.0f;
		for (int i = 0; i < menuItems.capacity(); ++i) {
			UI::MenuItem& menuItem = GE::Instantiate(Prefab::UI::MenuItemPrefab(), *scene);
			menuItem.GetTransform().pos.y = currentMenuItemPosY;
			currentMenuItemPosY += menuItemSpacing;
			menuItems.push_back(&menuItem);
		}

		// Director
		GameObject& directorObj = GameObject::Create(*scene, "Director");
		directorObj.AddComponent<::EndingScene::Director>(
			std::move(menuItems),
			congratsText,
			resultText);

		return scene;
	}
}