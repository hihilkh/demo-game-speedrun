#pragma once

#include "MapChipBase.h"

namespace Map
{
	class UnbreakableWallMapChip : public MapChipBase
	{
	public:
		UnbreakableWallMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase);
		~UnbreakableWallMapChip();

	protected:
		ML::Box2D GetRenderSrc() const override;

	public:
		bool GetIsWalkable() const override;
	};
}