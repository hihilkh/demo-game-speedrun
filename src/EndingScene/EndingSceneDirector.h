#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <vector>

namespace GE::UI
{
	class Text;
}

namespace UI
{
	class MenuItem;
}

namespace EndingScene
{
	class Director : public Component
	{
	public:
		Director(
			GameObject& gameObject, 
			std::vector<UI::MenuItem*>&& menuItems,
			GE::UI::Text& congratsText,
			GE::UI::Text& resultText);

	private:
		std::vector<UI::MenuItem*> menuItems;
		std::size_t focusingMenuItemIndex;
		GE::UI::Text& congratsText;
		GE::UI::Text& resultText;

		bool isInteractable;

	protected:
		void Start() override;
		void Update() override;

	private:
		void SelectNextMenuItem(bool isForward);
		void SelectMenuItem(std::size_t index);

		void OnRetryBtnClicked();
		void OnBackToMainMenuBtnClicked();
	};
}