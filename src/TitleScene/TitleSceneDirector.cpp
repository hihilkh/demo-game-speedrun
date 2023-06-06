#include "GE/GEHeader.h"
#include "TitleSceneDirector.h"
#include "UI/MenuItem.h"

namespace TitleScene
{
	namespace
	{
		void OnStartBtnClicked()
		{
			// TODO
		}

		void OnExitBtnClicked()
		{
			exit(0);
		}

		const std::vector<std::tuple<std::string, std::function<void()>>> menuItemInfos = 
		{
			{ "スタート", OnStartBtnClicked },
			{ "終了", OnExitBtnClicked }
		};
	}

	Director::Director(GameObject& gameObject, std::vector<UI::MenuItem*>&& menuItems) :
		Component(gameObject),
		menuItems(std::move(menuItems)),
		focusingMenuItemIndex(0)
	{
	}

	void Director::Start()
	{
		assert(menuItems.size() == menuItemInfos.size() && "menuItemsとmenuItemInfosの数が合わせない");

		for (std::size_t i = 0; i < menuItems.size(); ++i) {
			if (i < menuItemInfos.size()) {
				auto& info = menuItemInfos[i];
				menuItems[i]->Init(std::get<0>(info), i == focusingMenuItemIndex, std::get<1>(info));
			} else {
				menuItems[i]->Init("",false, nullptr);
			}
		}
	}

	void Director::Update()
	{
		// TODO : Directorの代わりに、Input SystemとButtonでUIをコントロールする
		// TODO : Input
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
}