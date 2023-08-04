#pragma once

#include "GE/Utils/TypeDef.h"

namespace UI
{
	class CountDownUI;
}

namespace Prefab::UI
{
	class CountDownUIPrefab
	{
	public:
		::UI::CountDownUI& operator()(GameObject& baseGameObject) const;
	};
}