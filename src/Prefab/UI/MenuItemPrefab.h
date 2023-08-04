#pragma once

#include "GE/Utils/TypeDef.h"

namespace UI
{
	class MenuItem;
}

namespace Prefab::UI
{
	class MenuItemPrefab
	{
	public:
		::UI::MenuItem& operator()(GameObject& baseGameObject) const;
	};
}