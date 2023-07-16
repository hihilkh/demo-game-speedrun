#include "GE/GEHeader.h"
#include "TransportBeltTile.h"
#include "GE/Collision/Collider.h"
#include "Character/Player/PlayerModel.h"
#include "Map/MapSizeInfo.h"
#include "GE/Render/Image.h"

namespace Map
{
	const RectPixel TransportBeltTile::downImgSrcRect(0, tileHeight, tileWidth, tileHeight);
	const RectPixel TransportBeltTile::leftImgSrcRect(tileWidth * 2, tileHeight, tileWidth, tileHeight);
	const RectPixel TransportBeltTile::upImgSrcRect(tileWidth * 2, tileHeight * 3, tileWidth, tileHeight);
	const RectPixel TransportBeltTile::rightImgSrcRect(0, tileHeight * 3, tileWidth, tileHeight);

	TransportBeltTile::TransportBeltTile(GameObject& gameObject, Collider& collider, Image& image) :
		Tile(gameObject, Map::TileType::TransportBelt),
		collider(collider),
		image(image),
		direction()
	{
	}

	void TransportBeltTile::Start()
	{
		collider.onTriggered.AddListener(&TransportBeltTile::HandleTrigger, *this);
	}

	void TransportBeltTile::PreDestroy()
	{
		collider.onTriggered.RemoveListener(&TransportBeltTile::HandleTrigger, *this);
	}

	void TransportBeltTile::HandleTrigger(const Collider& other, CollidedType collidedType)
	{
		if (collidedType != CollidedType::Overlap) {
			return;
		}

		auto playerModel = other.gameObject.GetComponent<Player::PlayerModel>();
		if (playerModel) {
			playerModel->ApplyTransportBeltDir(direction);
		}
	}

	void TransportBeltTile::SetDirection(TransformUtils::Direction direction)
	{
		this->direction = direction;

		// TODO : Animatorで制御する
		RectPixel srcRect;
		switch (direction) {
			case TransformUtils::Direction::Down:
				srcRect = downImgSrcRect;
				break;
			case TransformUtils::Direction::Left:
				srcRect = leftImgSrcRect;
				break;
			case TransformUtils::Direction::Up:
				srcRect = upImgSrcRect;
				break;
			case TransformUtils::Direction::Right:
				srcRect = rightImgSrcRect;
				break;
		}
		image.SetSrcRect(srcRect);
	}

	// TODO 
	/*


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

	*/
}