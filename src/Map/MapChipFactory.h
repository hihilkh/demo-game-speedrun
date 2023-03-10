#pragma once

#include <myLib.h>

namespace Map
{
#pragma region 前方宣言

	class Resource;
	class MapChipBase;

#pragma endregion

	shared_ptr<MapChipBase> GenerateMap(int typeId, shared_ptr<Resource> res, const ML::Box2D& hitBase);
}