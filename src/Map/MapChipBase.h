#pragma once
#include <myLib.h>
#include "MapChipType.h"

#pragma region 前方宣言

namespace Map {	class Resource;	}

#pragma endregion

namespace Map
{
	class MapChipBase
	{
	public:
		MapChipBase(MapChipType type, shared_ptr<Resource> res, const ML::Box2D& hitBase);
		~MapChipBase();

		typedef shared_ptr<MapChipBase> SP;

	protected:
		MapChipType type;
		shared_ptr<Resource> res;
		ML::Box2D hitBase;

	protected:
		virtual ML::Box2D GetRenderSrc() const = 0;

	public:
		void Render(int offsetX, int offsetY);
		MapChipType GetType() { return type; }
	};
}