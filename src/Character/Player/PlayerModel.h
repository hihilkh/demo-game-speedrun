﻿#pragma once

#include <set> 
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "TransformUtils/Direction.h"
#include "State/PlayerStateMachine.h"
#include "GE/DataType/Vector2.h"

namespace Map
{
	class MapManager;
}

namespace Player
{
	class PlayerModel : public Component
	{
	public:
		explicit PlayerModel(GameObject& gameObject);

	public:

		/// <param name="dirVector">長さは1とは限らない</param>
		void Move(const Vector2& dirVector);
		void StartRunning();
		void StopRunning();
		void Crash(const Collider& other);
		void HitWall(const Collider& other);
		bool CanControl() const;

		TransformUtils::Direction GetFacingDirection() const { return facingDir; }
		void UpdateFacingDirection();

		const Vector2& GetMoveDirVector() const { return moveDirVector; }
		const Vector2& GetLastWorldPos() const { return lastWorldPos; }
		PlayerState GetPlayerState() const { return stateMachine.GetState(); }

		void ApplyTransportBeltDir(TransformUtils::Direction direction);

	protected:
		void Awake() override;
		void PreDestroy() override;
		void Update() override;
		void LateUpdate() override;

	private:
		TransformUtils::Direction facingDir;
		PlayerStateMachine stateMachine;
		Vector2 moveDirVector;
		Vector2 lastWorldPos;
		// TODO : もっと良い方法を考える
		std::set<TransformUtils::Direction> transportBeltAppliedDir;

	private:
		void SceneReadyHandler(const Map::MapManager& mapManager);
	};
}
