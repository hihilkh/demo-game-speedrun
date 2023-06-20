#include "GE/GEHeader.h"
#include "TransportBeltTile.h"

namespace Map
{
	TransportBeltTile::TransportBeltTile(GameObject& gameObject) :
		Tile(gameObject, Map::TileType::TransportBelt)
	{
	}

	// TODO 
	/*
		namespace {
		const float TransportBeltSpeed = 4.0f;
	}

	TransportBeltMapChip::TransportBeltMapChip(shared_ptr<Resource> res, const ML::Box2D& hitBase, Direction direction) :
		MapChipBase::MapChipBase(MapChipType::TransportBelt, res, hitBase),
		direction(direction),
		speed(TransportBeltSpeed)
	{

	}


	// TODO : AnimationClipと補間によって処理する？
	ML::Box2D TransportBeltMapChip::GetRenderSrc() const
	{
		int offset = Game::GameStatus::FrameCount % 32;
		switch (direction) {
			case Direction::Down:		return ML::Box2D( 0, 64 - offset, 32, 32);
			case Direction::Left:		return ML::Box2D(32 + offset, 32, 32, 32);
			case Direction::Up:			return ML::Box2D(64, 64 + offset, 32, 32);
			case Direction::Right:		return ML::Box2D(32 - offset, 96, 32, 32);			
		}

		assert(false && "おかしい方向");

		// 警告を出さないように
		return ML::Box2D(0, 64, 32, 32);
	}

	bool TransportBeltMapChip::GetIsWalkable() const
	{
		return true;
	}

	void TransportBeltMapChip::TriggerByChara(Chara::CharaBase& chara)
	{
		chara.SetAdditionalSpeedInfo(direction, speed);
	}
	*/
}