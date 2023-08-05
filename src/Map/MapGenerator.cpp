#include "GE/GEHeader.h"
#include "MapGenerator.h"
#include <fstream>
#include "MapFactory.h"
#include "MapCoreInfo.h"

namespace Map
{
	namespace
	{
		const std::string mapBaseName = "MapBase";
	}

	void MapGenerator::GenerateMap(const MapId& mapId, std::function<void(MapCoreInfo)> onSuccess, std::function<void()> onFailure) const
	{
		std::ifstream fin(mapId.GetFilePath());
		if (!fin) {
			DEBUG_LOG_ERROR("マップの読み込みに失敗した。MapId : " << mapId);
			if (onFailure) {
				onFailure();
			}
			return;
		}

		GameObject* mapBase = GE::FindGameObject(mapBaseName);
		if (!mapBase) {
			mapBase = &GameObject::Create(mapBaseName);
		}

		MapFactory factory(*mapBase);
		MapCoreInfo info;

		int sizeX, sizeY;
		int leftIndex, topIndex;
		int rawInfo;
		fin >> sizeX >> sizeY >> leftIndex >> topIndex;

		for (int y = 0; y < sizeY; ++y) {
			for (int x = 0; x < sizeX; ++x) {
				fin >> rawInfo;
				factory.Create({ leftIndex + x, topIndex  - y }, rawInfo, info);
			}
		}

		if (onSuccess) {
			onSuccess(info);
		}
	}
}