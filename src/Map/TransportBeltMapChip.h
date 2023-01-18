#pragma once

#include "MapChipBase.h"
#include "Common/Direction.h"

namespace Map
{
	class TransportBeltMapChip : public MapChipBase
	{
	public:
		TransportBeltMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase, Direction direction);
		~TransportBeltMapChip();

	private:
		Direction direction;

	protected:
		ML::Box2D GetRenderSrc() const override;

	public:
		bool GetIsWalkable() const override;
	};
}