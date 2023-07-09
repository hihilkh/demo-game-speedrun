#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "Map/MapManager.h"
#include "PlayerConfig.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject),
		currentDir(TransformUtils::Direction::Down)
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

	void PlayerModel::Move(const Vector2& dirVector)
	{
		// TODO : 仮処理
		currentDir = TransformUtils::GetNewDirection(currentDir, dirVector);
		GetTransform().SetPos(GetTransform().GetPos() + dirVector * walkSpeed);
	}

	bool PlayerModel::CanControl() const
	{
		return true;
	}
}