#pragma once

#include "GE/Utils/TypeDef.h"

namespace Prefab::Camera
{
	class MainCameraPrefab
	{
	public:
		Camera2D& operator()(GameObject& baseGameObject) const;
	};
}