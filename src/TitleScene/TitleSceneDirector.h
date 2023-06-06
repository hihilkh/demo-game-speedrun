#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include <vector>

namespace UI
{
	class MenuItem;
}

namespace TitleScene
{
	class Director : public Component
	{
	public:
		Director(GameObject& gameObject, std::vector<UI::MenuItem*>&& menuItems);

	private:
		std::vector<UI::MenuItem*> menuItems;
		std::size_t focusingMenuItemIndex;

	protected:
		void Start() override;
		void Update() override;

	private:
		void SelectNextMenuItem(bool isForward);
		void SelectMenuItem(std::size_t index);
	};
}