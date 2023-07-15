#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "Map/MapManager.h"
#include "State/PlayerStateRequest.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/Collision/Collider.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject),
		facingDir(TransformUtils::Direction::Down),
		stateMachine(*this),
		lastWorldPos(),
		transportBeltOffset()
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

	void PlayerModel::Update()
	{
		lastWorldPos = GetTransform().GetWorldPos();
	}

	void PlayerModel::LateUpdate()
	{
		stateMachine.Update();
		auto& transform = GetTransform();
		transform.SetPos(transform.GetPos() + transportBeltOffset);
		transportBeltOffset = Vector2::zero;
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

	void PlayerModel::Crash(const GE::Collision::Collider& other)
	{
		stateMachine.AddStateRequest(PlayerStateRequest::Fallback);

		auto weakWallTile = other.gameObject.GetComponent<Map::WeakWallTile>();
		if (weakWallTile) {
			weakWallTile->Break();
		}
	}

	bool PlayerModel::CanControl() const
	{
		switch (stateMachine.GetState()) {
			case PlayerState::Fallback:
				return false;
		}

		return true;
	}

	void PlayerModel::AddTransportBeltOffset(const Vector2& offset)
	{
		switch (stateMachine.GetState()) {
			case PlayerState::Fallback:
				return;
		}

		transportBeltOffset += offset;
	}
}