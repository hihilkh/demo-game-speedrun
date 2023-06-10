﻿#include "GE/GEHeader.h"
#include "TitleSceneDirector.h"
#include "UI/MenuItem.h"
#include "GE/Input/InputSystem.h"
#include "Scene/SceneTransition.h"

namespace TitleScene
{
	Director::Director(GameObject& gameObject, std::vector<UI::MenuItem*>&& menuItems) :
		Component(gameObject),
		menuItems(std::move(menuItems)),
		focusingMenuItemIndex(0),
		isInteractable(false)
	{
	}

	void Director::Start()
	{
		const std::vector<std::tuple<std::string, std::function<void()>>> menuItemInfos =
		{
			{ "スタート",		std::bind(&Director::OnStartBtnClicked, this) },
			{ "終了",		std::bind(&Director::OnExitBtnClicked, this) },
		};

		assert(menuItems.size() == menuItemInfos.size() && "menuItemsとmenuItemInfosの数が合わせない");

		for (std::size_t i = 0; i < menuItems.size(); ++i) {
			if (i < menuItemInfos.size()) {
				auto& info = menuItemInfos[i];
				menuItems[i]->Init(std::get<0>(info), i == focusingMenuItemIndex, std::get<1>(info));
			} else {
				menuItems[i]->Init("",false, nullptr);
			}
		}

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
			++focusingMenuItemIndex;
		} else {
			--focusingMenuItemIndex;
		}
		focusingMenuItemIndex = std::clamp(focusingMenuItemIndex, std::size_t(0), menuItems.size());
		
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

	void Director::OnStartBtnClicked()
	{
		isInteractable = false;
		// TODO
	}

	void Director::OnExitBtnClicked()
	{
		isInteractable = false;
		exit(0);
	}
}