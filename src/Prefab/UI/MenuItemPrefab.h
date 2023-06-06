#pragma once

namespace GE
{
	class GameObject;
}

namespace UI
{
	class MenuItem;
}

namespace Prefab::UI
{
	class MenuItemPrefab
	{
	public:
		::UI::MenuItem& operator()(GE::GameObject& baseGameObject) const;
	};
}