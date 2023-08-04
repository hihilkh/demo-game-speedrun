#pragma once

#include <string>
#include <iostream>

namespace Map
{
	struct MapId
	{
		std::string value;

		MapId(const char* id);
		MapId(const std::string& id);

		std::string GetFilePath() const;
	};

	inline std::ostream& operator<<(std::ostream& os, const MapId& mapId)
	{
		return os << mapId.value;
	}
}