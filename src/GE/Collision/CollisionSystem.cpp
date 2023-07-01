#include "CollisionSystem.h"
#include <unordered_map>
#include <set>
#include "Collider.h"
#include "GE/Core/GameObject.h"

namespace GE::Collision
{
	CollisionLayerMatrix CollisionSystem::collisionLayerMatrix;
	std::vector<Collider*> CollisionSystem::colliders;

	void CollisionSystem::AddCollider(Collider& collider)
	{
		colliders.push_back(&collider);
	}

	void CollisionSystem::RemoveCollider(Collider& collider)
	{
		colliders.erase(std::remove(colliders.begin(), colliders.end(), &collider), colliders.end());
	}

	void CollisionSystem::OnStartCollision()
	{
		// TODO : もっと効率的な方法を考える

		// Layerによっての分類
		std::unordered_map<CollisionLayer::Bitmask, std::vector<Collider*>> map;
		for (auto collider : colliders) {
			map[collider->GetCollisionLayer()].push_back(collider);
		}

		for (auto& pair : map) {
			CollisionLayer::Bitmask targetsBitmask = collisionLayerMatrix[pair.first];

			if (targetsBitmask == CollisionLayer::none) {
				continue;
			}

			// 全てのターゲット
			std::vector<Collider*> targets;
			for (auto& targetPair : map) {
				if ((targetPair.first & targetsBitmask) == targetPair.first) {
					targets.insert(targets.end(), targetPair.second.begin(), targetPair.second.end());
				}
			}

			std::set<Collider*> colliderToAdjustPos;

			// 当たり判定
			for (auto target : targets) {
				for (auto collider : pair.second) {
					if (collider->GetIsTrigger() && target->GetIsTrigger()) {
						continue;
					}

					Detection::CollidedType collidedType = collider->CheckCollision(*target);
					if (collidedType == Detection::CollidedType::None) {
						continue;
					}

					if (collider->GetIsTrigger()) {
						collider->onTriggered.Invoke(*target);
					} else if (target->GetIsTrigger()) {
						target->onTriggered.Invoke(*collider);
					} else {
						if (collidedType == Detection::CollidedType::Overlap) {
							if (!collider->gameObject.GetIsStatic()) {
								colliderToAdjustPos.insert(collider);
							}
							if (!target->gameObject.GetIsStatic()) {
								colliderToAdjustPos.insert(target);
							}
						}

						collider->onCollided.Invoke(*target);
						target->onCollided.Invoke(*collider);
					}
				}
			}

			// 当たり判定後の位置調整
			for (auto collider : colliderToAdjustPos) {
				collider->AdjustCollidedPos();
			}
		}
	}
}