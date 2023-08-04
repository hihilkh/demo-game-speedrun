#pragma once

#include "GE/Core/Component.h"
#include "GE/Utils/TypeDef.h"
#include "GE/Core/Event.h"
#include "MapId.h"
#include "MapCoreInfo.h"

namespace Map
{
	class MapManager : public Component
	{
	public:
		static GE::Event<const MapManager&> onMapLoaded;

	public:
		MapManager(GameObject& gameObject);
		const Vector2& GetPlayerStartPos() const { return mapCoreInfo.playerStartPos; }
		const Vector2& GetGoalPos() const { return mapCoreInfo.goalPos; }

	protected:
		void Start() override;

	private:
		MapCoreInfo mapCoreInfo;

	private:
		void LoadMap(const MapId& mapId);
	};
}