#pragma once

namespace GE
{
	class GameObject;
}

namespace Prefab
{
	class MenuItemPrefab
	{
	public:
		void operator()(GE::GameObject& baseGameObject) const;
	};
}