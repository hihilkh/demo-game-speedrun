#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "Map/MapManager.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void PlayerModel::Awake()
	{
		Map::MapManager::onMapLoaded.AddListener(&PlayerModel::SceneReadyHandler, *this);
	}

	void PlayerModel::PreDestroy()
	{
		Map::MapManager::onMapLoaded.RemoveListener(&PlayerModel::SceneReadyHandler, *this);
	}

	void PlayerModel::SceneReadyHandler(const Map::MapManager& mapManager)
	{
		GetTransform().SetWorldPos(mapManager.GetPlayerStartPos());
	}

	void PlayerModel::Move(const Vector2& direction, float speed)
	{
		// TODO : 仮処理
		GetTransform().SetPos(GetTransform().GetPos() + Vector2(direction.x * speed, direction.y * speed));
	}
}