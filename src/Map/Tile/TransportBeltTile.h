#pragma once

#include "Tile.h"
#include "TransformUtils/Direction.h"

namespace Map
{
	class TransportBeltTile : public Tile
	{
	public:
		explicit TransportBeltTile(GameObject& gameObject, Collider& collider);

		TransformUtils::Direction GetDirection() const {return direction; }
		void SetDirection(TransformUtils::Direction direction) { this->direction = direction; }

	protected:
		void Start() override;
		void PreDestroy() override;

	private:
		Collider& collider;

		TransformUtils::Direction direction;

	private:
		void HandleTrigger(const Collider& other, CollidedType collidedType);
	};
}