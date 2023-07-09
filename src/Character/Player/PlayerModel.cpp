#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "Map/MapManager.h"
#include "State/PlayerStateRequest.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject),
		facingDir(TransformUtils::Direction::Down),
		stateMachine(*this)
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

	void PlayerModel::LateUpdate()
	{
		stateMachine.Update();
	}

	void PlayerModel::SceneReadyHandler(const Map::MapManager& mapManager)
	{
		GetTransform().SetWorldPos(mapManager.GetPlayerStartPos());
	}

	void PlayerModel::Move(const Vector2& dirVector)
	{
		moveDirVector = dirVector;
	}

	void PlayerModel::UpdateFacingDirection()
	{
		facingDir = TransformUtils::GetNewDirection(facingDir, moveDirVector);
	}

	void PlayerModel::StartRunning()
	{
		stateMachine.AddStateRequest(PlayerStateRequest::StartRunning);
	}

	void PlayerModel::StopRunning()
	{
		stateMachine.AddStateRequest(PlayerStateRequest::StopRunning);
	}

	bool PlayerModel::CanControl() const
	{
		return true;
	}
}