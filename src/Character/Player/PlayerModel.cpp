#include "GE/GEHeader.h"
#include "PlayerModel.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void PlayerModel::Move(const Vector2& direction, float speed)
	{
		// TODO : 仮処理
		GetTransform().pos.x += direction.x * speed;
		GetTransform().pos.y += direction.y * speed;
	}
}