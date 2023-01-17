#include "MapChipBase.h"
#include "Task_Map.h"

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
}
