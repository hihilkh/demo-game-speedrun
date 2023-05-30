#pragma once

namespace GE
{
	class GameObject;
}

namespace Prefab::UI
{
	class MenuItemPrefab
	{
	public:
		void operator()(GE::GameObject& baseGameObject) const;
	};
}