#pragma once

#include "GE/Utils/TypeDef.h"
#include <string>
#include <functional>
#include "MapId.h"

namespace Map
{
	struct MapCoreInfo;

	class MapGenerator
	{
	public:
		void GenerateMap(
			const MapId& mapId, 
			std::function<void(MapCoreInfo)> onSuccess = nullptr,
			std::function<void()> onFailure = nullptr) const;
	};
}