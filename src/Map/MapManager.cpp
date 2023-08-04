#include "GE/GEHeader.h"
#include "MapManager.h"
#include "MapGenerator.h"

namespace Map
{
	namespace
	{
		const MapId mapId = "Map1";
	}

	GE::Event<const MapManager&> MapManager::onMapLoaded;

	MapManager::MapManager(GameObject& gameObject) :
		Component(gameObject),
		mapCoreInfo()
	{
	}

	void MapManager::Start()
	{
		LoadMap(mapId);
	}

	void MapManager::LoadMap(const MapId& mapId)
	{
		auto onLoadFinished = [this](MapCoreInfo info) {
			this->mapCoreInfo = info;
			onMapLoaded.Invoke(*this);
		};

		MapGenerator generator;
		generator.GenerateMap(mapId, onLoadFinished);
	}
}