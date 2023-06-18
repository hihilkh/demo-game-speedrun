#include "GE/GEHeader.h"
#include "MapManager.h"
#include "MapGenerator.h"

namespace Map
{
	GE::Event<> MapManager::onMapLoaded;

	MapManager::MapManager(GameObject& gameObject) :
		Component(gameObject)
	{
	}

	void MapManager::Start()
	{
		LoadMap("Map1", [] { onMapLoaded.Invoke(); });
	}

	void MapManager::LoadMap(const MapId& mapId, std::function<void()> onFinished) const
	{
		MapGenerator generator;
		generator.GenerateMap(mapId, onFinished);
	}
}