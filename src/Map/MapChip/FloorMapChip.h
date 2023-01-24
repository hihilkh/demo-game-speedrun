#pragma once

#include "MapChipBase.h"

namespace Map
{
	class FloorMapChip : public MapChipBase
	{
	public:
		FloorMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase);
		~FloorMapChip();

	protected:
		ML::Box2D GetRenderSrc() const override;

	public:
		bool GetIsWalkable() const override;
	};
}