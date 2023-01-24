#pragma once

#include <myLib.h>

namespace Map
{
#pragma region 前方宣言

	class Resource;
	class MapChipBase;

#pragma endregion

	shared_ptr<MapChipBase> GenerateMapChip(int typeId, shared_ptr<Resource> res, const ML::Box2D& hitBase);
	void GenerateMapObject(int typeId, const ML::Box2D& hitBase);
}