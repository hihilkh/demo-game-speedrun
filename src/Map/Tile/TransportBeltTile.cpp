#include "GE/GEHeader.h"
#include "TransportBeltTile.h"
#include "GE/Collision/Collider.h"
#include "Character/Player/PlayerModel.h"

namespace Map
{
	TransportBeltTile::TransportBeltTile(GameObject& gameObject, Collider& collider) :
		Tile(gameObject, Map::TileType::TransportBelt),
		collider(collider),
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
}