#include "WeakWallMapChip.h"
#include "Chara/Player/Task_Player.h"
#include "ParticleSystem/Task_BreakWallEffect.h"

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
			return ML::Box2D(64, 0, 32, 32);
		}

	}

	bool WeakWallMapChip::GetIsWalkable() const
	{
		return isBroken;
	}

	void WeakWallMapChip::CollideWithChara(const Chara::CharaBase& chara)
	{
		if (isBroken) {
			return;
		}

		try {
			const Player::Object& player = dynamic_cast<const Player::Object&>(chara);
			if (player.CheckIsInCrashStateAndSpeed()) {
				Break();
			}
		}
		catch (...) {

		}

	}

	void WeakWallMapChip::Break()
	{
		isBroken = true;

		auto effect = ParticleSystem::BreakWallEffect::Object::Create(true);
		effect->Play(GetCenterPos(), 20, 60);
	}
}