#include "MapChipBase.h"
#include "Map/Task_Map.h"

namespace Map
{
	MapChipBase::MapChipBase(MapChipType type, shared_ptr<Resource> res, const ML::Box2D& hitBase) :
		type(type),
		res(res),
		hitBase(hitBase)
	{

	}

	MapChipBase::~MapChipBase()
	{

	}

	void MapChipBase::Render(int offsetX, int offsetY)
	{
		ML::Box2D draw = hitBase.OffsetCopy(offsetX, offsetY);
		res->chipImg->Draw(draw, GetRenderSrc());
	}

	ML::Vec2 MapChipBase::GetCenterPos() const
	{
		return ML::Vec2(hitBase.x + hitBase.w / 2.0f, hitBase.y + hitBase.h / 2.0f);
	}
}
