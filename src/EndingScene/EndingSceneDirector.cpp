#include "GE/GEHeader.h"
#include "EndingSceneDirector.h"
#include "UI/MenuItem.h"
#include "GE/Input/InputSystem.h"
#include "Scene/SceneTransition.h"
#include "Scene/Builder/TitleScene.h"
#include "Scene/Builder/GameScene.h"
#include "GE/UI/Text.h"
#include <format>
#include "Game/GameStatus.h"

namespace EndingScene
{
	Director::Director(
		GameObject& gameObject,
		std::vector<UI::MenuItem*>&& menuItems,
		GE::UI::Text& congratsText,
		GE::UI::Text& resultText) :

		Component(gameObject),
		menuItems(std::move(menuItems)),
		focusingMenuItemIndex(0),
		congratsText(congratsText),
		resultText(resultText),
		isInteractable(false)
	{
	}

	void Director::Start()
	{
		const std::vector<std::tuple<std::string, std::function<void()>>> menuItemInfos =
		{
			{ "リトライ",		std::bind(&Director::OnRetryBtnClicked, this) },
			{ "タイトル",		std::bind(&Director::OnBackToMainMenuBtnClicked, this) },
		};

		assert(menuItems.size() == menuItemInfos.size() && "menuItemsとmenuItemInfosの数が合わせない");

		for (std::size_t i = 0; i < menuItems.size(); ++i) {
			if (i < menuItemInfos.size()) {
				auto& info = menuItemInfos[i];
				menuItems[i]->Init(std::get<0>(info), i == focusingMenuItemIndex, std::get<1>(info));
			} else {
				menuItems[i]->Init("", false, nullptr);
			}
		}

		congratsText.SetText("おめでとうございます！");
		std::string resultStr = std::format("クリア時間：{0:.3f}s", Game::GameStatus::ClearGameTimeMillisecond / 1000.0f);
		resultText.SetText(resultStr);

		Scene::FadeIn([this] { this->isInteractable = true; });
	}

	void Director::Update()
	{
		// TODO : Directorの代わりに、Input SystemとButtonでUIをコントロールする

		if (!isInteractable) {
			return;
		}

		if (GE::Input::GetKeyDown(GE::Input::Key::up)) {
			SelectNextMenuItem(false);
		} else if (GE::Input::GetKeyDown(GE::Input::Key::down)) {
			SelectNextMenuItem(true);
		}

		if (GE::Input::GetKeyDown(GE::Input::Key::x)) {
			menuItems[focusingMenuItemIndex]->Click();
		}
	}

	void Director::SelectNextMenuItem(bool isForward)
	{
		if (isForward) {
			if (focusingMenuItemIndex < menuItems.size() - 1) {
				++focusingMenuItemIndex;
			}
		} else {
			if (focusingMenuItemIndex > 0) {
				--focusingMenuItemIndex;
			}
		}

		SelectMenuItem(focusingMenuItemIndex);
	}

	void Director::SelectMenuItem(std::size_t index)
	{
		for (std::size_t i = 0; i < menuItems.size(); ++i) {
			if (i == index) {
				menuItems[i]->Select();
			} else {
				menuItems[i]->Unselect();
			}
		}
	}

	void Director::OnRetryBtnClicked()
	{
		isInteractable = false;
		Scene::FadeOutAndChangeScene(Scene::gameSceneName);
	}

	void Director::OnBackToMainMenuBtnClicked()
	{
		isInteractable = false;
		Scene::FadeOutAndChangeScene(Scene::titleSceneName);
	}
}