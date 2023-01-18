#include "WeakWallMapChip.h"
#include "Chara/Player/Task_Player.h"

namespace Map
{
	WeakWallMapChip::WeakWallMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase) :
		MapChipBase::MapChipBase(MapChipType::WeakWall, res, hitBase),
		isBroken(false)
	{

	}

	WeakWallMapChip::~WeakWallMapChip()
	{

	}

	// TODO : Think of use design pattern and do it in res
	ML::Box2D WeakWallMapChip::GetRenderSrc() const
	{
		if (isBroken) {
			return ML::Box2D(0, 0, 32, 32);
		}
		else {
			return ML::Box2D(32, 32, 32, 32);
		}

	}

	bool WeakWallMapChip::GetIsWalkable() const
	{
		return isBroken;
	}

	void WeakWallMapChip::HitByChara(const Chara::CharaBase& chara)
	{
		if (isBroken) {
			return;
		}

		try {
			const Player::Object& player = dynamic_cast<const Player::Object&>(chara);
			if (player.GetState() == Player::PlayerState::Running &&
				player.GetIsInCrashSpeed()) {
				Break();
			}
		}
		catch (...) {

		}

	}

	void WeakWallMapChip::Break()
	{
		// TODO : エフェクト
		isBroken = true;
	}
}