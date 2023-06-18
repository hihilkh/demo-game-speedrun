#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "TileType.h"

namespace Map
{
	class TileBase : public Component
	{
	public:
		TileBase(GameObject& gameObject, TileType type);
		virtual ~TileBase() = default;

		TileType GetType() const { return type; }
		void SetPos(const Vector2Int& pos);

	private:
		const TileType type;
	};
}