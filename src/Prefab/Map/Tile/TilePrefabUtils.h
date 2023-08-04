#pragma once

#include "GE/Utils/TypeDef.h"
#include <string>

namespace Prefab::Map::Tile
{
	void CreateCommon(
		GameObject& baseGameObject, 
		const std::string& name,
		const RectPixel& imgSrcRect,
		bool hasCollider,
		bool isColliderTrigger
	);
}