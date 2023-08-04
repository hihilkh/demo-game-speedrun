#pragma once

#include "GE/Utils/TypeDef.h"
#include "GE/Core/Component.h"
#include "MapObjectType.h"

namespace Map
{
	class MapObject : public Component
	{
	public:
		MapObject(GameObject& gameObject, MapObjectType type);
		virtual ~MapObject() = default;

		MapObjectType GetType() const { return type; }
		void SetPos(const Vector2Int& grid);

	private:
		const MapObjectType type;
	};
}