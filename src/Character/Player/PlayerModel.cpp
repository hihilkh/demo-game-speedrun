#include "GE/GEHeader.h"
#include "PlayerModel.h"
#include "PlayerConfig.h"
#include "Map/MapManager.h"
#include "State/PlayerStateRequest.h"
#include "Map/Tile/WeakWallTile.h"
#include "GE/Collision/Collider.h"
#include "Map/Tile/TransportBeltTile.h"

namespace Player
{
	PlayerModel::PlayerModel(GameObject& gameObject) :
		Component(gameObject),
		facingDir(TransformUtils::Direction::Down),
		stateMachine(*this),
		lastWorldPos()
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

		Vector2 totalOffset = Vector2::zero;
		for (auto dir : transportBeltAppliedDir) {
			Vector2 offset = TransformUtils::GetDirectionalVector(dir);
			offset *= transportBeltSpeed * Time::GetDeltaTime();
			totalOffset += offset;
		}

		transform.SetPos(transform.GetPos() + totalOffset);
		transportBeltAppliedDir.clear();
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
		stateMachine.AddStateRequest(PlayerStateRequest::CrashWithWall);

		auto weakWallTile = other.gameObject.GetComponent<Map::WeakWallTile>();
		if (weakWallTile) {
			weakWallTile->Break();
		}
	}

	void PlayerModel::HitWall(const GE::Collision::Collider& other)
	{
		stateMachine.AddStateRequest(PlayerStateRequest::HitWall);
	}

	bool PlayerModel::CanControl() const
	{
		switch (stateMachine.GetState()) {
			case PlayerState::Fallback:
				return false;
		}

		return true;
	}

	void PlayerModel::ApplyTransportBeltDir(TransformUtils::Direction direction)
	{
		switch (stateMachine.GetState()) {
			case PlayerState::Fallback:
				return;
		}

		transportBeltAppliedDir.insert(direction);
	}
}