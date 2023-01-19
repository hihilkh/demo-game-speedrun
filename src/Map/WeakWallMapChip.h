#pragma once

#include "MapChipBase.h"

namespace Map
{
	class WeakWallMapChip : public MapChipBase
	{
	public:
		WeakWallMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase);
		~WeakWallMapChip();

	private:
		bool isBroken;

	private:
		void Break();

	protected:
		ML::Box2D GetRenderSrc() const override;

	public:
		bool GetIsWalkable() const override;
		void CollideWithChara(const Chara::CharaBase& chara) override;
	};
}