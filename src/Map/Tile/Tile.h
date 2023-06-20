#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "TileType.h"

namespace Map
{
	class Tile : public Component
	{
	public:
		Tile(GameObject& gameObject, TileType type);
		virtual ~Tile() = default;

		TileType GetType() const { return type; }
		void SetPos(const Vector2Int& pos);

	private:
		const TileType type;
	};
}