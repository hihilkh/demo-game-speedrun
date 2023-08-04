#pragma once

#include "GE/Utils/TypeDef.h"

namespace Prefab::Camera
{
	class UICameraPrefab
	{
	public:
		Camera2D& operator()(GameObject& baseGameObject) const;
	};
}